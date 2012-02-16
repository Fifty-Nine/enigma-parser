#include "AstViewer.h"

#include <QFileDialog>
#include <QFutureWatcher>
#include <QMessageBox>
#include <QProgressBar>
#include <QtConcurrentRun>

#include "AstModel.h"
#include "enigma/ast/AssignmentList.h"
#include "enigma/ast/Leaf.h"
#include "enigma/ast/ValueList.h"
#include "enigma/exceptions/Exception.h"
#include "enigma/FileReader.h"
#include "enigma/tokens/Token.h"
#include "enigma/visitors/Visitor.h"
#include "ui_AstViewer.h"

using namespace enigma;
using enigma::ast::AssignmentList;

class SearchVisitor : private enigma::visitors::ConstVisitor
{
public:
    SearchVisitor(const QRegExp& regex) : 
        m_regex(regex), m_result( false )
    {
    }

    virtual void visit(const ast::Leaf& node) 
    {
        m_result = m_result || 
            ( m_regex.indexIn( node.token().toString() ) >= 0 );
    }

    virtual void visit(const ast::Assignment& node)
    {
        node.left().accept(*this);
        node.right().accept(*this);
    }

    virtual void visit(const ast::AssignmentList& node) 
    {
        for (int i = 0; i < node.count(); ++i)
        {
            node.at(i).accept(*this);
        }
    }
    virtual void visit(const ast::ValueList& node)
    {
        for (int i = 0; i < node.count(); ++i)
        {
            node.at(i).accept(*this);
        }
    }

    bool operator()(const ast::Node& node)
    {
        m_result = false;
        node.accept(*this);
        return m_result;
    }

private:
    QRegExp m_regex;
    bool m_result;
};

class AstViewer::Data
{
public:
    Data(AstViewer *parent_, Ui::AstViewer *ui_) : 
        parent(parent_), ui(ui_), dialog(parent), watcher(parent), 
        model(parent), filter_model(parent), bar(new QProgressBar(parent))
    {
        ui->setupUi(parent);

        filter_model.setSourceModel(&model);
        ui->treeView->setModel(&filter_model);

        QList<QString> filters;
        filters << "All Paradox Files (*.txt *.eu3 *.ck2 *.v2 *.hoi3 *.sgu *.eug)";
        filters << "Europa Universalis III Games (*.eu3)";
        filters << "Crusader Kings II Games (*.ck2)";
        filters << "Victoria II Games (*.v2)";
        filters << "Hearts of Iron III Games (*.hoi3)";
        filters << "Sengoku Games (*.sgu)";
        filters << "Old Paradox save games (*.eug)";
        filters << "All files (*.*)";
        dialog.setNameFilters(filters);

        connect(&dialog, SIGNAL(fileSelected(QString)), 
            parent, SLOT(fileSelected(QString)));
        connect(&watcher, SIGNAL(finished()), parent, SLOT(fileLoaded()));

        ui->statusBar->addPermanentWidget(bar);
        reader.setProgressBar(bar);
        bar->setVisible(false);
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
    AstFilterModel filter_model;
    enigma::FileReader reader;
    std::unique_ptr<AssignmentList> tree;
    QProgressBar *bar;
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
    d->ui->actionCloseFile->setEnabled(false);
}

void AstViewer::on_buttonSearch_clicked()
{
    QString text( d->ui->searchBox->text() );

    if ( !text.isEmpty() )
    {
        d->filter_model.setFilter( SearchVisitor( QRegExp( text ) ) );
    }
    else
    {
        d->filter_model.setFilter();
    }
}

void AstViewer::fileSelected(const QString& filename)
{
    d->model.setFile(NULL);
    d->tree.reset(NULL);
    d->ui->actionCloseFile->setEnabled(false);
    d->bar->setVisible(true);
    d->watcher.setFuture(QtConcurrent::run(&Data::readFile, d.get(), filename));
}

void AstViewer::fileLoaded()
{
    AssignmentList* tree = d->watcher.result();
    d->model.setFile(tree);
    d->tree.reset(tree);
    d->ui->actionCloseFile->setEnabled(true);
    d->bar->setVisible(false);
}
