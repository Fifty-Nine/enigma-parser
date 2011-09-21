#ifndef ENIGMA_LOCATION_H
#define ENIGMA_LOCATION_H
#pragma once

namespace enigma
{

/// A class that represents a location in an enigma document.
struct Location
{
    /// Default constructor.
    Location() :
        pos(0), line(0), column(0)
    { }

    /// Constructor.
    Location(int pos_, int line_, int col_) :
        pos(pos_), line(line_), column(col_)
    { }

    int pos;
    int line;
    int column;
};

} // namespace enigma

#endif // ENIGMA_LOCATION
