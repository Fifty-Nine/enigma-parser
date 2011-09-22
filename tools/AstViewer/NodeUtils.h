#ifndef NODE_UTILS_H
#define NODE_UTILS_H

#include <QString>
#include <QVariant>

namespace enigma { namespace ast { class Node; } }

/*! Convert a node into a user-friendly string representation. */
QString toString(const enigma::ast::Node& node);

/*! Get the value of a node, if applicable. */
QVariant value(const enigma::ast::Node& node);

/*! Try to set the value of a node, if applicable.
 *  \return True if the value was set. */
bool setValue(enigma::ast::Node& node, const QVariant& value);


#endif // NODE_UTILS_H
