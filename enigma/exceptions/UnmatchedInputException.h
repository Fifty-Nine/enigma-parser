#ifndef ENIGMA_EXCEPTIONS_UNMATCHED_INPUT_EXCEPTION_H
#define ENIGMA_EXCEPTIONS_UNMATCHED_INPUT_EXCEPTION_H
#pragma once

#include "enigma/exceptions/Exception.h"

namespace enigma
{
namespace exceptions
{

/*! Exception thrown when an unexpected character is encountered. */
class UnmatchedInputException : public Exception
{
public:
    /*! Construct an exception with the given location and
     *  the specified unmatched input. 
     *  \param [in] loc Location where the input was encountered.
     *  \param [in] input The unmatched input. */
    UnmatchedInputException(const Location& loc, const QString& input);

    virtual void raise() { throw this; }
	virtual UnmatchedInputException *clone() const;

private:
    static QString buildMessage(const Location& loc, const QString& input);
};

} // namespace exceptions
} // namespace enigma
#endif // ENIGMA_EXCEPTIONS_UNMATCHED_INPUT_EXCEPTION_H
