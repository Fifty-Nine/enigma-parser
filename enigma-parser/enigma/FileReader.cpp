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

ast::AssignmentListPtr FileReader::readFile(const QString& filename)
{
    std::unique_ptr<QFile> file(new QFile(filename));

    if (!file->open(QIODevice::ReadOnly))
    {
        return ast::AssignmentListPtr();
    }

    qint64 pfactor = std::numeric_limits<int>::max() / file->size();
    std::unique_ptr<Lexer> lexer(new Lexer(std::move(file)));

    Parser parser(std::move(lexer));

    QList<ast::AssignmentPtr> nodes;

    emit progressChanged(0);

    while (true)
    {
        ast::AssignmentPtr node = parser.parseOne();
    
        if (node)
        {
            nodes.append(node);
        }
        else
        {
            emit progressChanged(std::numeric_limits<int>::max());
            break;
        }

        emit progressChanged(pfactor * parser.currentPos().pos);

    }

    FileSpan span(FilePos(0, 1, 1), parser.currentPos());

    return ast::AssignmentListPtr(
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
