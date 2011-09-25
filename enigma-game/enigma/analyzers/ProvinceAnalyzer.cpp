#include "enigma/analyzers/ProvinceAnalyzer.h"

#include "enigma/ast/Assignment.h"
#include "enigma/Game.h"
#include "enigma/Province.h"

namespace enigma
{
namespace analyzers
{

void ProvinceAnalyzer::analyze(Game& game, const ast::Assignment& node)
{
    Province::Id id;
    node >> id;

    /// \todo For now, just make sure the province is created.
    (void)game.province(id);
}

} // namespace analyzers
} // namespace enigma
