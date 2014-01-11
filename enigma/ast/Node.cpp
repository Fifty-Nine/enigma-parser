#include "enigma/ast/Node.h"

#include <cassert>

namespace enigma
{
namespace ast
{

Node::~Node()
{
}

const Node& Node::at(int idx) const 
{
	(void)idx;
	assert(false);
	return *(const Node*)0;
}

Node& Node::at(int idx) 
{
	(void)idx;
	assert(false);
	return *(Node*)0;
}

} // namespace ast
} // namespace enigma
