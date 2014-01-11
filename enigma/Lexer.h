#ifndef ENIGMA_LEXER_H
#define ENIGMA_LEXER_H

#include <boost/noncopyable.hpp>
#include <memory>
#include <QChar>
#include <QSet>

#include "enigma/Location.h"

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
    std::unique_ptr<tokens::Token> nextToken();

    /*! Get the current location of the input stream. */
    Location currentPos() const;

protected:
    virtual std::unique_ptr<tokens::Token> lexIdentifiers();
    virtual std::unique_ptr<tokens::Token> lexStrings();
    virtual std::unique_ptr<tokens::Token> lexNumeric();

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
