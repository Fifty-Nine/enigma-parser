#ifndef ASTMODEL_H
#define ASTMODEL_H

#include <QAbstractItemModel>

namespace enigma
{
namespace ast { class Node; }
}

class AstModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    AstModel(QObject *parent);
    virtual ~AstModel();

    void setFile(enigma::ast::Node *file);

    virtual QModelIndex index(
        int row, int column, const QModelIndex& parent=QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex& idx) const;
    virtual int rowCount(const QModelIndex& parent=QModelIndex()) const;
    virtual int columnCount(const QModelIndex& parent=QModelIndex()) const;
    virtual QVariant data(
        const QModelIndex& idx, int role=Qt::DisplayRole) const;
    virtual QVariant headerData(int section, 
        Qt::Orientation orientation, int role=Qt::DisplayRole) const;

private:
    QVariant displayData( const QModelIndex& idx ) const;
    QVariant checkStateData( const QModelIndex& idx ) const;

    enigma::ast::Node *GetNode(const QModelIndex& idx) const;
    enigma::ast::Node *m_root;
};

#endif // ASTMODEL_H
