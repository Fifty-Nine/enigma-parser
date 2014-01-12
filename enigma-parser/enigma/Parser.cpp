#include "Parser.h"

#include <stack>
#include <QSet>
#include <QStringList>

#include "enigma/Lexer.h"
#include "enigma/ast/Assignment.h"
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

Parser::Callback default_cb = [](ast::NodePtr) { };

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

    ast::ValueListPtr parseValueList(Callback cb)
    {
        QList<ast::ValuePtr> nodes;
        FilePos start = m_lexer->currentPos();

        while (!atEnd() && (next()->type() != TokenType::RightBrace))
        {
            nodes << parseValue(cb);
        }

        FileSpan span(start, m_lexer->currentPos());
        ast::ValueListPtr result(new ast::ValueList(nodes, span));
        cb(result);
        return result;
    }

    ast::ValuePtr parseValue(Callback cb)
    {
        if ((next()->type() == TokenType::LeftBrace) || 
            (next()->type() == TokenType::FileStart))
        {
            consume(TokenSet()
                << TokenType::LeftBrace
                << TokenType::FileStart
            );

            ast::ValuePtr result = parseValueList(cb);

            consume(TokenType::RightBrace);

            return result;
        }
       
        ast::LeafPtr leaf = parseLeaf(cb);

        if (ast::AssignmentPtr assignment = tryParseAssignment(leaf, cb))
        {
            return assignment;
        }
        return leaf;
    }

    ast::AssignmentPtr tryParseAssignment(ast::LeafPtr left, Callback cb)
    {
        if (atEnd() || next()->type() != TokenType::Equals)
        {
            return ast::AssignmentPtr();
        }

        consume();
        ast::ValuePtr right(parseValue(cb));
        ast::AssignmentPtr result(
            new ast::Assignment(std::move(left), std::move(right)));
        cb(result);
        return result;
    }

    ast::LeafPtr parseLeaf(Callback cb)
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
        ast::LeafPtr result(new ast::Leaf(std::move(tok)));
        cb(result);
        return result;
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

ast::ValueListPtr Parser::parse()
{
    return parse(default_cb);
}

ast::ValueListPtr Parser::parse(Callback cb)
{
    return d->parseValueList(cb);
}

} // namespace enigma

