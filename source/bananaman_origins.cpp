#include "bananaman_origins.h"

#include <scenes/level_1.h>

//------------------------------------------------------------------//

BananaManOrigins::BananaManOrigins()
    : mp_levelContainer(new Level1()), mp_player(new Player())
{
    addChild(mp_levelContainer);
    mp_levelContainer->setPlayer(mp_player);
}

//------------------------------------------------------------------//