#pragma once

#include <scenes/level.h>
#include <player/player.h>

//------------------------------------------------------------------//

class BananaManOrigins : public AE::Object
{
public:
    BananaManOrigins();

private:
    Level *mp_levelContainer{nullptr};
    Player *mp_player{nullptr};
};

//------------------------------------------------------------------//
