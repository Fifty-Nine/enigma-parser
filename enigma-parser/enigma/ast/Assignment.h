#ifndef ENIGMA_AST_ASSIGNMENT_H
#define ENIGMA_AST_ASSIGNMENT_H

#include "enigma/ast/Node.h"

namespace enigma
{
namespace ast
{

class Leaf;

class Assignment : public Node
{
public:
    /*! Construct an assignment node with the given left- and right-hand 
     *  sides. */
    Assignment(LeafPtr left, ValuePtr right);
    virtual ~Assignment();

    virtual Assignment *clone() const;
    virtual void accept(visitors::Visitor& visitor);
    virtual void accept(visitors::ConstVisitor& visitor) const;

    LeafPtr left() const { return m_left; }
    ValuePtr right() const { return m_right; }

    virtual int count() const { return 2; }

    inline ValuePtr at(int i) const
        { return std::static_pointer_cast<Value>(at_impl(i)); }
    inline ValuePtr operator[](int i) const 
        { return at(i); }

protected:
    virtual NodePtr at_impl(int idx) const;

private:
    Assignment(Leaf *left, Value *right);
    void reparent();

    LeafPtr m_left;
    ValuePtr m_right;
};

} // namespace ast
} // namespace enigma

#endif // ENIGMA_AST_ASSIGNMENT_H
