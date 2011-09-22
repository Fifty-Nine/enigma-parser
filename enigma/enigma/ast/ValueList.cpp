#include "enigma/ast/ValueList.h"
#include "enigma/visitors/Visitor.h"

namespace enigma
{
namespace ast
{

namespace
{
QList<Node*> convertList(const QList<Value*>& list)
{
    QList<Node*> result;
    for (int i = 0; i < list.count(); ++i)
    {
        result.append( list[i] );
    }
    return result;
}
} // namespace

ValueList::ValueList(QList<Value*>& list) : 
    List(NodeType::ValueList, convertList(list))
{
    list.clear();
}

ValueList::ValueList(QList<Value*>&& list) : 
    List(NodeType::ValueList, convertList(list))
{
}

ValueList::ValueList(QList<Node*>& list) : 
    List(NodeType::ValueList, list)
{
}

ValueList *ValueList::clone() const
{
    QList<Node*> copy;
    for (int i = 0; i < m_list.count(); ++i)
    {
        copy << m_list[i]->clone();
    }

    return new ValueList(copy);
}

const Value& ValueList::at(int i) const
{
    return static_cast<const Value&>(List::at(i));
}

Value& ValueList::at(int i) 
{
    return static_cast<Value&>(List::at(i));
}

void ValueList::accept(visitors::Visitor& visitor)
{
    visitor.visit(*this);
}

void ValueList::accept(visitors::ConstVisitor& visitor) const
{
    visitor.visit(*this);
}

} // namespace ast
} // namespace enigma
