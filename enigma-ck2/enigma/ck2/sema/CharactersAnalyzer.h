#ifndef ENIGMA_CK2_SEMA_CHARACTERS_ANALYZER_H
#define ENIGMA_CK2_SEMA_CHARACTERS_ANALYZER_H

#include "enigma/ck2/sema/Analyzer.h"

namespace enigma { 
namespace ck2 { 

class Game;

namespace sema { 

class CharactersAnalyzer : public Analyzer
{
public:
    CharactersAnalyzer(Game& game);

    virtual void Process(const ast::Assignment& node);

private:
    virtual void ProcessCharacter(const ast::Assignment& node);

    Game& m_game;
}; 

} // namespace sema
} // namespace ck2
} // namespace enigma

#endif // ENIGMA_CK2_SEMA_CHARACTERS_ANALYZER_H
