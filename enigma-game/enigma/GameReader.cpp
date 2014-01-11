#include "enigma/GameReader.h"

#include <QMultiMap>

#include "enigma/Game.h"
#include "enigma/analyzers/Analyzer.h"
#include "enigma/ast/Assignment.h"

namespace enigma
{

class GameReader::Data
{
public:
    Data(Game& game_) : 
        game(game_)
    {
    }

    ~Data()
    {
        qDeleteAll(analyzers);
    }

    Game& game;
    QMultiMap<int, analyzers::Analyzer *> analyzers;
};

GameReader::GameReader(Game& game) : 
    d(new Data(game))
{
}

GameReader::~GameReader()
{
}

void GameReader::analyzeAssignment(const ast::Assignment& node)
{
    for (analyzers::Analyzer *analyzer : d->analyzers)
    {
        analyzer->analyze(d->game, node);
    } 
}

void GameReader::postProcess()
{
    for (analyzers::Analyzer *analyzer : d->analyzers)
    {
        analyzer->postProcess(d->game);
    }
}

void GameReader::addAnalyzer(int prio, std::unique_ptr<analyzers::Analyzer> a)
{
    d->analyzers.insert(prio, a.release());
}


} // namespace enigma
