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
    ToString(const enigma::ast::Node& node) 
    {
        node.accept(*this);
    }

    operator QString() { return data; }

private:
    void visit(const enigma::ast::Leaf& node);
    void visit(const enigma::ast::Assignment& node);
    void visit(const enigma::ast::AssignmentList& node);
    void visit(const enigma::ast::ValueList& node);

    QString data;
};

void ToString::visit(const enigma::ast::Leaf& node)
{
    data = node.token().toString();
}

void ToString::visit(const enigma::ast::Assignment& node)
{
    QString format = "%1 = %2";
    format = format.arg(node.left().token().toString());
    format = format.arg(ToString(node.right()));

    data = format;
}

void ToString::visit(const enigma::ast::AssignmentList&)
{
    data = "{...}";
}

void ToString::visit(const enigma::ast::ValueList&)
{
    data = "{...}";
}
} // namespace

QString toString(const enigma::ast::Node& node)
{
    return ToString(node);
}
