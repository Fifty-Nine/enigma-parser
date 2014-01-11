#ifndef ENIGMA_PARSER_H
#define ENIGMA_PARSER_H

#include <boost/noncopyable.hpp>
#include <memory>
#include "enigma/File.h"
#include "enigma/FilePos.h"
#include "enigma/ast/NodePtrs.h"

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

    FileType parseHeader();
    File parse();
    ast::AssignmentPtr parseOne();

private:
    class Data;
    std::unique_ptr<Data> d;
};

} // namespace enigma

#endif // ENIGMA_PARSER_H
