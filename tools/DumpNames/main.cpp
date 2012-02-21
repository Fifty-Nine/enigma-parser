#include <QList>
#include <QString>
#include <cstdio>
#include "enigma/ast/AssignmentList.h"
#include "enigma/exceptions/Exception.h"
#include "enigma/FileReader.h"
#include "enigma/ck2/Game.h"

int main(int argc, const char *argv[])
{
    if ( argc < 2 )
    {
        return 1;
    }

    QString file = argv[1];
    
    enigma::ast::AssignmentList *root = NULL;
    try
    {
        enigma::FileReader reader;
        root = reader.readFile(file).release();
    }
    catch (enigma::exceptions::Exception& ex)
    {
        QString format = "Error while parsing file \"%1\": %2";
        format = format.arg(file);
        format = format.arg(ex.what());
        printf("%s\n", qPrintable(format));
        return 1;
    }
    
    {
        const enigma::ck2::Game g(root);
        QList<const enigma::ck2::Character*> chars(g.characters());

        foreach (const enigma::ck2::Character *c, chars)
        {
            printf("%s\n", qPrintable(c->birthName()));
        }
    }

    delete root;
}


