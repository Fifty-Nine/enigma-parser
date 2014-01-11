#ifndef ENIGMA_UTIL_ENUMERATION_H
#define ENIGMA_UTIL_ENUMERATION_H

#include <boost/operators.hpp>
#include <QHash>

namespace enigma
{
namespace util
{

template<class Def, class Inner=typename Def::Enum>
class Enumeration : 
    public Def,
    boost::less_than_comparable<Enumeration<Def, Inner> >, 
    boost::equality_comparable<Enumeration<Def, Inner> >
{
public:
    Enumeration( Inner value=Inner() ) : m_value( value ) { }

    Inner rawValue() const { return m_value; }

    bool operator==( const Enumeration& rhs ) const 
    { 
        return m_value == rhs.m_value; 
    }

    bool operator<( const Enumeration& rhs ) const
    {
        return m_value < rhs.m_value;
    }

    QString toString() const
    {
        return Def::toString(m_value);
    }

private:
    Inner m_value;
};

template<class T>
inline unsigned int qHash(const Enumeration<T>& e)
{
    return ::qHash((int)e.rawValue());
}

} // namespace util
} // namespace enigma
#endif // ENIGMA_UTIL_ENUMERATION


