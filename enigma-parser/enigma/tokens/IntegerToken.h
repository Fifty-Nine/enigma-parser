#ifndef ENIGMA_TOKENS_INTEGER_TOKEN_H
#define ENIGMA_TOKENS_INTEGER_TOKEN_H
#pragma once

#include "enigma/tokens/Token.h"

namespace enigma
{
namespace tokens 
{

class IntegerToken : public Token
{
public:
    /*! Construct a decimal token with the given value and precision.
     * \param [in] value The value.
     * \param [in] stringify True if the value is quoted, as in StringToken. */
    IntegerToken(long long value, bool stringify);

    /*! Get the token's integral value. */
    virtual QVariant value() const { return m_value; }
    virtual bool setValue(const QVariant& value);
    void setValue(long long value) { m_value = value; }

    virtual QString toString() const;
    virtual IntegerToken *clone() const;

private:
    long long m_value;
    const bool m_stringify;
};

} // namespace tokens
} // namespace enigma
#endif // ENIGMA_TOKENS_INTEGER_TOKEN_H

