#include "NodeUtils.h"

#include "enigma/ast/Leaf.h"
#include "enigma/ast/Assignment.h"
#include "enigma/ast/AssignmentList.h"
#include "enigma/ast/ValueList.h"
#include "enigma/tokens/Token.h"
#include "enigma/visitors/Visitor.h"

namespace
{
class ToString : private enigma::visitors::NullVisitor
{
public:
    /*! Constructs a visitor for the given node. */
    ToString(const enigma::ast::Node& node) : 
        data("{...}")
    {
        node.accept(*this);
    }

    operator QString() { return data; }

private:
    void visit(const enigma::ast::Leaf& node)
    {
        data = node.token().toString();
    }

    void visit(const enigma::ast::Assignment& node)
    {
        QString format = "%1 = %2";
        format = format.arg(node.left().token().toString());
        format = format.arg(ToString(node.right()));

        data = format;
    }

    QString data;
};

class GetValue : private enigma::visitors::NullVisitor
{
public:
    GetValue(const enigma::ast::Node& node)
    {
        node.accept(*this);
    }

    void visit(const enigma::ast::Leaf& node)
    {
        data = node.token().value();
    }

    operator QVariant() { return data; }

private:
    QVariant data;
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
