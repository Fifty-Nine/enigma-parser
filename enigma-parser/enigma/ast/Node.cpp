#include "enigma/ast/Node.h"

#include <cassert>

namespace enigma
{
namespace ast
{

Node::~Node()
{
}

NodePtr Node::at_impl(int idx) const 
{
    (void)idx;
    assert(false);
    return NodePtr();
}

} // namespace ast
} // namespace enigma
