#include "enigma/ast/Node.h"

#include <cassert>

#include "enigma/ast/Leaf.h"
#include "enigma/ast/Assignment.h"
#include "enigma/ast/AssignmentList.h"
#include "enigma/ast/ValueList.h"
#include "enigma/visitors/Visitor.h"
#include "enigma/tokens/Token.h"
#include "enigma/Date.h"

namespace enigma
{
namespace ast
{

class Node::StreamVisitor : public visitors::ConstVisitor
{
public:
    StreamVisitor(const Node& node)
    {
        node.accept(*this);
    }

    virtual void visit(const Leaf& node)
    {
        /*! \todo Throw a proper exception. */
        assert(node.m_stream_idx == 0);
            
        value = node.token().value();
        ++node.m_stream_idx;
    }

    virtual void visit(const Assignment& node)
    {
        /*! \todo Throw a proper exception. */
        assert(node.m_stream_idx < node.count());
        node[node.m_stream_idx++].accept(*this);
    }

    virtual void visit(const AssignmentList& node)
    {
        /*! \todo Throw a proper exception. */
        assert(node.m_stream_idx < node.count());
        node[node.m_stream_idx++].accept(*this);
    }

    virtual void visit(const ValueList& node)
    {
        assert(node.m_stream_idx < node.count());
        node[node.m_stream_idx++].accept(*this);
    }

    QVariant value;
};

const Node& operator>>(const Node& node, QString& value)
{
    Node::StreamVisitor v(node);

    if (v.value.canConvert(QVariant::String))
    {
        value = v.value.toString();
    }

    return node;
}

const Node& operator>>(const Node& node, int& value)
{
    Node::StreamVisitor v(node);

    if (v.value.canConvert(QVariant::LongLong))
    {
        value = v.value.toLongLong();
    }

    return node;
}

const Node& operator>>(const Node& node, double& value)
{
    Node::StreamVisitor v(node);

    if (v.value.canConvert(QVariant::Double))
    {
        value = v.value.toDouble();
    }
    
    return node;
}

const Node& operator>>(const Node& node, bool& value)
{
    Node::StreamVisitor v(node);

    if (v.value.canConvert(QVariant::Bool))
    {
        value = v.value.toBool();
    }
    
    return node;
}

const Node& operator>>(const Node& node, Date& date)
{
    QString str;
    
    node >> str;

    Date node_date = Date::parse(str);
    if (node_date.isValid())
    {
        date = node_date;
    }

    return node;
}


} // namespace ast
} // namespace enigma
