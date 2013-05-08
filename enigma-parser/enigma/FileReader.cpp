#include "enigma/FileReader.h"

#include <QFile>
#include <QFileInfo>
#include <QProgressBar>
#include <limits>

#include "enigma/Lexer.h"
#include "enigma/Parser.h"
#include "enigma/ast/AssignmentList.h"

namespace enigma
{

FileReader::FileReader(QObject *parent) : 
    QObject(parent), bar(NULL)
{
}

FileReader::~FileReader()
{
}

std::unique_ptr<ast::AssignmentList> FileReader::readFile(const QString& filename)
{
    std::unique_ptr<QFile> file(new QFile(filename));

    if (!file->open(QIODevice::ReadOnly))
    {
        return std::unique_ptr<ast::AssignmentList>();
    }

    qint64 pfactor = std::numeric_limits<int>::max() / file->size();
    std::unique_ptr<Lexer> lexer(new Lexer(std::move(file)));

    Parser parser(std::move(lexer));

    

    QList<ast::Assignment*> nodes;
    class Guard
    {
    public:
        Guard(QList<ast::Assignment*>& nodes) : 
            nodes(nodes), enabled(true) 
        { }
        ~Guard() 
        { 
            if (enabled) qDeleteAll(nodes);
        }

        void dismiss() { enabled = false; }

    private:
        QList<ast::Assignment*>& nodes;
        bool enabled;
    } g(nodes);

    emit progressChanged(0);

    while (true)
    {
        std::unique_ptr<ast::Assignment> node = parser.parseOne();
    
        if (node)
        {
            nodes.append(node.release());
        }
        else
        {
            emit progressChanged(std::numeric_limits<int>::max());
            break;
        }

        emit progressChanged(pfactor * parser.currentPos().pos);

    }

    g.dismiss();

    FileSpan span(FilePos(0, 1, 1), parser.currentPos());

    return std::unique_ptr<ast::AssignmentList>(
        new ast::AssignmentList(nodes, span));
}

void FileReader::setProgressBar(QProgressBar *bar_)
{
    if (bar)
    {
        disconnect(bar);
    }

    bar = bar_;

    if (bar)
    {
        bar->reset();
        bar->setMinimum(0);
        bar->setMaximum(std::numeric_limits<int>::max());
        bar->setValue(0);

        connect(this, SIGNAL(progressChanged(int)), bar, SLOT(setValue(int)));
    }
}

} // namespace enigma
