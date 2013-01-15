#ifndef ENIGMA_GAME_H
#define ENIGMA_GAME_H

#include <QHash>
#include "enigma/Province.h"

namespace enigma
{

/*! This class holds information about an analyzed save game. */
class Game
{
public:
    Game();
    virtual ~Game();

    /*! Get the province with the given ID. 
     *  \return The province, or NULL if it doesn't exist. */
    virtual const Province* province(Province::Id id) const;

    /*! Get the province with the given ID.
     *  \return The identified province, or a new province if it wasn't
     *          already in the game. */
    virtual Province* province(Province::Id id);

    /*! Get the list of provinces in the game.
     *  \return The provinces. */
    virtual QList<Province*> provinces();

    /*! Get the list of provinces in the game.
     *  \return The provinces. */
    virtual QList<const Province*> provinces() const;

protected:
    typedef QHash<Province::Id, Province*> ProvinceMap;
    ProvinceMap m_provinces;
};

} // namespace enigma

#endif // ENIGMA_GAME_H
