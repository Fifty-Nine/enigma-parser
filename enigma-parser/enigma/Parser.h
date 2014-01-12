#ifndef ENIGMA_PARSER_H
#define ENIGMA_PARSER_H

#include <boost/noncopyable.hpp>
#include <memory>
#include "enigma/FilePos.h"
#include "enigma/ast/NodePtrs.h"

namespace enigma
{

class Lexer;

class Parser : boost::noncopyable
{
public:
    Parser(std::unique_ptr<Lexer> lexer);
    ~Parser();

    FilePos currentPos() const;

    typedef std::function<void (ast::NodePtr)> Callback;
    ast::ValueListPtr parse();
    ast::ValueListPtr parse(Callback cb);

private:
    class Data;
    std::unique_ptr<Data> d;
};

} // namespace enigma

#endif // ENIGMA_PARSER_H
