#ifndef ENIGMA_ANALYZERS_PROVINCE_ANALYZER_H
#define ENIGMA_ANALYZERS_PROVINCE_ANALYZER_H

#include "enigma/analyzers/Analyzer.h"

namespace enigma
{
namespace analyzers 
{

class ProvinceAnalyzer : public Analyzer
{
public:
    virtual void analyze(Game& game, const ast::AssignmentNode& node);
};

} // namespace analyzers 
} // namespace enigma

#endif // ENIGMA_ANALYZERS_PROVINCE_ANALYZER_H
