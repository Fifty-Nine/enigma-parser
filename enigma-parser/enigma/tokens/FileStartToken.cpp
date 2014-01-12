#include "enigma/tokens/FileStartToken.h"

namespace enigma
{
namespace tokens
{

FileStartToken::FileStartToken(const FileSpan& loc) :
    Token(TokenType::FileStart, loc) 
{
}

FileStartToken *FileStartToken::clone() const 
{
    return new FileStartToken(location());
}

QString FileStartToken::toString() const 
{
    return "CK2txt";
}

bool FileStartToken::isLeftBrace() const
{
    return true;
}

} // namespace tokens
} // namespace enigma
