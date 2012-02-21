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
QList<Node*> convertList(const QList<Assignment*>& list)
{
    QList<Node*> result;
    for (int i = 0; i < list.count(); ++i)
    {
        result.append( list[i] );
    }
    return result;
}
} // namespace

AssignmentList::AssignmentList(QList<Assignment*>& list) : 
    List(NodeType::AssignmentList, convertList(list))
{
    list.clear();
}

AssignmentList::AssignmentList(QList<Assignment*>&& list) : 
    List(NodeType::AssignmentList, convertList(list))
{
}

AssignmentList::AssignmentList(QList<Node*>& list) : 
    List(NodeType::AssignmentList, list)
{
}

AssignmentList *AssignmentList::clone() const
{
    QList<Node*> copy;
    for (int i = 0; i < m_list.count(); ++i)
    {
        copy << m_list[i]->clone();
    }

    return new AssignmentList(copy);
}

void AssignmentList::accept(visitors::Visitor& visitor)
{
    visitor.visit(*this);
}

void AssignmentList::accept(visitors::ConstVisitor& visitor) const
{
    visitor.visit(*this);
}

Value* AssignmentList::operator[](const QString& key) 
{
    for (int i = 0; i < count(); ++i)
    {
        Assignment& node(at(i));

        if (node.left().token().toString() == key)
        {
            return &node.right();
        }
    }

    return NULL;
}

const Value* AssignmentList::operator[](const QString& key) const
{
    for (int i = 0; i < count(); ++i)
    {
        const Assignment& node(at(i));

        if (node.left().token().toString() == key)
        {
            return &node.right();
        }
    }

    return NULL;
}

const Assignment& AssignmentList::at(int i) const
{
    return static_cast<const Assignment&>(List::at(i));
}

Assignment& AssignmentList::at(int i)
{
    return static_cast<Assignment&>(List::at(i));
}

} // namespace ast
} // namespace enigma
