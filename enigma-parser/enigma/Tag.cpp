#include "enigma/Tag.h"

#include <cassert>
#include <QRegExp>

namespace enigma
{

Tag::Tag()
{ }

Tag::Tag(const QString& str, bool quoted) :
    m_tag(str), m_quoted(quoted)
{ }

bool Tag::isValid() const
{
    return !m_tag.isNull();
}

QString Tag::tag() const
{
    assert(isValid());

    return m_tag;
}

Tag Tag::parse(const QString& str)
{
    if ((str.count() != 3) && (str.count() != 5))
    {
        return Tag();
    }

    QString copy(str);

    if (str.count() == 5)
    {
        if (str[0] != '"')
        {
            return Tag();
        }
        if (str[4] != '"')
        {
            return Tag();
        }

        copy.remove('"');
    }

    if (QRegExp("([A-Z]{3}|---)").exactMatch(copy))
    {
        return Tag(copy);
    }

    return Tag();
}

QString Tag::toString() const
{
    return m_tag;
}

} // namespace enigma
