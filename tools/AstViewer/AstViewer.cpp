#include "AstViewer.h"

#include <QFileDialog>
#include <QFutureWatcher>
#include <QMessageBox>
#include <QProgressBar>
#include <QtConcurrentRun>

#include "AstModel.h"
#include "enigma/ast/AssignmentList.h"
#include "enigma/exceptions/Exception.h"
#include "enigma/FileReader.h"
#include "ui_AstViewer.h"

using namespace enigma;
using enigma::ast::AssignmentList;

class AstViewer::Data
{
public:
    Data(AstViewer *parent_, Ui::AstViewer *ui_) : 
        parent(parent_), ui(ui_), dialog(parent), watcher(parent), model(parent)
    {
        ui->setupUi(parent);

        ui->treeView->setModel(&model);

        QList<QString> filters;
        filters << "All Paradox Files (*.txt *.eu3 *.v2 *.hoi3 *.sgu *.eug)";
        filters << "Europa Universalis III Games (*.eu3)";
        filters << "Victoria II Games (*.v2)";
        filters << "Hearts of Iron III Games (*.hoi3)";
        filters << "Sengoku Games (*.sgu)";
        filters << "Old Paradox save games (*.eug)";
        filters << "All files (*.*)";
        dialog.setNameFilters(filters);

        connect(&dialog, SIGNAL(fileSelected(QString)), 
            parent, SLOT(fileSelected(QString)));
        connect(&watcher, SIGNAL(finished()), parent, SLOT(fileLoaded()));

        QProgressBar *bar = new QProgressBar(parent);
        ui->statusBar->addPermanentWidget(bar);
        reader.setProgressBar(bar);
    }

    static ast::AssignmentList *readFile(Data *d, const QString& file)
    {
        try
        {
            return d->reader.readFile(file).release();
        } 
        catch (exceptions::Exception& ex)
        {
            QString format = "Error while parsing file \"%1\": %2";
            format = format.arg(file);
            format = format.arg(ex.what());
            QMessageBox::information(d->parent, d->parent->tr("Error"), format);
        }
        return NULL;
    }

    AstViewer *parent;
    std::unique_ptr<Ui::AstViewer> ui;
    QFileDialog dialog;
    QFutureWatcher<AssignmentList*> watcher;
    AstModel model;
    enigma::FileReader reader;
    std::unique_ptr<AssignmentList> tree;
};

AstViewer::AstViewer(QWidget *parent, Qt::WFlags flags) : 
    QMainWindow(parent, flags), 
    d(new Data(this, new Ui::AstViewer))
{
}

AstViewer::~AstViewer()
{
}

void AstViewer::on_actionOpen_activated()
{
    d->dialog.show();
}

void AstViewer::on_actionCloseFile_activated()
{
    d->model.setFile(NULL);
    d->tree.reset(NULL);
}

void AstViewer::fileSelected(const QString& filename)
{
    d->model.setFile(NULL);
    d->tree.reset(NULL);
    d->watcher.setFuture(QtConcurrent::run(&Data::readFile, d.get(), filename));
}

void AstViewer::fileLoaded()
{
    AssignmentList* tree = d->watcher.result();
    d->model.setFile(tree);
    d->tree.reset(tree);
}
