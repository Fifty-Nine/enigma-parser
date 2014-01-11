#ifndef ENIGMA_EXCEPTIONS_EXPECTED_INPUT_EXCEPTION_H
#define ENIGMA_EXCEPTIONS_EXPECTED_INPUT_EXCEPTION_H

#include "enigma/exceptions/Exception.h"

namespace enigma
{
namespace exceptions
{

/*! An exception thrown when we encounter unexpected input. */
class ExpectedInputException : public Exception
{
public:
    /*! Construct a new expected input exception.
     * \param [in] loc The location of the error.
     * \param [in] expected The possible expected options. */
    ExpectedInputException(const Location& loc, const QStringList& expected);

    virtual void raise() { throw this; }
	virtual ExpectedInputException *clone() const;

private:
    static QString buildMessage(
		const Location& loc, const QStringList& expected);
};

} // namespace exceptions
} // namespace enigma

#endif // ENIGMA_EXCEPTIONS_EXPECTED_INPUT_EXCEPTION_H


