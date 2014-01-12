#include "Parser.h"

#include <stack>
#include <QSet>
#include <QStringList>

#include "enigma/Lexer.h"
#include "enigma/ast/Assignment.h"
#include "enigma/ast/AssignmentList.h"
#include "enigma/ast/ValueList.h"
#include "enigma/ast/Leaf.h"
#include "enigma/tokens/Token.h"
#include "enigma/exceptions/ExpectedInputException.h"

using namespace enigma::tokens;

namespace enigma
{

typedef QSet<TokenType> TokenSet;

namespace
{
TokenSet makeSet(TokenType type)
{
    TokenSet r;
    r << type;
    return r;
}
}

class Parser::Data 
{
public:
    Data(std::unique_ptr<Lexer> lexer) : 
        m_lexer(std::move(lexer)) 
    { 
    }
    
    TokenPtr next() 
    {
        if (!m_next)
        {
            m_next = m_lexer->nextToken();
        }

        return m_next;
    }

    bool atEnd() 
    {
        return !next();
    }

    void backtrack(TokenPtr t)
    {
        m_backtrack.push(std::move(m_next));
        m_next = std::move(t);
    }

    TokenPtr consume(TokenType expected) 
    { 
        return consume(makeSet(expected)); 
    }

    TokenPtr consume(const TokenSet& expected = TokenSet())
    {
        expect(expected);
    
        TokenPtr result = std::move(m_next);

        if (!m_backtrack.empty())
        {
            m_next = std::move(m_backtrack.top());
            m_backtrack.pop();
        }
        else
        {
            m_next = m_lexer->nextToken();
        }

        return result;
    }

    void expect(TokenType expected)
    {
        expect(makeSet(expected));
    }

    void expect(const TokenSet& expected = TokenSet())
    {
        if ((expected.count() > 0) && 
            !expected.contains(next()->type()))
        {
            QStringList names;
            for (TokenType t : expected)
            {
                names << t.toString().toLower();
            }
            throw exceptions::ExpectedInputException(
                m_lexer->currentPos(), names);
        }
    }

    ast::ListPtr parseList()
    {
        FilePos start = m_lexer->currentPos();
        consume(TokenType::LeftBrace);

        TokenPtr leaf = consume();
        TokenPtr peek = next();

        backtrack(std::move(leaf));

        ast::ListPtr result;

        if (peek->type() == TokenType::Equals)
        {
            result = std::move(parseAssignmentList(start));
        }
        else
        {
            result = std::move(parseValueList(start));
        }

        return result;
    }

    ast::AssignmentListPtr parseAssignmentList(FilePos start)
    {
        QList<ast::AssignmentPtr> nodes;

        while (!atEnd() && (next()->type() != TokenType::RightBrace))
        {
            nodes << parseAssignment();
        }
        
        consume(TokenType::RightBrace);

        FileSpan span(start, m_lexer->currentPos());
        return ast::AssignmentListPtr(
            new ast::AssignmentList(nodes, span));
    }

    ast::ValueListPtr parseValueList(FilePos start)
    {
        QList<ast::ValuePtr> nodes;

        while (!atEnd() && (next()->type() != TokenType::RightBrace))
        {
            nodes << parseValue();
        }

        consume(TokenType::RightBrace);

        FileSpan span(start, m_lexer->currentPos());
        return ast::ValueListPtr(new ast::ValueList(nodes, span));
    }

    ast::ValuePtr parseValue()
    {
        if (next()->type() == TokenType::LeftBrace)
        {
            return parseList();
        }

        return parseLeaf();
    }

    ast::AssignmentPtr parseAssignment()
    {
        expect(TokenSet()
            << TokenType::Identifier
            << TokenType::Tag
            << TokenType::Integer
            << TokenType::Date
            << TokenType::String
        );

        ast::LeafPtr left(parseLeaf());

        consume(TokenType::Equals);

        ast::ValuePtr right(parseValue());

        return ast::AssignmentPtr(
            new ast::Assignment(std::move(left), std::move(right)));
    }

    ast::AssignmentPtr maybeParseAssignment()
    { 
        return (next() && (next()->type() != TokenType::RightBrace)) ? 
            parseAssignment() : ast::AssignmentPtr();
    }

    ast::LeafPtr parseLeaf()
    {
        TokenPtr tok = consume(TokenSet() 
            << TokenType::Boolean
            << TokenType::Date
            << TokenType::Decimal
            << TokenType::Identifier
            << TokenType::Integer
            << TokenType::String
            << TokenType::Tag
        );
        return ast::LeafPtr(new ast::Leaf(std::move(tok)));
    }

    std::unique_ptr<Lexer> m_lexer;
    TokenPtr m_next;
    std::stack<TokenPtr> m_backtrack;
};

Parser::Parser(std::unique_ptr<Lexer> lexer) : 
    d(new Data(std::move(lexer)))
{
}

Parser::~Parser()
{
}

FilePos Parser::currentPos() const
{
    return d->m_lexer->currentPos();
}

FileType Parser::parseHeader() {
    TokenPtr t = d->next();
    QString value = t->toString();

    if (value == "CK2txt") { 
        d->consume();
        return FileType::CK2Txt;
    }
    else if (value == "CK2bin") { 
        d->consume();
        return FileType::CK2Bin; 
    }
    else {
        // Assume text for backwards compatibility.
        return FileType::CK2Txt;
    }
}

File Parser::parse()
{
    return File { 
        parseHeader(), 
        d->parseAssignmentList(d->m_lexer->currentPos()) 
    };
}

ast::AssignmentPtr Parser::parseOne()
{
    return d->maybeParseAssignment();
}

} // namespace enigma

