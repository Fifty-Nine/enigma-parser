#include "enigma/ast/Leaf.h"

#include <cassert>

#include "enigma/tokens/LiteralTokens.h"
#include "enigma/visitors/Visitor.h"

namespace enigma
{
namespace ast
{

Leaf::Leaf(tokens::TokenPtr token) : 
    Value(NodeType::Value, token->location()), 
    m_token(std::move(token)) 
{ 
    using namespace tokens;

    assert( m_token
         && (m_token->type() != TokenType::LeftBrace)
         && (m_token->type() != TokenType::RightBrace)
         && (m_token->type() != TokenType::Equals) ); 
}

Leaf::~Leaf() 
{ 
}

Leaf *Leaf::clone() const
{
    return new Leaf(m_token->clone());
}

void Leaf::accept(visitors::Visitor& visitor)
{
    visitor.visit(*this);
}

void Leaf::accept(visitors::ConstVisitor& visitor) const
{
    visitor.visit(*this);
}

Leaf::Leaf(tokens::Token *token) : 
    Value(NodeType::Value, token->location()), 
    m_token(token)
{
}

QString Leaf::toString() const
{
    return m_token->toString();
}

QVariant Leaf::value() const
{
    return m_token->value();
}

} // namespace ast
} // namespace enigma
