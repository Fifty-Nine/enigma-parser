#include <QStringList>

#include "enigma/exceptions/ExpectedInputException.h"

namespace enigma
{
namespace exceptions
{

ExpectedInputException::ExpectedInputException(
    const FilePos& loc, const QStringList& expected) : 
    Exception(loc, buildMessage(loc, expected))
{
}

ExpectedInputException *ExpectedInputException::clone() const
{ 
    return new ExpectedInputException(*this); 
}

QString ExpectedInputException::buildMessage(
    const FilePos& loc, const QStringList& expected)
{
    QString format("Expected %1 at %2:%3");
    if (expected.count() == 1)
    {
        format = format.arg(expected[0]);
    }
    else if (expected.count() == 0)
    {
        format = format.arg("nothing");
    }
    else
    {
        format = format.arg("either " + expected.join(" or "));
    }

    format = format.arg(loc.line);
    format = format.arg(loc.column);

    return format;
}

} // namespace exceptions
} // namespace enigma
