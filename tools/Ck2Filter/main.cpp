#include <QList>
#include <QFile>
#include <QString>
#include <cstdio>
#include "enigma/ast/ValueList.h"
#include "enigma/exceptions/Exception.h"
#include "enigma/File.h"
#include "enigma/Lexer.h"
#include "enigma/Parser.h"
#include "enigma/visitors/PrettyPrinter.h"

int main()
{
    std::unique_ptr<QFile> input(new QFile);
    input->open(stdin, QFile::ReadOnly);

    std::unique_ptr<enigma::Lexer> lexer(new enigma::Lexer(std::move(input)));
    enigma::Parser parser(std::move(lexer));
  
    enigma::ast::ValueListPtr list;
    try
    {
        list = parser.parse();
    }
    catch (enigma::exceptions::Exception& ex)
    {
        QString format = "Error while parsing file: %1";
        format = format.arg(ex.what());
        printf("%s\n", qPrintable(format));
        return 1;
    }

    std::unique_ptr<QFile> output(new QFile);
    output->open(stdout, QFile::WriteOnly);

    output->write("CK2txt\r\n");

    enigma::visitors::PrettyPrinter pp(std::move(output));
    list->accept(pp);
}


