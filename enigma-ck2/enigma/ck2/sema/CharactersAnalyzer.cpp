#include "enigma/ck2/sema/CharactersAnalyzer.h"

#include <cassert>
#include <QVariant>

#include "enigma/ast/Assignment.h"
#include "enigma/ast/AssignmentList.h"
#include "enigma/ast/Leaf.h"
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

    ast::AssignmentListPtr right = 
        std::dynamic_pointer_cast<ast::AssignmentList>(node.right());

    /// \todo Throw exception.
    assert(right);

    for (int i = 0; i < right->count(); ++i)
    {
        ProcessCharacter(*right->at(i));
    }
    
}

void CharactersAnalyzer::ProcessCharacter(const ast::Assignment& node)
{
    Character::Id id = node.left()->value().toInt();

    const ast::AssignmentList& table = 
        *node.right()->cast<ast::AssignmentList>();

    Character *char_p(m_game.character(id));

    const ast::Leaf *birth_name = table["birth_name"]->cast<ast::Leaf>();
    char_p->setBirthName(birth_name->toString());
}

} // namespace sema
} // namespace ck2
} // namespace enigma

