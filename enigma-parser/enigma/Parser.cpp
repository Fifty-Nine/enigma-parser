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



namespace
{
QSet<TokenType> makeSet(TokenType type)
{
    QSet<TokenType> r;
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
    
    Token *next() 
    {
        if (!m_next)
        {
            m_next = m_lexer->nextToken();
        }

        return m_next.get();
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

    TokenPtr consume(const QSet<TokenType>& expected = QSet<TokenType>())
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

    void expect(const QSet<TokenType>& expected = QSet<TokenType>())
    {
        if ((expected.count() > 0) && 
            !expected.contains(next()->type()))
        {
            QStringList names;
            typedef QSet<TokenType>::const_iterator It;
            for (It it = expected.begin(); it != expected.end(); ++it)
            {
                names << it->toString().toLower();
            }
            throw exceptions::ExpectedInputException(
                m_lexer->currentPos(), names);
        }
    }

    ast::ListPtr parseList()
    {
        FilePos start = next()->location().first;
        consume(TokenType::LeftBrace);

        TokenPtr leaf = consume();
        Token *peek = next();

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

        FileSpan span(start, next()->location().first);
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

        FileSpan span(start, next()->location().first);
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
        QSet<TokenType> expected;
        expected << TokenType::Identifier;
        expected << TokenType::Tag;
        expected << TokenType::Integer;
        expected << TokenType::Date;
        expected << TokenType::String;
        expect(expected);

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
        QSet<TokenType> expected;
        expected << TokenType::Boolean;
        expected << TokenType::Date;
        expected << TokenType::Decimal;
        expected << TokenType::Identifier;
        expected << TokenType::Integer;
        expected << TokenType::String;
        expected << TokenType::Tag;
        TokenPtr tok = consume(expected);
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

ast::AssignmentListPtr Parser::parse()
{
    return d->parseAssignmentList(d->m_lexer->currentPos());
}

ast::AssignmentPtr Parser::parseOne()
{
    return d->maybeParseAssignment();
}

} // namespace enigma

