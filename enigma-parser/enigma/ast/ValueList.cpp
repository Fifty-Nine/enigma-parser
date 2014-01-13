#include "enigma/ast/ValueList.h"

#include "enigma/ast/Assignment.h"
#include "enigma/ast/Leaf.h"
#include "enigma/tokens/Token.h"
#include "enigma/visitors/Visitor.h"

namespace enigma
{
namespace ast
{

ValueList::ValueList(QList<ValuePtr>& list, FileSpan span) : 
    Value(NodeType::ValueList, span)
{
    std::swap(list, m_list);
    reparent();
}

ValueList::ValueList(QList<ValuePtr>&& list, FileSpan span) : 
    Value(NodeType::ValueList, span),
    m_list(std::move(list))
{
    reparent();
}

ValueList *ValueList::clone() const
{
    QList<ValuePtr> copy;
    for (int i = 0; i < m_list.count(); ++i)
    {
        copy << ValuePtr( m_list[i]->clone() );
    }

    return new ValueList(copy, location());
}

void ValueList::accept(visitors::Visitor& visitor)
{
    visitor.visit(*this);
}

void ValueList::accept(visitors::ConstVisitor& visitor) const
{
    visitor.visit(*this);
}

ValuePtr ValueList::operator[](const QString& key) const
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

void ValueList::reparent()
{
    for (int i = 0; i < m_list.count(); ++i)
    {
        m_list[i]->setParent(this);
        m_list[i]->setParentIdx(i);
    }
}

} // namespace ast
} // namespace enigma
