#include "AstModel.h"

#include <QList>

#include "enigma/ast/Leaf.h"
#include "enigma/ast/Assignment.h"
#include "enigma/ast/AssignmentList.h"
#include "enigma/ast/ValueList.h"
#include "enigma/tokens/Token.h"
#include "enigma/visitors/Visitor.h"

using namespace enigma;
namespace
{
class DisplayData : public visitors::Visitor
{
public:
    DisplayData(const ast::Node *node, int column_) :
        column(column_) 
    { 
        node->accept(*this);
    }

    void visit(const ast::Leaf& node) 
    {
        if (column == 0) data = node.type().toString();
        else if (column == 1) data = node.token().toString();
    }
    void visit(const ast::Assignment& node) 
    { 
        if (column == 0) 
        {
            data = node.type().toString();
            return;
        }

        QString format = "%1 = %2";
        format = format.arg(node.left().token().toString());
        format = format.arg(DisplayData(&node.right(), 1));

        data = format;
    }
    void visit(const ast::AssignmentList& node) 
    { 
        if (column == 0) data = node.type().toString();
        else if (column == 1) data = "{...}";
    }
    void visit(const ast::ValueList& node) 
    {
        if (column == 0) data = node.type().toString();
        else if (column == 1) data = "{...}";
    }

    operator QVariant() const { return data; }
    operator QString() const { return data; }

    int column;
    QString data;
};

}

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
    if (!idx.isValid() || role != Qt::DisplayRole)
    {
        return QVariant();
    }

    return DisplayData(GetNode(idx), idx.column());
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

ast::Node* AstModel::GetNode(const QModelIndex& idx) const
{
    return idx.isValid() ?
        (ast::Node*)idx.internalPointer() : m_root;
}

