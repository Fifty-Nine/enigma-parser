#ifndef ENIGMA_AST_NODE_H
#define ENIGMA_AST_NODE_H
#pragma once

#include <boost/noncopyable.hpp>
#include <memory>
#include <QString>

#include "enigma/FilePos.h"
#include "enigma/util/Enumeration.h"
#include "enigma/ast/NodePtrs.h"

namespace enigma
{

namespace visitors 
{ 
class Visitor; 
class ConstVisitor; 
}
class Date;

namespace ast
{

struct NodeTypeDef
{
enum Enum
{
    Value,
    Assignment,
    AssignmentList,
    ValueList
};

static QString toString(Enum t)
{
    switch (t)
    {
    case Value: return "Value";
    case Assignment: return "Assignment";
    case AssignmentList: return "AssignmentList";
    case ValueList: return "ValueList";
    }
    return "Unknown";
}
};
typedef util::Enumeration<NodeTypeDef> NodeType;

class Node : 
    public std::enable_shared_from_this<Node>,
    boost::noncopyable
{
public:
    virtual ~Node();

    FileSpan location() const { return m_span; }
    const Node* parent() const { return m_parent; }
    Node *parent() { return m_parent; }
    void setParent(Node *parent) { m_parent = parent; }
    int parentIdx() const { return m_parent_idx; }
    void setParentIdx(int idx) { m_parent_idx = idx; }

    /*! Get the type of the node. */
    NodeType type() const { return m_type; }

    /*! Clone the node. 
     * \returns A copy of the node. The caller takes ownership. */
    virtual Node *clone() const = 0;

    /*! Accept the given visitor, calling the appropriate Visit function. */
    virtual void accept(visitors::Visitor& visitor) = 0;
    virtual void accept(visitors::ConstVisitor& visitor) const = 0;

    virtual int count() const { return 0; }
    inline NodePtr at(int idx) const { return at_impl(idx); }
    inline NodePtr operator[](int idx) const { return at(idx); }

    class StreamVisitor;
    friend class StreamVisitor;

    template<class T> const T* cast() const;
    template<class T> T* cast();

protected:
    Node(NodeType type, FileSpan span) : 
        m_type(type), m_span(span), 
        m_parent(NULL), m_parent_idx(-1), m_stream_idx(0) { }

    virtual NodePtr at_impl(int idx) const;

private:
    const NodeType m_type;
    FileSpan m_span;
    Node *m_parent;
    int m_parent_idx;
    mutable int m_stream_idx;
};

class Value : public Node
{
public:
    virtual Value *clone() const = 0;

protected:
    Value(NodeType type, FileSpan span) : 
        Node(type, span) { }
};

template<class T>
const T* Node::cast() const
{
    return dynamic_cast<const T*>( this );
}

template<class T>
T* Node::cast() 
{
    return dynamic_cast<T*>( this );
}

const Node& operator>>(const Node& node, QString& value);
const Node& operator>>(const Node& node, long long& value);
const Node& operator>>(const Node& node, int& value);
const Node& operator>>(const Node& node, unsigned int& value);
const Node& operator>>(const Node& node, double& value);
const Node& operator>>(const Node& node, bool& value);
const Node& operator>>(const Node& node, Date& date);

} // namespace ast
} // namespace enigma

#endif // ENIGMA_AST_NODE_H
