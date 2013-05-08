#ifndef ENIGMA_PARSER_H
#define ENIGMA_PARSER_H

#include <boost/noncopyable.hpp>
#include <memory>
#include "enigma/FilePos.h"

namespace enigma
{

class Lexer;
namespace ast 
{ 
    class Assignment;
    class AssignmentList; 
}

class Parser : boost::noncopyable
{
public:
    Parser(std::unique_ptr<Lexer> lexer);
    ~Parser();

    FilePos currentPos() const;

    std::unique_ptr<ast::AssignmentList> parse();
    std::unique_ptr<ast::Assignment> parseOne();

private:
    class Data;
    std::unique_ptr<Data> d;
};

} // namespace enigma

#endif // ENIGMA_PARSER_H
