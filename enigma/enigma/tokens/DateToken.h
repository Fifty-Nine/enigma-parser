#ifndef ENIGMA_TOKENS_DATE_TOKEN_H
#define ENIGMA_TOKENS_DATE_TOKEN_H
#pragma once

#include "enigma/Date.h"
#include "enigma/tokens/StringToken.h"

namespace enigma
{
namespace tokens
{

class DateToken : public StringToken
{
public:
    /*! Construct a new token initialized with the given date.
     * \param[in] date The date.
     * \param[in] stringify True to quote the date, as in StringToken. */
    DateToken(const Date& date, bool stringify);

    /*! Get the date value of this token. 
     * \return The date. */
    Date date() const { return m_date; }
    void setDate(const Date& date);

    QVariant value() const { return m_date.toString(); }

    virtual DateToken *clone() const;

private:
    Date m_date;
};

} // namespace tokens
} // namespace enigma
#endif // ENIGMA_TOKENS_DATE_TOKEN_H
