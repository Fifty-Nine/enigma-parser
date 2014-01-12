#include "enigma/FileReader.h"

#include <QFile>
#include <QFileInfo>
#include <limits>

#include "enigma/Lexer.h"
#include "enigma/Parser.h"
#include "enigma/ast/AssignmentList.h"

namespace enigma
{

FileReader::FileReader(QObject *parent) : 
    QObject(parent)
{
}

FileReader::~FileReader()
{
}

ast::ListPtr FileReader::readFile(const QString& filename)
{
    std::unique_ptr<QFile> file(new QFile(filename));

    if (!file->open(QIODevice::ReadOnly))
    {
        return ast::ListPtr();
    }

    qint64 pfactor = std::numeric_limits<int>::max() / file->size();
    std::unique_ptr<Lexer> lexer(new Lexer(std::move(file)));

    Parser parser(std::move(lexer));

    QList<ast::AssignmentPtr> nodes;

    emit progressChanged(0);

    auto callback = [&](ast::NodePtr) {
        emit progressChanged(pfactor * parser.currentPos().pos);
    };

    ast::ListPtr result = parser.parse(callback);

    emit progressChanged(std::numeric_limits<int>::max());

    return result;
}

} // namespace enigma
