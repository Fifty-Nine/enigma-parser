#ifndef ENIGMA_FILE_POS_H
#define ENIGMA_FILE_POS_H
#pragma once

namespace enigma
{

/// A class that represents a location in an enigma document.
struct FilePos 
{
    /// Default constructor.
    FilePos() :
        pos(0), line(0), column(0)
    { }

    /// Constructor.
    FilePos(int pos_, int line_, int col_) :
        pos(pos_), line(line_), column(col_)
    { }

    int pos;
    int line;
    int column;
};

/// A class that represents a range of locations in an enigma document.
typedef std::pair<FilePos, FilePos> FileSpan;

} // namespace enigma

#endif // ENIGMA_FILE_POS
