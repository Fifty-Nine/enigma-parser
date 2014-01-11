#include "enigma/exceptions/UnmatchedInputException.h"

namespace enigma
{
namespace exceptions
{

UnmatchedInputException::UnmatchedInputException(
    const Location& loc, const QString& input) : 
    Exception(loc, buildMessage(loc, input))
{
}

UnmatchedInputException *UnmatchedInputException::clone() const
{
	return new UnmatchedInputException(*this);
}

QString UnmatchedInputException::buildMessage(
    const Location& loc, const QString& input)
{
    QString format("Unmatched input \"%1\" at %2:%3");

    format = format.arg(input);
    format = format.arg(loc.line);
    format = format.arg(loc.column);

    return format;
}

} // namespace exceptions
} // namespace enigma
