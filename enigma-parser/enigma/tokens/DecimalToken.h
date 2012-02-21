#ifndef ENIGMA_TOKENS_DECIMAL_TOKEN_H
#define ENIGMA_TOKENS_DECIMAL_TOKEN_H
#pragma once

#include "enigma/tokens/Token.h"

namespace enigma
{
namespace tokens 
{

class DecimalToken : public Token
{
public:
    /*! Construct a decimal token with the given value and precision.
     * \param [in] value The value.
     * \param [in] precision The precision.
     * \param [in] stringify True if the value is quoted, as in StringToken.
     * \param [in] loc The location of the token in the input file. */
    DecimalToken(
        double value, int precision, bool stringify, const Location& loc);

    /*! Get the numeric value of the token. */
    virtual QVariant value() const { return m_value; }
    virtual bool setValue(const QVariant& value);
    void setValue(double value) { m_value = value; }

    int precision() const { return m_precision; }
    void setPrecision(int precision) { m_precision = precision; }

    virtual DecimalToken *clone() const;
    virtual QString toString() const;

private:
    double m_value;
    int m_precision;
    bool m_stringify;
};

} // namespace tokens
} // namespace enigma
#endif // ENIGMA_TOKENS_DECIMAL_TOKEN_H
