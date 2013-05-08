#ifndef ENIGMA_TOKENS_BOOLEAN_TOKEN_H
#define ENIGMA_TOKENS_BOOLEAN_TOKEN_H

#include "enigma/tokens/StringToken.h"

namespace enigma
{
namespace tokens
{

class BooleanToken : public StringToken
{
public:
    /*! Construct a boolean token with the given value.
     * \param [in] value The value.
     * \param [in] stringify True if the value is quoted, as in StringToken. 
     * \param [in] loc The location of the token in the input file. */
    BooleanToken(bool value, bool stringify, const FileSpan& loc);

    /*! Get the token's boolean value. */
    virtual QVariant value() const { return m_value; }
    virtual bool setValue(const QVariant& value);
    void setValue(bool value);

    virtual BooleanToken *clone() const;
private:
    bool m_value;
};

} // namespace tokens
} // namespace enigma

#endif //ENIGMA_TOKENS_BOOLEAN_TOKEN_H

