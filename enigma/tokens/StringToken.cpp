#include "enigma/tokens/StringToken.h"

namespace enigma 
{
namespace tokens
{

StringToken::StringToken(const QString& value) : 
    Token(TokenType::String), m_value(value), m_stringify(true)
{
}

StringToken *StringToken::clone() const
{
    return new StringToken(type(), m_value, m_stringify);
}

QString StringToken::toString() const
{
    return m_stringify ? QString("\"%1\"").arg(m_value) : m_value;
}

StringToken::StringToken( 
    TokenType type, const QString& value, bool stringify) :
    Token(type), m_value(value), m_stringify(stringify)
{
}

} // namespace tokens
} // namespace enigma
