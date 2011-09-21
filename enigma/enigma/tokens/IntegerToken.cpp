
#include "enigma/tokens/IntegerToken.h"

namespace enigma
{
namespace tokens 
{

IntegerToken::IntegerToken(long long value, bool stringify) : 
    Token(TokenType::Integer), m_value(value), m_stringify(stringify)
{
}

QString IntegerToken::toString() const
{
    QString format = m_stringify ? "\"%1\"" : "%1";

    return format.arg( m_value );
}

IntegerToken *IntegerToken::clone() const
{
    return new IntegerToken(m_value, m_stringify);
}

} // namespace tokens
} // namespace enigma
