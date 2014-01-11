#ifndef ENIGMA_UTIL_SET_UTILS_H
#define ENIGMA_UTIL_SET_UTILS_H
#pragma once

#include <QSet>

#if !defined(_MSC_VER) || (_MSC_VER >= 1700)
namespace enigma
{
namespace util
{


template<class T>
QSet<T> makeSet(std::initializer_list<T> list)
{
    return QSet<T>::fromList(QList<T>::fromStdList(list));
}

}
}
#endif

#endif // ENIGMA_UTIL_SET_UTILS_H
