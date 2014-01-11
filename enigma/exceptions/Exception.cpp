#include "enigma/exceptions/Exception.h"

namespace enigma
{
namespace exceptions
{
Exception::Exception(const Location& loc, const QString& message) :
    m_loc(loc), m_msg(message)
{
}

Exception::~Exception()
{
}

Location Exception::location() const
{
    return m_loc;
}

QString Exception::what() const
{
    return m_msg;
}

} // namespace exceptions
} // namespace enigma
