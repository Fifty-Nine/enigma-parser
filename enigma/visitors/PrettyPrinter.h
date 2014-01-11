#ifndef ENIGMA_VISITORS_PRETTY_PRINTER_H
#define ENIGMA_VISITORS_PRETTY_PRINTER_H
#pragma once

#include "enigma/visitors/Visitor.h"

#include <memory>

class QIODevice;

namespace enigma
{
namespace visitors
{

class PrettyPrinter : public Visitor
{
public:
	PrettyPrinter(std::unique_ptr<QIODevice> output);
	virtual ~PrettyPrinter();

	virtual void visit(const ast::Leaf& node);
	virtual void visit(const ast::Assignment& node);
	virtual void visit(const ast::ValueList& node);
	virtual void visit(const ast::AssignmentList& node);

private:
	class Data;
	std::unique_ptr<Data> d;
};

}
}

#endif // ENIGMA_VISITORS_PRETTY_PRINTER_H
