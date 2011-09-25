#include "enigma/Province.h"

namespace enigma
{

class Province::Data
{
public:
    Data(Id id_) :
        id(id_)
    {
    }

    Province::Id id;
};

Province::Province(Id id) : 
    d(new Data(id))
{
}

Province::~Province()
{
}

Province::Id Province::id() const
{
    return d->id;
}

} // namespace enigma
