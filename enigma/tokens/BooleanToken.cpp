#include "enigma/tokens/BooleanToken.h"

namespace enigma
{
namespace tokens
{

BooleanToken::BooleanToken(bool value, bool stringify) :
    StringToken(TokenType::Boolean, value ? "yes" : "no", stringify),
    m_value(value)
{
}

BooleanToken *BooleanToken::clone() const
{
    return new BooleanToken(m_value, m_stringify);
}

void BooleanToken::setValue(bool value)
{
	m_value = value;
	StringToken::setValue(value ? "yes" : "no");
}

} // namespace tokens
} // namespace enigma
