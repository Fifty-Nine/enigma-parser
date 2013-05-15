#ifndef ENIGMA_AST_ASSIGNMENT_LIST_H
#define ENIGMA_AST_ASSIGNMENT_LIST_H

#include "enigma/ast/List.h"
#include "enigma/ast/Assignment.h"

namespace enigma
{
namespace ast
{

class Assignment;
class Value;

class AssignmentList : public List
{
public:
    AssignmentList(QList<AssignmentPtr>& list, FileSpan span);
    AssignmentList(QList<AssignmentPtr>&& list, FileSpan span);
 
    virtual AssignmentList *clone() const;
    virtual void accept(visitors::Visitor& visitor);
    virtual void accept(visitors::ConstVisitor& visitor) const;

    ValuePtr operator[](const QString& key) const;
   
    inline AssignmentPtr at(int i) const
        { return std::static_pointer_cast<Assignment>(at_impl(i)); }
    inline AssignmentPtr operator[](int i) const 
        { return at(i); }

private:
    AssignmentList(QList<NodePtr>& list, FileSpan span);
};

} // namespace ast
} // namespace enigma

#endif // ENIGMA_AST_ASSIGNMENT_LIST_H
