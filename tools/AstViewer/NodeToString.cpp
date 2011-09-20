#include "NodeToString.h"

#include "enigma/ast/Leaf.h"
#include "enigma/ast/Assignment.h"
#include "enigma/ast/AssignmentList.h"
#include "enigma/ast/ValueList.h"
#include "enigma/tokens/Token.h"
#include "enigma/visitors/Visitor.h"

ToString::ToString(const enigma::ast::Node& node)
{
    node.accept(*this);
}

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

