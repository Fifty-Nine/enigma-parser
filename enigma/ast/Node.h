#ifndef ENIGMA_AST_NODE_H
#define ENIGMA_AST_NODE_H
#pragma once

#include <boost/noncopyable.hpp>
#include <memory>
#include <QString>

#include "enigma/util/Enumeration.h"

namespace enigma
{

namespace visitors { class Visitor; }

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

class Node : boost::noncopyable
{
public:
    virtual ~Node();

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
    virtual void accept(visitors::Visitor& visitor) const = 0;

    virtual int count() const { return 0; }
    virtual const Node& at(int idx) const;
    virtual Node& at(int idx);

    inline const Node& operator[](int idx) const { return at(idx); }
    inline Node& operator[](int idx) { return at(idx); }


protected:
    Node(NodeType type) : 
        m_type(type), m_parent(NULL), m_parent_idx(-1) { }

private:
    const NodeType m_type;
    Node *m_parent;
    int m_parent_idx;
};

class Value : public Node
{
public:
    virtual Value *clone() const = 0;

protected:
    Value(NodeType type) : 
        Node(type) { }
};

} // namespace ast
} // namespace enigma

#endif // ENIGMA_AST_NODE_H
