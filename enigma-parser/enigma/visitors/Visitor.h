#ifndef ENIGMA_AST_VISITOR_H
#define ENIGMA_AST_VISITOR_H

namespace enigma
{

namespace ast
{
class Leaf;
class Assignment;
class ValueList;
}

namespace visitors
{

class Visitor
{
public:
    virtual ~Visitor() { }
    virtual void visit(ast::Leaf& node) = 0;
    virtual void visit(ast::Assignment& node) = 0;
    virtual void visit(ast::ValueList& node) = 0;
};

class ConstVisitor
{
public:
    virtual ~ConstVisitor() { }
    virtual void visit(const ast::Leaf& node) = 0;
    virtual void visit(const ast::Assignment& node) = 0;
    virtual void visit(const ast::ValueList& node) = 0;
};

/*! A visitor that does nothing.
 *  Useful for defining visitors that only handle 
 *  a subset of the possible node types. */
class NullVisitor : public Visitor
{
public:
    virtual void visit(ast::Leaf&) { }
    virtual void visit(ast::Assignment&) { }
    virtual void visit(ast::ValueList&) { }
};

class NullConstVisitor : public ConstVisitor
{
public:
    virtual void visit(const ast::Leaf&) { }
    virtual void visit(const ast::Assignment&) { }
    virtual void visit(const ast::ValueList&) { }
};

} // namespace visitors
} // namespace enigma

#endif // ENIGMA_AST_VISITOR_H
