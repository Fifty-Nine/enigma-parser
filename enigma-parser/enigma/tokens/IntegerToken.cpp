
#include "enigma/tokens/IntegerToken.h"

namespace enigma
{
namespace tokens 
{

IntegerToken::IntegerToken(
    long long value, bool stringify, const FilePos& loc) : 
    Token(TokenType::Integer, loc), m_value(value), m_stringify(stringify)
{
}

bool IntegerToken::setValue(const QVariant& value)
{
    if (!value.canConvert(QVariant::LongLong)) return false;

    m_value = value.toLongLong();

    return true;
}

QString IntegerToken::toString() const
{
    QString format = m_stringify ? "\"%1\"" : "%1";

    return format.arg( m_value );
}

IntegerToken *IntegerToken::clone() const
{
    return new IntegerToken(m_value, m_stringify, location());
}

} // namespace tokens
} // namespace enigma
