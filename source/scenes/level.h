#pragma once

#include <objects/object.h>

//------------------------------------------------------------------//

class GameUi;
class Player;

//------------------------------------------------------------------//

class Level : public AE::Object
{
public:
    virtual ~Level() = default;

    enum class Type
    {
        None,
        Level1,
        Level2,
        Level3,
        End
    };

    virtual void setUi(GameUi *p_gameUi) = 0;
    virtual void setPlayer(Player *p_player) = 0;
};

//------------------------------------------------------------------//
