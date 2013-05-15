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

protected:
    virtual NodePtr at_impl(int idx) const { return m_list.at(idx); }

    List(NodeType type, QList<NodePtr>& list, FileSpan span);
    List(NodeType type, QList<NodePtr>&& list, FileSpan span);

    QList<NodePtr> m_list;

private:
    void reparent();
};

} // namespace ast 
} // namespace enigma

#endif // ENIGMA_AST_LIST_H
