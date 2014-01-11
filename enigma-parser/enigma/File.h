#ifndef ENIGMA_FILE_H
#define ENIGMA_FILE_H

#include "enigma/ast/NodePtrs.h"

namespace enigma {

enum class FileType { Invalid, CK2Txt, CK2Bin };

class File { 
public:
    FileType type;
    ast::AssignmentListPtr tree;
};

} // namespace enigma

#endif
