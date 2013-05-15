#include "enigma/ast/List.h"

namespace enigma
{
namespace ast 
{

List::List(NodeType type, QList<NodePtr>& list, FileSpan span) :
    Value(type, span)
{
    std::swap(list, m_list);
    reparent();
}

List::List(NodeType type, QList<NodePtr>&& list, FileSpan span) : 
    Value(type, span), m_list(std::move(list))
{
    reparent();
}

List::~List()
{
}

void List::reparent()
{
    for (int i = 0; i < m_list.count(); ++i)
    {
        m_list[i]->setParent(this);
        m_list[i]->setParentIdx(i);
    }
}

} // namespace ast 
} // namespace enigma
