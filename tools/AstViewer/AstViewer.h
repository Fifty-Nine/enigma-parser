#ifndef ASTVIEWER_H
#define ASTVIEWER_H

#include <QtGui/QMainWindow>
#include <memory>

class AstViewer : public QMainWindow
{
	Q_OBJECT

public:
	AstViewer(QWidget *parent = 0, Qt::WFlags flags = 0);
	virtual ~AstViewer();

private slots:
	void on_actionOpen_activated();
	void fileSelected(const QString& filename);
	void fileLoaded();

private:
	class Data;
	std::unique_ptr<Data> d;
};

#endif // ASTVIEWER_H
