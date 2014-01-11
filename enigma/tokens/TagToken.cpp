#include "enigma/tokens/TagToken.h"

namespace enigma
{
namespace tokens
{

TagToken::TagToken(const QString& tag, bool stringify) :
    StringToken(TokenType::Tag, tag, stringify)
{
}

TagToken *TagToken::clone() const
{
    return new TagToken(m_value, m_stringify);
}

} // namespace tokens
} // namespace enigma

