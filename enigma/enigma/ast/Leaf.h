#ifndef ENIGMA_AST_LEAF_H
#define ENIGMA_AST_LEAF_H
#pragma once

#include "enigma/ast/Node.h"

namespace enigma
{

namespace tokens
{
class StringToken;
class BooleanToken;
class IntegerToken;
class DecimalToken;
class Token;
}

namespace ast
{

class Leaf : public Value
{
public:
    Leaf(std::unique_ptr<tokens::Token> token);
    virtual ~Leaf();

    virtual Leaf *clone() const;
    virtual void accept(visitors::Visitor& visitor) const;

    const tokens::Token& token() const { return *m_token; }

private:
    Leaf(tokens::Token* token);
    const std::unique_ptr<tokens::Token> m_token;
};

} // namespace ast
} // namespace enigma


#endif // ENIGMA_AST_LEAF_H
