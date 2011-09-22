#ifndef ENIGMA_AST_VALUE_LIST_H
#define ENIGMA_AST_VALUE_LIST_H

#include "enigma/ast/List.h"

namespace enigma
{
namespace ast
{

class Value;

class ValueList : public List
{
public:
    ValueList(QList<Value*>& list);
    ValueList(QList<Value*>&& list);

    virtual ValueList *clone() const;
    virtual void accept(visitors::Visitor& visitor);
    virtual void accept(visitors::ConstVisitor& visitor) const;

    virtual const Value& at(int i) const;
    virtual Value& at(int i);

    inline const Value& operator[](int i) const { return at(i); }
    inline Value& operator[](int i) { return at(i); }

private:
    ValueList(QList<Node*>& list);
};

} // namespace ast
} // namespace enigma

#endif // ENIGMA_AST_VALUE_LIST_H
