#ifndef ENIGMA_TOKENS_TOKEN_H
#define ENIGMA_TOKENS_TOKEN_H
#pragma once

#include <boost/noncopyable.hpp>
#include <QString>
#include <QVariant>

#include "enigma/util/Enumeration.h"

namespace enigma
{
namespace tokens
{

struct TokenTypeDef
{
enum Enum
{
    Identifier,
    Boolean,
    String,
    Tag,
    Date,
    Integer,
    Decimal,
    LeftBrace,
    RightBrace,
    Equals,
};

static QString toString(Enum t)
{
    switch (t)
    {
    case Identifier: return "Identifier";
    case Boolean: return "Boolean";
    case String: return "String";
    case Tag: return "Tag";
    case Date: return "Date";
    case Integer: return "Integer";
    case Decimal: return "Decimal";
    case LeftBrace: return "LeftBrace";
    case RightBrace: return "RightBrace";
    case Equals: return "Equals";
    }
    return "Unknown";
}

};

typedef util::Enumeration<TokenTypeDef> TokenType;

class Token : boost::noncopyable
{
public:
    virtual ~Token();

    /*! Get the type of the token.
     * \return The type. */
    TokenType type() const { return m_type; }

    /*! Clone the given token.
     * \returns a copy of the token. The caller takes ownership. */
    virtual Token *clone() const = 0;

    /*! Convert the token to a string.
     * \return A human-readable representation of the token. */
    virtual QString toString() const = 0;

    /*! Get the value of the token, if applicable. */
    virtual QVariant value() const { return QVariant(); }

    /*! Set the value of the token, if applicable. 
     *  \return True if the value was set. */
    virtual bool setValue(const QVariant&) { return false; }

protected:
    Token(TokenType type) : 
        m_type(type) { }

private:
    const TokenType m_type;
};

} // namespace tokens
} // namespace enigma

#include "LiteralTokens.h"

#endif // ENIGMA_TOKENS_TOKEN_H



