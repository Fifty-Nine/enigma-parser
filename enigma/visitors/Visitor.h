#ifndef ENIGMA_AST_VISITOR_H
#define ENIGMA_AST_VISITOR_H

namespace enigma
{

namespace ast
{
class Leaf;
class Assignment;
class AssignmentList;
class ValueList;
}

namespace visitors
{

class Visitor
{
public:
	virtual ~Visitor() { }
    virtual void visit(const ast::Leaf& node) = 0;
    virtual void visit(const ast::Assignment& node) = 0;
    virtual void visit(const ast::AssignmentList& node) = 0;
    virtual void visit(const ast::ValueList& node) = 0;
};

} // namespace visitors
} // namespace enigma

#endif // ENIGMA_AST_VISITOR_H
