#ifndef ENIGMA_TOKENS_TAG_TOKEN_H
#define ENIGMA_TOKENS_TAG_TOKEN_H
#pragma once

#include "enigma/tokens/StringToken.h"

namespace enigma
{
namespace tokens
{

class TagToken : public StringToken
{
public:
    TagToken(const QString& tag, bool stringify);

	using StringToken::setValue;

    virtual TagToken *clone() const;
};

} // namespace tokens
} // namespace enigma

#endif // ENIGMA_TOKENS_TAG_TOKEN_H
