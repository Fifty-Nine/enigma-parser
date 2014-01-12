#include "enigma/ast/ValueList.h"

#include "enigma/ast/Assignment.h"
#include "enigma/ast/Leaf.h"
#include "enigma/tokens/Token.h"
#include "enigma/visitors/Visitor.h"

namespace enigma
{
namespace ast
{

namespace
{
QList<NodePtr> convertList(const QList<ValuePtr>& list)
{
    QList<NodePtr> result;
    for (int i = 0; i < list.count(); ++i)
    {
        result.append( list[i] );
    }
    return result;
}
} // namespace

ValueList::ValueList(QList<ValuePtr>& list, FileSpan span) : 
    List(NodeType::ValueList, convertList(list), span)
{
    list.clear();
}

ValueList::ValueList(QList<ValuePtr>&& list, FileSpan span) : 
    List(NodeType::ValueList, convertList(list), span)
{
}

ValueList::ValueList(QList<NodePtr>& list, FileSpan span) : 
    List(NodeType::ValueList, list, span)
{
}

ValueList *ValueList::clone() const
{
    QList<NodePtr> copy;
    for (int i = 0; i < m_list.count(); ++i)
    {
        copy << NodePtr( m_list[i]->clone() );
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

} // namespace ast
} // namespace enigma
