#include "AstModel.h"

#include <boost/phoenix/core/value.hpp>

#include "enigma/ast/Node.h"
#include "enigma/ast/Leaf.h"
#include "NodeUtils.h"

using namespace enigma;

AstModel::AstModel(QObject *parent)
    : QAbstractItemModel(parent), m_root(NULL)
{

}

AstModel::~AstModel()
{

}

void AstModel::setFile(ast::Node *file)
{
    beginResetModel();
    m_root = file;
    endResetModel();
}

QModelIndex AstModel::index(
    int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    return createIndex(row, column, (void*)&GetNode(parent)->at(row));
}

QModelIndex AstModel::parent(const QModelIndex& idx) const
{
    if (!idx.isValid()) return QModelIndex();

    ast::Node *parent = GetNode(idx)->parent();

    if (parent == m_root) return QModelIndex();

    return createIndex(parent->parentIdx(), 0, parent);
}

int AstModel::rowCount(const QModelIndex& parent) const
{
    if (!m_root) return 0;
    return parent.isValid() ? GetNode(parent)->count() : m_root->count();
}

int AstModel::columnCount(const QModelIndex&) const
{
    return 2;
}

QVariant AstModel::data(const QModelIndex& idx, int role) const
{
    if (!idx.isValid())
    {
        return QVariant();
    }

    switch (role)
    {
    case Qt::DisplayRole: return displayData(idx);
    case Qt::CheckStateRole: return checkStateData(idx);
    }

    return QVariant();
}

bool AstModel::setData(const QModelIndex& idx, const QVariant& value, int role)
{
    if (role != Qt::EditRole) return false;

    return setValue(*GetNode(idx), value);
}

QVariant AstModel::headerData(
    int section, Qt::Orientation orientation, int role) const
{
    if ((orientation != Qt::Horizontal) || (role != Qt::DisplayRole))
    {
        return QVariant();
    }

    switch (section)
    {
    case 0: return "Type";
    case 1: return "Data";
    }

    return QVariant();
}

Qt::ItemFlags AstModel::flags(const QModelIndex& idx) const
{
    const ast::Leaf* leaf = dynamic_cast<const ast::Leaf*>( GetNode(idx) );

    Qt::ItemFlags result = Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    if (leaf)
    {
        result |= Qt::ItemIsEditable;
    }

    return result;
}

QVariant AstModel::displayData(const QModelIndex& idx) const
{
    ast::Node& node( *GetNode(idx) );
    if (idx.column() == 0)
    {
        return node.type().toString();
    }
    else
    {
        return toString(node);
    }
}

QVariant AstModel::checkStateData(const QModelIndex& idx) const
{
    if (idx.column() != 1) return QVariant();

    ast::Node& node( *GetNode(idx) );
    
    QVariant val = value(node);

    if (val.type() != QVariant::Bool) return QVariant();

    return val.toBool() ? Qt::Checked : Qt::Unchecked;
}

ast::Node* AstModel::GetNode(const QModelIndex& idx) const
{
    return idx.isValid() ?
        (ast::Node*)idx.internalPointer() : m_root;
}

AstFilterModel::AstFilterModel(QObject *parent) : 
    QSortFilterProxyModel(parent), 
    m_pred(boost::phoenix::val(true))
{
}

AstFilterModel::~AstFilterModel()
{
}

void AstFilterModel::setFilter(Predicate pred)
{
    m_pred = pred;
    invalidateFilter();
}

void AstFilterModel::setSourceModel(AstModel *model)
{
    QSortFilterProxyModel::setSourceModel(model);
}

AstModel* AstFilterModel::sourceModel() const
{
    return static_cast<AstModel*>( QSortFilterProxyModel::sourceModel() );
}

bool AstFilterModel::filterAcceptsRow( int row, const QModelIndex& parent ) 
    const
{
    ast::Node& parent_p = *(sourceModel()->GetNode( parent ));
    ast::Node& node_p = parent_p.at( row );

    return m_pred(node_p);

    (void)row; (void)parent;
    return true;
}
