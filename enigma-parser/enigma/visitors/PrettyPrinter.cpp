#include "enigma/visitors/PrettyPrinter.h"

#include <QIODevice>
#include <QTextStream>

#include "enigma/ast/Leaf.h"
#include "enigma/ast/Assignment.h"
#include "enigma/ast/ValueList.h"
#include "enigma/ast/AssignmentList.h"
#include "enigma/tokens/Token.h"

namespace enigma
{
namespace visitors
{

class PrettyPrinter::Data
{
public:
    Data(std::unique_ptr<QIODevice> output) : 
        m_device(std::move(output)), 
        m_out(m_device.get()),
        m_indent(-1)
    {
        m_out.setCodec("UTF-8");
    }

    void indent()
    {
        indent(m_indent);
    }

    void indent(int depth)
    {
        for (int i = 0; i < depth; ++i)
        {
            m_out << "    ";
        }
    }

    std::unique_ptr<QIODevice> m_device;
    QTextStream m_out;
    int m_indent;
};

PrettyPrinter::PrettyPrinter(std::unique_ptr<QIODevice> output)
    : d(new Data(std::move(output)))
{
}

PrettyPrinter::~PrettyPrinter()
{
    d->m_out << '\n';
}

void PrettyPrinter::visit(const ast::Leaf& node)
{
    d->m_out << node.token().toString();
}

void PrettyPrinter::visit(const ast::Assignment& node)
{
    node.left()->accept(*this);
    d->m_out << "=";
    node.right()->accept(*this);
    d->m_out << "\n";
}

void PrettyPrinter::visit(const ast::AssignmentList& node)
{
    if (d->m_indent >= 0)
    {
        d->m_out << '\n';
        d->indent();
        d->m_out << "{\n";
    }

    ++d->m_indent;

    for (int i = 0; i < node.count(); ++i)
    {
        d->indent();
        node[i]->accept(*this);
    }

    --d->m_indent;
    d->indent();

    if (d->m_indent >= 0)
    {
        d->m_out << '}';
    }
}

void PrettyPrinter::visit(const ast::ValueList& node)
{
    if (d->m_indent >= 0)
    {
        d->m_out << '\n';
        d->indent();
        d->m_out << '{';
    }

    ++d->m_indent;
    d->indent();
    d->m_out << '\n';
    
    for (int i = 0; i < node.count(); ++i)
    {
        node[i]->accept(*this);
        d->m_out << ' ';
    }

    --d->m_indent;

    if (d->m_indent >= 0)
    {
        d->indent();
        d->m_out << '}';
    }
}

} // namespace visitors
} // namespace enigma
