#include "enigma/tokens/TagToken.h"

namespace enigma
{
namespace tokens
{

TagToken::TagToken(const QString& tag, bool stringify, const Location& loc) :
    StringToken(TokenType::Tag, tag, stringify, loc)
{
}

TagToken *TagToken::clone() const
{
    return new TagToken(m_value, m_stringify, location());
}

} // namespace tokens
} // namespace enigma

