#ifndef ENIGMA_AST_VALUE_LIST_H
#define ENIGMA_AST_VALUE_LIST_H

#include <QList>

#include "enigma/ast/Node.h"

namespace enigma
{
namespace ast
{

class Value;

class ValueList : public Value 
{
public:
    ValueList(QList<ValuePtr>& list, FileSpan span);
    ValueList(QList<ValuePtr>&& list, FileSpan span);

    virtual int count() const { return m_list.count(); }
    virtual ValueList *clone() const;
    virtual void accept(visitors::Visitor& visitor);
    virtual void accept(visitors::ConstVisitor& visitor) const;

    inline ValuePtr at(int i) const
        { return m_list.at(i); }
    inline ValuePtr operator[](int i) const 
        { return at(i); }

    ValuePtr operator[](const QString& key) const;

protected:
    virtual NodePtr at_impl(int idx) const { return m_list.at(idx); }

private:
    void reparent();

    QList<ValuePtr> m_list;
};

} // namespace ast
} // namespace enigma

#endif // ENIGMA_AST_VALUE_LIST_H
