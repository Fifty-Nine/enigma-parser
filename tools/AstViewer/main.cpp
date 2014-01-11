#include "AstViewer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AstViewer w;
    w.show();
    return a.exec();
}
