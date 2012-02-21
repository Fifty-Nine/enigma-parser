#include "enigma/tokens/IdentifierToken.h"

namespace enigma
{
namespace tokens
{

IdentifierToken::IdentifierToken(
    const QString& identifier, const Location& loc) : 
    StringToken(TokenType::Identifier, identifier, false, loc)
{
}

IdentifierToken *IdentifierToken::clone() const
{
    return new IdentifierToken(m_value, location());
}

} // namespace tokens
} // namespace enigma
