#include <scenes/level.h>

#include <player/player.h>

//------------------------------------------------------------------//

void Level::setPlayer(Player *p_player)
{
    mp_player = p_player;
    mp_player->addChild(mp_player);
}

//------------------------------------------------------------------//
