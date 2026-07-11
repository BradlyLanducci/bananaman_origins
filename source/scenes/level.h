#pragma once

#include <objects/object.h>

//------------------------------------------------------------------//

class Player;

//------------------------------------------------------------------//

class Level : public AE::Object
{
public:
    virtual ~Level() = default;
    void setPlayer(Player *p_player);

private:
    Player *mp_player{nullptr};
};

//------------------------------------------------------------------//
