#ifndef ENIGMA_AST_LIST_H
#define ENIGMA_AST_LIST_H
#pragma once

#include <QList>

#include "enigma/ast/Node.h"

namespace enigma
{
namespace ast 
{

class List : public Value
{
public:
    virtual ~List();
    
    virtual int count() const { return m_list.count(); }
    virtual const Node& at(int idx) const { return *m_list.at(idx); }
    virtual Node& at(int idx) { return *m_list.at(idx); }

protected:
    List(NodeType type, QList<NodePtr>& list, FileSpan span);
    List(NodeType type, QList<NodePtr>&& list, FileSpan span);

    QList<NodePtr> m_list;

private:
    void reparent();
};

} // namespace ast 
} // namespace enigma

#endif // ENIGMA_AST_LIST_H
