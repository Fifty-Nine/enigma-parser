#ifndef ENIGMA_TOKENS_IDENTIFIER_TOKEN_H
#define ENIGMA_TOKENS_IDENTIFIER_TOKEN_H
#pragma once

#include "enigma/tokens/StringToken.h"

namespace enigma
{
namespace tokens
{

class IdentifierToken : public StringToken
{
public:
    /*! Construct a new token initialized with the given name.
     * \param[in] identifier The identifier.
     * \param [in] loc The location of the token in the input file. */
    IdentifierToken(const QString& identifier, const FileSpan& loc);

    /*! Get the date value of this token. 
     * \return The date. */
    QString identifier() const { return m_value; }
    void setIdentifier(const QString& value) { StringToken::setValue(value); }

    virtual IdentifierToken *clone() const;
};

} // namespace tokens
} // namespace enigma
#endif // ENIGMA_TOKENS_IDENTIFIER_TOKEN_H
