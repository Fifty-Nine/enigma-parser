#include "enigma/ck2/Game.h"

namespace enigma {
namespace ck2 {

Game::Game(ast::Node *root)
{
    (void)root;
}

Game::~Game()
{
    qDeleteAll( m_characters );
}

Character *Game::character(Character::Id id)
{
    CharacterMap::const_iterator it = m_characters.find( id );
    return ( it != m_characters.end() ) ? it.value() : NULL;
}

const Character *Game::character(Character::Id id) const
{
    CharacterMap::const_iterator it = m_characters.find( id );
    return ( it != m_characters.end() ) ? it.value() : NULL;
}

} // namespace ck2
} // namespace enigma
