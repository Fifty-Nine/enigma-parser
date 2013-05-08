#include "enigma/tokens/DateToken.h"

namespace enigma
{
namespace tokens
{

DateToken::DateToken(const Date& date, bool stringify, const FilePos& loc)
    : StringToken(TokenType::Date, date.toString(), stringify, loc)
{
}

void DateToken::setDate(const Date& date)
{
    m_date = date;
    StringToken::setValue(date.toString());
}

bool DateToken::setValue(const QVariant& value)
{
    if (!value.canConvert(QVariant::String)) return false;

    Date new_value = Date::parse(value.toString());

    if (!new_value.isValid()) return false;

    m_date = new_value;

    return true;
}

DateToken *DateToken::clone() const
{
    return new DateToken(m_date, m_stringify, location());
}

} // namespace tokens
} // namespace enigma
