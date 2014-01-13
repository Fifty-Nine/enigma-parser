#include "enigma/ck2/sema/CharactersAnalyzer.h"

#include <cassert>
#include <QVariant>

#include "enigma/ast/Assignment.h"
#include "enigma/ast/Leaf.h"
#include "enigma/ast/List.h"
#include "enigma/ck2/Character.h"
#include "enigma/ck2/Game.h"

namespace enigma { 
namespace ck2 { 
namespace sema { 

CharactersAnalyzer::CharactersAnalyzer(Game& game) : 
    m_game(game)
{
}

void CharactersAnalyzer::Process(const ast::Assignment& node)
{
    if (node.left()->toString() != "character")
    {
        return;
    }

    ast::ListPtr right = 
        std::dynamic_pointer_cast<ast::List>(node.right());

    /// \todo Throw exception.
    assert(right);

    for (int i = 0; i < right->count(); ++i)
    {
        ast::Assignment *assignment = dynamic_cast<ast::Assignment*>(
            right->at(i).get());
        if (assignment)
        {
            ProcessCharacter(*assignment);
        }
    }
    
}

void CharactersAnalyzer::ProcessCharacter(const ast::Assignment& node)
{
    Character::Id id = node.left()->value().toInt();

    const ast::List& table = 
        *node.right()->cast<ast::List>();

    Character *char_p(m_game.character(id));

    const ast::Leaf *birth_name = table["birth_name"]->cast<ast::Leaf>();
    char_p->setBirthName(birth_name->toString());
}

} // namespace sema
} // namespace ck2
} // namespace enigma

