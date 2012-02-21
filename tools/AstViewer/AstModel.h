#ifndef ASTMODEL_H
#define ASTMODEL_H

#include <QAbstractItemModel>
#include <QRegExp>
#include <QSortFilterProxyModel>

#include <boost/function.hpp>
#include <boost/phoenix/core/value.hpp>

#include "enigma/ast/Node.h"

class AstFilterModel;

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
    virtual bool setData(
        const QModelIndex& idx, const QVariant& value, int role=Qt::EditRole);
    virtual QVariant headerData(int section, 
        Qt::Orientation orientation, int role=Qt::DisplayRole) const;
    virtual Qt::ItemFlags flags(const QModelIndex& idx) const;

    typedef boost::function<bool(const enigma::ast::Node&)> Predicate;
    void setHighlight(Predicate pred = boost::phoenix::val(false));

private:
    QVariant displayData(const QModelIndex& idx) const;
    QVariant checkStateData(const QModelIndex& idx) const;
    QVariant bgColorData(const QModelIndex& idx) const;

    enigma::ast::Node *GetNode(const QModelIndex& idx) const;
    enigma::ast::Node *m_root;

    Predicate m_highlight;

    friend class AstFilterModel;
};

#endif // ASTMODEL_H
