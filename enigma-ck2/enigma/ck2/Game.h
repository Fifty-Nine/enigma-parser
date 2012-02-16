#ifndef ENIGMA_CK2_GAME_H
#define ENIGMA_CK2_GAME_H

#include <QHash>
#include <memory>

#include "enigma/ck2/Character.h"

namespace enigma {

namespace ast { class Node; }

namespace ck2 {

/*! This class holds information about an analyzed CK2 save game. */
class Game 
{
public:
    /*! Constructor.
     *  \param[in] root A pointer to the root node for the game. */
    Game(ast::Node *root);

    /*! Destructor. */
    virtual ~Game();

    /*! Get the character with the given ID.
     *  \param[in] id The character's ID. 
     *  \return A pointer to the character, or NULL if none with that ID. */
    Character* character(Character::Id id);

    /*! Get the character with the given ID.
     *  \param[in] id The character's ID. 
     *  \return A pointer to the character, or NULL if none with that ID. */
    const Character* character(Character::Id id) const;

private:
    typedef QHash<Character::Id, Character*> CharacterMap;
    CharacterMap m_characters;
};

} // namespace ck2
} // namespace enigma

#endif // ENIGMA_CK2_GAME_H
