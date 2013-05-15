#ifndef ENIGMA_LEXER_H
#define ENIGMA_LEXER_H

#include <boost/noncopyable.hpp>
#include <memory>
#include <QChar>
#include <QSet>

#include "enigma/FilePos.h"
#include "enigma/tokens/TokenPtrs.h"

class QIODevice;

namespace enigma
{

namespace tokens { class Token; }

class Lexer : boost::noncopyable
{
public:
    Lexer(std::unique_ptr<QIODevice> dev_p);
    ~Lexer();

    /*! Read the next token from the input stream.
     * \return The next token, or a null pointer on end of file. */
    tokens::TokenPtr nextToken();

    /*! Get the current location of the input stream. */
    FilePos currentPos() const;

protected:
    virtual tokens::TokenPtr lexIdentifiers();
    virtual tokens::TokenPtr lexStrings();
    virtual tokens::TokenPtr lexNumeric();

    QChar peek() const;
    void expect(const QSet<QChar>& expected);
    void expect(const QChar& c);
    void consume(const QSet<QChar>& expected=QSet<QChar>());
    void consume(const QChar& c);
    void consumeToEnd();

private:
    struct Impl;
    std::unique_ptr<Impl> d;
};

} // namespace enigma

#endif // ENIGMA_LEXER_H
