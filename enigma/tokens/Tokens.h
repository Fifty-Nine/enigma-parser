#ifndef ENIGMA_TOKENS_H
#define ENIGMA_TOKENS_H

#include <boost/util/noncopyable.hpp>

#include "enigma/util/Enumeration.h"

namespace enigma
{

class DecimalToken : public Token
{
public:
    DecimalToken(double value, int precision, bool stringify);

    double value() const { return m_value; }

    virtual DecimalToken *clone() const;
    virtual QString toString() const;

private:
    double m_value;
    int m_precision;
    bool m_stringify;
};

class EndOfFileToken : public Token
{
public:
    EndOfFileToken() { }

    virtual EndOfFileToken *clone() { return new EndOfFileToken; }
    virtual QString toString() const { return ""; }
};

} // namespace enigma

#endif // ENIGMA_TOKENS_H
