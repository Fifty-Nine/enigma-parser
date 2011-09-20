#ifndef NODE_UTILS_H
#define NODE_UTILS_H

#include <QString>

namespace enigma { namespace ast { class Node; } }

/*! Convert a node into a user-friendly string representation. */
QString toString(const enigma::ast::Node& node);


#endif // NODE_UTILS_H
