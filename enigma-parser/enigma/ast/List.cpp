#include "enigma/ast/ValueList.h"

#include "enigma/ast/Assignment.h"
#include "enigma/ast/Leaf.h"
#include "enigma/tokens/Token.h"
#include "enigma/visitors/Visitor.h"

namespace enigma
{
namespace ast
{

List::List(QList<ValuePtr>& list, FileSpan span) : 
    Value(NodeType::List, span)
{
    std::swap(list, m_list);
    reparent();
}

List::List(QList<ValuePtr>&& list, FileSpan span) : 
    Value(NodeType::List, span),
    m_list(std::move(list))
{
    reparent();
}

List *List::clone() const
{
    QList<ValuePtr> copy;
    for (int i = 0; i < m_list.count(); ++i)
    {
        copy << ValuePtr( m_list[i]->clone() );
    }

    return new List(copy, location());
}

void List::accept(visitors::Visitor& visitor)
{
    visitor.visit(*this);
}

void List::accept(visitors::ConstVisitor& visitor) const
{
    visitor.visit(*this);
}

ValuePtr List::operator[](const QString& key) const
{
    for (int i = 0; i < count(); ++i)
    {
        ValuePtr node = at(i);
        Assignment *assignment = node->cast<Assignment>();

        if (assignment && assignment->left()->token().toString() == key)
        {
            return assignment->right();
        }
    }

    return NULL;
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
