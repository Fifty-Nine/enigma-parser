#ifndef ENIGMA_FILE_READER_H
#define ENIGMA_FILE_READER_H

#include <QObject>

#include <memory>
#include "enigma/ast/NodePtrs.h"

namespace enigma
{

namespace ast { class AssignmentList; }

class FileReader : public QObject
{
    Q_OBJECT;
public:
    FileReader(QObject *parent=NULL);
    virtual ~FileReader();

    ast::AssignmentListPtr readFile(const QString& file);

signals:
    void progressChanged(int progress);
};

} // namespace enigma

#endif // ENIGMA_FILE_READER_H
