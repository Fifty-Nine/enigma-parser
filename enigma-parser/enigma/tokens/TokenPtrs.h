#ifndef ENIGMA_TOKENS_TOKEN_PTRS_H
#define ENIGMA_TOKENS_TOKEN_PTRS_H

#include <memory>

namespace enigma
{
namespace tokens
{

class Token;
typedef std::shared_ptr<Token> TokenPtr;

class BooleanToken;
typedef std::shared_ptr<BooleanToken> BooleanTokenPtr;

class DateToken;
typedef std::shared_ptr<DateToken> DateTokenPtr;

class DecimalToken;
typedef std::shared_ptr<DecimalToken> DecimalTokenPtr;

class IdentifierToken;
typedef std::shared_ptr<IdentifierToken> IdentifierTokenPtr;

class IntegerToken;
typedef std::shared_ptr<IntegerToken> IntegerTokenPtr;

class StringToken;
typedef std::shared_ptr<StringToken> StringTokenPtr;

class TagToken;
typedef std::shared_ptr<TagToken> TagTokenPtr;

class FileStartToken;
typedef std::shared_ptr<FileStartToken> FileStartTokenPtr;

} // namespace tokens
} // namespace enigma;

#endif // ENIGMA_TOKENS_TOKEN_PTRS_H
