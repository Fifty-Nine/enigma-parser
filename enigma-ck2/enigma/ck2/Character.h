#ifndef ENIGMA_CK2_CHARACTER_H
#define ENIGMA_CK2_CHARACTER_H
#pragma once

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

private:
    Id m_id;
};

} // namespace ck2
} // namespace enigma

#endif // ENIGMA_CK2_CHARACTER_H
