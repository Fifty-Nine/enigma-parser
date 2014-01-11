#ifndef ENIGMA_ANALYZER_H
#define ENIGMA_ANALYZER_H

namespace enigma 
{

/*! This is the interface used by the GameReader to analyze assignment nodes
 *  from a savegame. */
class Analyzer
{
public:
    virtual ~Analyzer() { }

    /*! Analyze the given assignment. */
    virtual void analyze(Game& game, const ast::AssignmentNode& node) 
       = 0;
    
    /*! Perform any necessary postprocessing steps on the game. */
    virtual void postProcess(Game& game) = 0;
};

} // namespace enigma 

#endif // ENIGMA_ANALYZER_H
