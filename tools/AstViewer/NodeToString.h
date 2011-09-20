#ifndef NODE_TO_STRING_H
#define NODE_TO_STRING_H

#include <QVariant>
#include <QString>

#include "enigma/ast/Node.h"
#include "enigma/visitors/Visitor.h"

/*! A functor that gets a string representation of a node. */
class ToString : private enigma::visitors::NullVisitor
{
public:
    /*! Constructs a visitor for the given node. */
    ToString(const enigma::ast::Node& node);

    /*! Get the data as a QString. */
    operator QString() const { return data; }
    /*! Get the data as a QVariant. */
    operator QVariant() const { return data; }

private:
    void visit(const enigma::ast::Leaf& node);
    void visit(const enigma::ast::Assignment& node);
    void visit(const enigma::ast::AssignmentList& node);
    void visit(const enigma::ast::ValueList& node);

private:
    QString data;
};

inline QString toString(const enigma::ast::Node& node) 
{ return ToString(node); }

#endif // NODE_TO_STRING_H
