#ifndef ENIGMA_TOKENS_LITERAL_TOKENS_H
#define ENIGMA_TOKENS_LITERAL_TOKENS_H
#pragma once

#include "enigma/tokens/Token.h"

namespace enigma
{
namespace tokens
{

template<TokenType::Enum T, char c>
class LiteralToken : public Token
{
public:
    LiteralToken(const FileSpan& loc) : Token(T, loc) { }

    virtual LiteralToken *clone() const { return new LiteralToken(location()); }
    virtual QString toString() const { return QString(c); }
};

typedef LiteralToken<TokenType::LeftBrace, '{'> LeftBraceToken;
typedef LiteralToken<TokenType::RightBrace, '}'> RightBraceToken;
typedef LiteralToken<TokenType::Equals, '='> EqualsToken;

typedef std::shared_ptr<LeftBraceToken> LeftBraceTokenPtr;
typedef std::shared_ptr<RightBraceToken> RightBraceTokenPtr;
typedef std::shared_ptr<EqualsToken> EqualsTokenPtr;

} // namespace tokens
} // namespace enigma

#endif // ENIGMA_TOKENS_LITERAL_TOKENS_H


