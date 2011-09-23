#ifndef ENIGMA_TAG_H
#define ENIGMA_TAG_H

#include <QString>
#include <QHash>

namespace enigma
{

class Tag 
{
public:
    /*! Constructs an invalid tag. */
    Tag();

    bool isValid() const;
    QString tag() const;

    /*! Parse the given string as a tag value.
     * \param[in] str The string to parse.
     * \return The parsed tag, or an invalid tag if unsuccessful. */
    static Tag parse(const QString& str);

    /*! Get the string representation of this tag. */
    QString toString() const;

private:
    Tag(const QString& str, bool quoted=false);
    QString m_tag;
    bool m_quoted;
};

/*! Hash the given tag. */
inline uint qHash(const Tag& tag)
{
    return qHash(tag.tag());
}

} // namespace enigma

#endif // ENIGMA_TAG_H
