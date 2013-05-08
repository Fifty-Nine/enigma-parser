#ifndef ENIGMA_TOKENS_STRING_TOKEN_H
#define ENIGMA_TOKENS_STRING_TOKEN_H
#pragma once

#include "enigma/tokens/Token.h"

namespace enigma 
{
namespace tokens 
{ 

class StringToken : public Token
{
public:
    /*! Construct a string token with the given value. */
    StringToken(const QString& value, const FileSpan& loc);

    virtual StringToken *clone() const;
    virtual QString toString() const;

    QVariant value() const { return m_value; }
    virtual bool setValue(const QVariant& value);

protected:
    /*! Construct a string token with the given parameters. 
     * \param[in] type The token type.
     * \param[in] value The token value.
     * \param[in] stringify True if the string representation should appear
     *                      within quotation marks.
     * \param[in] loc The location of the token in the input file. */
    StringToken(TokenType type, const QString& value, bool stringify, 
        const FileSpan& loc);

    void setValue(const QString& value) { m_value = value; }

    QString m_value;
    bool m_stringify;
};

} // namespace tokens
} // namespace enigma

#endif // ENIGMA_TOKENS_STRING_TOKEN_H
