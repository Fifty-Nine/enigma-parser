#include "enigma/tokens/IdentifierToken.h"

namespace enigma
{
namespace tokens
{

IdentifierToken::IdentifierToken(const QString& identifier) : 
    StringToken(TokenType::Identifier, identifier, false)
{
}

IdentifierToken *IdentifierToken::clone() const
{
    return new IdentifierToken(m_value);
}

} // namespace tokens
} // namespace enigma
