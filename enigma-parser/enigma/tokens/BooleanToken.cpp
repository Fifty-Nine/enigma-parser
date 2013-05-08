#include "enigma/tokens/BooleanToken.h"

namespace enigma
{
namespace tokens
{

BooleanToken::BooleanToken(bool value, bool stringify, const FileSpan& loc) :
    StringToken(TokenType::Boolean, value ? "yes" : "no", stringify, loc),
    m_value(value)
{
}

BooleanToken *BooleanToken::clone() const
{
    return new BooleanToken(m_value, m_stringify, location());
}

void BooleanToken::setValue(bool value)
{
    m_value = value;
    StringToken::setValue(QString(value ? "yes" : "no"));
}

bool BooleanToken::setValue(const QVariant& value)
{
    if (!value.canConvert(QVariant::Bool)) return false;

    m_value = value.toBool();

    return true;
}

} // namespace tokens
} // namespace enigma
