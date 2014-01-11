#ifndef ASTVIEWER_H
#define ASTVIEWER_H

#include <QMainWindow>
#include <memory>

class AstViewer : public QMainWindow
{
    Q_OBJECT

public:
    AstViewer(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    virtual ~AstViewer();

private slots:
    void on_actionOpen_triggered();
    void on_actionCloseFile_triggered(); 
    void on_buttonSearch_clicked();
    void fileSelected(const QString& filename);
    void fileLoaded();

private:
    class Data;
    std::unique_ptr<Data> d;
};

#endif // ASTVIEWER_H
