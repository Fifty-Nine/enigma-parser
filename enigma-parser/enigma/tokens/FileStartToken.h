#ifndef ENIGMA_TOKENS_FILE_START_TOKEN_H
#define ENIGMA_TOKENS_FILE_START_TOKEN_H

#include "enigma/tokens/Token.h"

namespace enigma 
{
namespace tokens 
{

class FileStartToken : public Token 
{
public:
    FileStartToken(const FileSpan& loc);

    virtual FileStartToken *clone() const; 
    virtual QString toString() const; 
    virtual bool isLeftBrace() const; 
};

} // namespace tokens
} // namespace enigma

#endif // ENIGMA_TOKENS_FILE_START_TOKEN_H

