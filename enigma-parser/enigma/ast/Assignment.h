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
    Assignment(std::unique_ptr<Leaf> left, std::unique_ptr<Value> right);
    virtual ~Assignment();

    virtual Assignment *clone() const;
    virtual void accept(visitors::Visitor& visitor);
    virtual void accept(visitors::ConstVisitor& visitor) const;

    const Leaf& left() const { return *m_left; }
    Leaf& left() { return *m_left; }
    const Value& right() const { return *m_right; }
    Value& right() { return *m_right; }

    virtual int count() const { return 2; }
    virtual const Value& at(int i) const;
    virtual Value& at(int i); 

    inline const Value& operator[](int i) const { return at(i); }
    inline Value& operator[](int i) { return at(i); }

private:
    Assignment(Leaf *left, Value *right);
    void reparent();

    std::unique_ptr<Leaf> m_left;
    std::unique_ptr<Value> m_right;
};

} // namespace ast
} // namespace enigma

#endif // ENIGMA_AST_ASSIGNMENT_H
