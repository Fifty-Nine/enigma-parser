#include "enigma/ast/AssignmentList.h"

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
QList<NodePtr> convertList(const QList<AssignmentPtr>& list)
{
    QList<NodePtr> result;
    for (int i = 0; i < list.count(); ++i)
    {
        result.append( list[i] );
    }
    return result;
}
} // namespace

AssignmentList::AssignmentList(QList<AssignmentPtr>& list, FileSpan span) : 
    List(NodeType::AssignmentList, convertList(list), span)
{
    list.clear();
}

AssignmentList::AssignmentList(QList<AssignmentPtr>&& list, FileSpan span) : 
    List(NodeType::AssignmentList, convertList(list), span)
{
}

AssignmentList::AssignmentList(QList<NodePtr>& list, FileSpan span) : 
    List(NodeType::AssignmentList, list, span)
{
}

AssignmentList *AssignmentList::clone() const
{
    QList<NodePtr> copy;
    for (int i = 0; i < m_list.count(); ++i)
    {
        copy << NodePtr( m_list[i]->clone() );
    }

    return new AssignmentList(copy, location());
}

void AssignmentList::accept(visitors::Visitor& visitor)
{
    visitor.visit(*this);
}

void AssignmentList::accept(visitors::ConstVisitor& visitor) const
{
    visitor.visit(*this);
}

ValuePtr AssignmentList::operator[](const QString& key) const
{
    for (int i = 0; i < count(); ++i)
    {
        AssignmentPtr node = at(i);
        if (node->left()->token().toString() == key)
        {
            return node->right();
        }
    }

    return NULL;
}

} // namespace ast
} // namespace enigma
