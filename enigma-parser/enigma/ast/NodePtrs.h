#ifndef ENIGMA_AST_NODE_PTRS_H
#define ENIGMA_AST_NODE_PTRS_H

#include <memory>

namespace enigma
{
namespace ast
{

class Node;
typedef std::shared_ptr<Node> NodePtr;

class Leaf;
typedef std::shared_ptr<Leaf> LeafPtr;

class Value;
typedef std::shared_ptr<Value> ValuePtr;

class Assignment;
typedef std::shared_ptr<Assignment> AssignmentPtr;

class ValueList;
typedef std::shared_ptr<ValueList> ValueListPtr;

} // namespace ast
} // namespace enigma

#endif // ENIGMA_AST_NODE_PTRS_H
