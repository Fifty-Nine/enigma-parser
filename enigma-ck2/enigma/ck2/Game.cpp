#include "enigma/ck2/Game.h"

#include "enigma/ast/AssignmentList.h"
#include "enigma/ck2/sema/CharactersAnalyzer.h"

namespace enigma {
namespace ck2 {

typedef QList<sema::Analyzer*> AnalyzerList;
typedef QHash<Character::Id, Character*> CharacterMap;
struct Game::Data
{
    ~Data()
    {
        qDeleteAll(analyzers);
        qDeleteAll(characters);
    }

    AnalyzerList analyzers;
    CharacterMap characters;
};

Game::Game(const ast::AssignmentList *root) : 
    d( new Data )
{
    d->analyzers << new sema::CharactersAnalyzer(*this);

    for (int i = 0; i < root->count(); ++i)
    {
        for (AnalyzerList::iterator it = d->analyzers.begin(); 
            it != d->analyzers.end(); ++it )
        {
            (*it)->Process(*root->at(i));
        }
    }
}

Game::~Game()
{
}

Character *Game::character(Character::Id id)
{
    CharacterMap::const_iterator it = d->characters.find(id);

    if (it != d->characters.end()) return it.value();

    Character *result = new Character(id);
    d->characters[id] = result;

    return result;
}

const Character *Game::character(Character::Id id) const
{
    CharacterMap::const_iterator it = d->characters.find(id);
    return (it != d->characters.end()) ? it.value() : NULL;
}

QList<const Character*> Game::characters() const
{
    QList<Character*> nonconst = d->characters.values();
    QList<const Character*> result;
    result.reserve(nonconst.count());
    std::copy(nonconst.begin(), nonconst.end(), std::back_inserter(result));
    return result;
}

} // namespace ck2
} // namespace enigma
