#ifndef ENIGMA_PROVINCE_H
#define ENIGMA_PROVINCE_H
#pragma once

#include <memory>

namespace enigma
{

/*! Represents a single province in a game. */
class Province
{
public:
    typedef int Id;
    Province(Id id);
    virtual ~Province();

    Id id() const;

private:
    friend class Game;

    class Data;
    std::unique_ptr<Data> d;
};

} // namespace enigma

#endif // ENIGMA_PROVINCE_H
