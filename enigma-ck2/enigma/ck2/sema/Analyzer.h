#ifndef ENIGMA_CK2_SEMA_ANALYZER_H
#define ENIGMA_CK2_SEMA_ANALYZER_H

namespace enigma { 

namespace ast { class Assignment; }

namespace ck2 { 
namespace sema { 

class Analyzer
{
public:
    virtual ~Analyzer() { }
    virtual void Process(const ast::Assignment& node) = 0;
};

} // namespace sema
} // namespace ck2
} // namespace enigma

#endif // ENIGMA_CK2_SEMA_ANALYZER_H
