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
    AssignmentList(QList<Assignment*>& list);
    AssignmentList(QList<Assignment*>&& list);
 
    virtual AssignmentList *clone() const;
    virtual void accept(visitors::Visitor& visitor);
    virtual void accept(visitors::ConstVisitor& visitor) const;

    const Value* operator[](const QString& key) const;
    virtual const Assignment& at(int i) const;
    virtual Assignment& at(int i);
    
    inline const Assignment& operator[](int i) const { return at(i); }
    inline Assignment& operator[](int i) { return at(i); }

private:
    AssignmentList(QList<Node*>& list);
};

} // namespace ast
} // namespace enigma

#endif // ENIGMA_AST_ASSIGNMENT_LIST_H
