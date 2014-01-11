#include "enigma/tokens/DateToken.h"

namespace enigma
{
namespace tokens
{

DateToken::DateToken(const Date& date, bool stringify)
    : StringToken(TokenType::Date, date.toString(), stringify)
{
}

void DateToken::setDate(const Date& date)
{
	m_date = date;
	StringToken::setValue(date.toString());
}

DateToken *DateToken::clone() const
{
    return new DateToken(m_date, m_stringify);
}

} // namespace tokens
} // namespace enigma
