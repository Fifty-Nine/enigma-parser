#include "enigma/ast/Assignment.h"

#include <cassert>

#include "enigma/ast/Leaf.h"
#include "enigma/visitors/Visitor.h"

namespace enigma
{
namespace ast
{

Assignment::Assignment(
    std::unique_ptr<Leaf> left, std::unique_ptr<Value> right) : 
    Node(NodeType::Assignment, left->location() + right->location()),
    m_left(std::move(left)), m_right(std::move(right))
{
    reparent();
}

Assignment::~Assignment()
{
}

Assignment *Assignment::clone() const
{
    return new Assignment(m_left->clone(), m_right->clone());
}

void Assignment::accept(visitors::Visitor& visitor) 
{
    visitor.visit(*this);
}

void Assignment::accept(visitors::ConstVisitor& visitor) const
{
    visitor.visit(*this);
}

const Value& Assignment::at(int i) const
{
    switch (i)
    {
    case 0: return left();
    case 1: return right();
    default:
        assert(false);
        return *(Value*)0;
    }
}

Value& Assignment::at(int i)
{
    switch (i)
    {
    case 0: return left();
    case 1: return right();
    default:
        assert(false);
        return *(Value*)0;
    }
}

Assignment::Assignment(Leaf *left, Value *right) : 
    Node(NodeType::Assignment, (left->location() + right->location())), 
    m_left(left), m_right(right)
{
    reparent();
}

void Assignment::reparent() 
{
    m_left->setParent(this);
    m_left->setParentIdx(0);
    m_right->setParent(this);
    m_right->setParentIdx(1);
}

} // namespace ast
} // namespace enigma
