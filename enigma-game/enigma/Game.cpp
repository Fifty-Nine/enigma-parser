#include "enigma/Game.h"

#include <QHash>

namespace enigma
{

Game::Game()
{
}

Game::~Game()
{
    qDeleteAll(m_provinces);
}

const Province* Game::province(Province::Id id) const
{
    ProvinceMap::const_iterator it = m_provinces.find(id);

    return (it != m_provinces.end()) ? *it : NULL;
}

Province* Game::province(Province::Id id)
{
    ProvinceMap::const_iterator it = m_provinces.find(id);

    if (it != m_provinces.end())
    {
        return *it;
    }

    Province *new_prov = new Province(id);
    m_provinces.insert(id, new_prov);
    return new_prov;
}

}
