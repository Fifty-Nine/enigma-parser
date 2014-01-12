#include <QStringList>
#include <QTextStream>

#include "enigma/Lexer.h"

#include "enigma/exceptions/ExpectedInputException.h"
#include "enigma/exceptions/UnmatchedInputException.h"
#include "enigma/tokens/BooleanToken.h"
#include "enigma/tokens/DateToken.h"
#include "enigma/tokens/DecimalToken.h"
#include "enigma/tokens/FileStartToken.h"
#include "enigma/tokens/IdentifierToken.h"
#include "enigma/tokens/IntegerToken.h"
#include "enigma/tokens/LiteralTokens.h"
#include "enigma/tokens/TagToken.h"

namespace enigma
{

using namespace tokens;

struct Lexer::Impl
{
    Impl(QIODevice *device_) :
        device(device_), stream(device_), 
        token_start(0, 1, 1), 
        token_end(0, 1, 1)
    {
        stream.setCodec("UTF-8");

        buffer = stream.read(1024);
        buffer_it = buffer.begin();
    }

    QString prettyChar(QChar c)
    {
        if ( !c.isNull() )
        {
            return "end of file";
        }

        return QString( c );
    }

    void newSpan()
    {
        token_start = token_end;
    }

    FileSpan currentSpan() const
    {
        return FileSpan(token_start, token_end);
    }

    std::unique_ptr<QIODevice> device;
    QTextStream stream;
    QString buffer;
    QString::const_iterator buffer_it;

    FilePos token_start;
    FilePos token_end;
};

Lexer::Lexer(std::unique_ptr<QIODevice> device) : 
    d(new Impl(device.release()))
{
}

Lexer::~Lexer()
{
}

TokenPtr Lexer::nextToken()
{
    while (true)
    {
        while (peek().isSpace())
        {
            consume();
        }

        QChar next = peek();
        d->newSpan();

        if (next.isNull())
        {
            return TokenPtr();
        }
        else if (next == '{')
        {
            consume();
            return TokenPtr(new LeftBraceToken(d->currentSpan()));
        }
        else if (next == '}')
        {
            consume();
            return TokenPtr(new RightBraceToken(d->currentSpan()));
        }
        else if (next == '=')
        {
            consume();
            return TokenPtr(new EqualsToken(d->currentSpan()));
        }
        else if (next.isLetter())
        {
            return lexIdentifiers();
        }
        else if (next == '"')
        {
            return lexStrings();
        }
        else if (next.isDigit() || next == '-')
        {
            return lexNumeric();
        }
        else if (next == '#')
        {
            consumeToEnd();
            continue;
        }

        throw exceptions::UnmatchedInputException(currentPos(), next);
    }
}

FilePos Lexer::currentPos() const
{
    return d->token_start;
}

/*! Lex any identifier types at the current position of the stream.
 * \return The lexed identifier token. */
TokenPtr Lexer::lexIdentifiers()
{
    QString id = "";

    do 
    {
        id += peek();
        consume();
    } while ( peek().isLetterOrNumber() 
           || peek() == '_' 
           || peek() == '-' 
           || peek() == '\''
           || peek() == ','
            );

    QString lower = id.toLower();

    if (lower == "yes" || lower == "no")
    {
        return TokenPtr(new BooleanToken(lower == "yes", false, 
            d->currentSpan()));
    }
    else if (lower == "ck2txt") 
    {
        return TokenPtr(new FileStartToken(d->currentSpan()));
    }

    if ((id.count() == 3) && ((id == "---") || (id == id.toUpper())))
    {
        return TokenPtr(new TagToken(id, false, d->currentSpan()));
    }

    return TokenPtr(new IdentifierToken(id, d->currentSpan()));
}

/*! Lex any string types at the current position of the stream.
 * \return The lexed token. */
TokenPtr Lexer::lexStrings()
{
    consume();

    QChar next = peek();

    QString str = "";

    int decimals = 0;
    while (!next.isNull() && next != '"')
    {
        str += next;
        if (next == '.') ++decimals;
        consume();
        next = peek();
    }

    consume('"');

    if ((str.count() == 3) && ((str == "---") || (str == str.toUpper())))
    {
        return TokenPtr(new TagToken(str, true, d->currentSpan()));
    }

    if ((decimals == '2') || (decimals == 3))
    {
        Date date = Date::parse(str);

        if (date.isValid())
        {
            return TokenPtr(new DateToken(date, true, d->currentSpan()));
        }
    }

    if (decimals == 0)
    {
        bool ok = false;
        long long v = str.toLongLong(&ok);
        if (ok)
        {
            return TokenPtr(new IntegerToken(v, true, d->currentSpan()));
        }
    }

    if (decimals == 1)
    {
        int prec = str.split('.')[1].count();
        bool ok = false;
        double v = str.toDouble(&ok);

        if (ok)
        {
            return TokenPtr(new DecimalToken(v, prec, true, d->currentSpan()));
        }
    }

    return TokenPtr(new StringToken(str, d->currentSpan()));
}

/*! Lex any numeric types at the current position of the stream.
 * \return The lexed numeric token. */
TokenPtr Lexer::lexNumeric()
{
    QString str = "";

    if (peek() == '-')
    {
        str += '-';
        consume();
    }

    int decimals = 0;

    while (peek().isDigit() || peek() == '.')
    {
        if (peek() == '.')
        {
            decimals++;
        }

        str += peek();
        consume();
    }

    if (decimals > 1)
    {
        Date date = Date::parse(str);

        if (!date.isValid())
        {
            throw exceptions::UnmatchedInputException(currentPos(), str);
        }

        return TokenPtr(new DateToken(date, false, d->currentSpan()));
    }
    else if (decimals == 1)
    {
        int prec = str.split('.')[1].count();

        return TokenPtr(new DecimalToken(str.toDouble(), prec, false, 
            d->currentSpan()));
    }

    return TokenPtr(new IntegerToken(str.toLongLong(), false, 
        d->currentSpan()));
}

/*! Examine the next character in the stream without consuming it. 
 * \return The next character, or -1 at end of file. */
QChar Lexer::peek() const
{
    return (d->buffer_it != d->buffer.end()) ?  
        *d->buffer_it : QChar();
}

/*! Assert that the character at the current position in the stream equals
 * the given values, throwing an exception if not.
 * \param [in] expected The expected character.
 * \throws an ExpectedInputException if the current input does not equal the
 * given expected character. */
void Lexer::expect(const QChar& expected)
{
    QSet<QChar> expected_set;
    expected_set << expected;
    expect(expected_set);
}

/*! Assert that the character at the current position in the stream has
 * one of the given values, throwing an exception if not.
 * \param [in] expected The set of potentially expected characters.
 * \throws an ExpectedInputException if the current input is not in the given
 *         expected set. */
void Lexer::expect(const QSet<QChar>& expected)
{
    if (expected.count() > 0 && !expected.contains(peek()))
    {
        QStringList chars;
        typedef QSet<QChar>::const_iterator Iterator;
        for (Iterator it = expected.begin(); it != expected.end(); ++it)
        {
            chars << d->prettyChar( *it );
        }

        throw exceptions::ExpectedInputException(currentPos(), chars);
    }
}

/*! Consume the next character of input, asserting that the consumed character
 *  is equal to the given character, throwing an exception if it is not.
 * \param [in] expected The expected character.
 * \throws an ExpectedInputException if the current does not equal the expected
 *         input. */
void Lexer::consume(const QChar& expected)
{
    QSet<QChar> expected_set;
    expected_set << expected;
    consume(expected_set);
}


/*! Consume the next character of input. If the given expected set is not empty,
 *  also assert that the consumed character is in the set, throwing an exception
 *  if it is not.
 * \param [in] expected The set of potentially expected characters.
 * \throws an ExpectedInputException if the current input is not in the given
 *         expected set. */
void Lexer::consume(const QSet<QChar>& expected)
{
    expect(expected);

    if (d->buffer.count() == 0)
    {
        return;
    }

    QChar head = *d->buffer_it;
    if (++d->buffer_it == d->buffer.end())
    {
        d->buffer = d->stream.read(1024);
        d->buffer_it = d->buffer.begin();
    }

    if ( head == '\n' )
    {
        ++d->token_end.line;
        d->token_end.column = 0;
    }
    ++d->token_end.pos;
    ++d->token_end.column;
}

/*! Consume input until the end of the line. */
void Lexer::consumeToEnd()
{
    while (peek() != '\n')
    {
        consume();
    }
    consume();
}

}
