#ifndef ENIGMA_CK2_CHARACTER_H
#define ENIGMA_CK2_CHARACTER_H
#pragma once

#include <QString>

namespace enigma { 
namespace ck2 { 

/*! Represents a character in the game. */
class Character 
{
public:
    /*! The type used to uniquely identify a character. */
    typedef int Id;

    /*! Constructor. 
     *  \param[in] id The character's ID. */
    Character(Id id);

    /*! Destructor. */
    virtual ~Character();

    /*! Get the character's unique identifier.
     *  \return The id. */
    Id id() const;

    /*! Get the character's birth name.
     *  \return The name. */
    QString birthName() const { return m_name; }

    /*! Set the character's birth name. 
     *  \param[in] name The new birth name. */
    void setBirthName(const QString& name) { m_name = name; }

private:
    Id m_id;
    QString m_name;
};

} // namespace ck2
} // namespace enigma

#endif // ENIGMA_CK2_CHARACTER_H
