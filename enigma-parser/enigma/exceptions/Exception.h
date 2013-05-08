#ifndef ENIGMA_EXCEPTIONS_EXCEPTION_H
#define ENIGMA_EXCEPTIONS_EXCEPTION_H
#pragma once

#include <QString>

#include "enigma/FilePos.h"

namespace enigma
{
namespace exceptions
{

/*! An exception thrown when an error is encountered in an Enigma document. */
class Exception
{
public:
    /*!
     * Constructor.
     *
     * \param [in] loc The location of the error.
     * \param [in] message The description of the error.
     */
    Exception(const FilePos& loc, const QString& message);

    virtual ~Exception();

    /*! Get the location where the error ocurred. */
    virtual FilePos location() const;

    /*! Get the message associated with the error. */
    virtual QString what() const;

    virtual void raise() = 0;
    virtual Exception *clone() const = 0;
private:
    FilePos m_loc;
    QString m_msg;
};

} // namespace exceptions
} // namespace enigma

#endif // ENIGMA_EXCEPTIONS_EXCEPTION_H
