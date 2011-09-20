#include "AstViewer.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AstViewer w;
	w.show();
	return a.exec();
}
