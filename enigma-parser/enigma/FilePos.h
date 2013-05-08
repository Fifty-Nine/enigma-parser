#ifndef ENIGMA_FILE_POS_H
#define ENIGMA_FILE_POS_H
#pragma once

#include <boost/operators.hpp>

namespace enigma
{

/// A class that represents a location in an enigma document.
struct FilePos : boost::less_than_comparable<FilePos>
{
    /// Default constructor.
    FilePos() :
        pos(0), line(0), column(0)
    { }

    /// Constructor.
    FilePos(int pos_, int line_, int col_) :
        pos(pos_), line(line_), column(col_)
    { }

    /*! Test whether this position comes before the given position.
     *  \param[in] other The other position.
     *  \return True if this position comes before the other. */
    bool operator<(FilePos other) const
    {
        return pos < other.pos;
    }

    int pos;
    int line;
    int column;
};

/// A class that represents a range of locations in an enigma document.
typedef std::pair<FilePos, FilePos> FileSpan;

/*! Given two file spans, create a file span that contains both.
 *  \param[in] l The first span.
 *  \param[in] r The second span.
 *  \return The new span. */
inline FileSpan operator+(FileSpan l, FileSpan r)
{
    return FileSpan(std::min(l.first, r.first), std::max(r.second, r.second));
}

/*! Update the given file span to include the other span.
 *  \param[in] l The first span.
 *  \param[in] r The second span.
 *  \return The new span. */
inline FileSpan& operator+=( FileSpan& l, FileSpan r)
{
    l = l + r;
    return l;
}

} // namespace enigma

#endif // ENIGMA_FILE_POS
