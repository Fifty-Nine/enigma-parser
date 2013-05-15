#include "NodeUtils.h"

#include "enigma/ast/Leaf.h"
#include "enigma/ast/Assignment.h"
#include "enigma/ast/AssignmentList.h"
#include "enigma/ast/ValueList.h"
#include "enigma/tokens/Token.h"
#include "enigma/visitors/Visitor.h"

namespace
{
class ToString : private enigma::visitors::NullConstVisitor
{
public:
    /*! Constructs a visitor for the given node. */
    ToString(const enigma::ast::Node& node) : 
        data("{...}")
    {
        node.accept(*this);
    }

    operator QString() const { return data; }

private:
    void visit(const enigma::ast::Leaf& node)
    {
        data = node.token().toString();
    }

    void visit(const enigma::ast::Assignment& node)
    {
        QString format = "%1 = %2";
        format = format.arg(node.left()->token().toString());
        format = format.arg(ToString(*node.right()));

        data = format;
    }

    QString data;
};

class GetValue : private enigma::visitors::NullConstVisitor
{
public:
    GetValue(const enigma::ast::Node& node)
    {
        node.accept(*this);
    }

    operator QVariant() const { return data; }

private:
    void visit(const enigma::ast::Leaf& node)
    {
        data = node.token().value();
    }

    QVariant data;
};

class SetValue : private enigma::visitors::NullVisitor
{
public:
    SetValue(enigma::ast::Node& node, const QVariant& value_) : 
        value(value_), result(false)
    {
        node.accept(*this);
    }

    operator bool() const
    {
        return result;
    }

private:
    void visit(enigma::ast::Leaf& node)
    {
        result = node.token().setValue(value);
    }

    QVariant value;
    bool result;
};

} // namespace

QString toString(const enigma::ast::Node& node)
{
    return ToString(node);
}

QVariant value(const enigma::ast::Node& node)
{
    return GetValue(node);
}

bool setValue(enigma::ast::Node& node, const QVariant& value)
{
    return SetValue(node, value);
}
