#ifndef ENIGMA_FILE_READER_H
#define ENIGMA_FILE_READER_H

#include <QObject>

#include <memory>

class QProgressBar;

namespace enigma
{

namespace ast { class AssignmentList; }

class FileReader : public QObject
{
	Q_OBJECT;
public:
	FileReader(QObject *parent=NULL);
	virtual ~FileReader();

	std::unique_ptr<ast::AssignmentList> readFile(const QString& file);

	void setProgressBar(QProgressBar *bar);

signals:
	void progressChanged(int progress);

private:
	QProgressBar *bar;
};

} // namespace enigma

#endif // ENIGMA_FILE_READER_H