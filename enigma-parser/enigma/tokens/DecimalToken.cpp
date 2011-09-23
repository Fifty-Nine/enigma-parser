#include "enigma/tokens/DecimalToken.h"

namespace enigma
{
namespace tokens 
{

DecimalToken::DecimalToken(double value, int precision, bool stringify) :
    Token(TokenType::Decimal), 
    m_value(value), m_precision(precision), m_stringify(stringify)
{
}

DecimalToken *DecimalToken::clone() const
{
    return new DecimalToken(m_value, m_precision, m_stringify);
}

bool DecimalToken::setValue(const QVariant& value)
{
    if (!value.canConvert(QVariant::Double)) return false;

    m_value = value.toDouble();

    return true;
}

QString DecimalToken::toString() const
{
    QString format = m_stringify ? "\"%1\"" : "%1";

    return format.arg(QString::number(m_value, 'f', m_precision));
}

} // namespace tokens
} // namespace enigma

