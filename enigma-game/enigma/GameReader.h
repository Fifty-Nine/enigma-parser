#ifndef ENIGMA_GAME_READER_H
#define ENIGMA_GAME_READER_H
#pragma once

#include <boost/noncopyable.hpp>
#include <memory>

class QRegExp;

namespace enigma
{

class Game;
namespace analyzers { class Analyzer; }
namespace ast { class AssignmentNode; }

/*! This class is used to analyze a parsed AST from a save
 *  game and store the information in a Game object. */
class GameReader : private boost::noncopyable
{
public:
    virtual ~GameReader();

    virtual void analyzeAssignment(const ast::AssignmentNode& node);
    virtual void postProcess();

protected:
    GameReader(Game& game_);

    void addAnalyzer(int prio, std::unique_ptr<analyzers::Analyzer> a);
    
private:
    class Data;
    std::unique_ptr<Data> d;
};

} // namespace enigma

#endif // ENIGMA_GAME_READER_H
