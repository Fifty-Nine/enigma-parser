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
     * \param[in] identifier The identifier. */
    IdentifierToken(const QString& identifier);

    /*! Get the date value of this token. 
     * \return The date. */
    QString identifier() const { return m_value; }
	void setIdentifier(const QString& value) { StringToken::setValue(value); }

    virtual IdentifierToken *clone() const;
};

} // namespace tokens
} // namespace enigma
#endif // ENIGMA_TOKENS_IDENTIFIER_TOKEN_H
