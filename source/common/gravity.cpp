#include <common/gravity.h>

//------------------------------------------------------------------//

void Gravity::apply(double deltaTime, double force, AE::Character *p_character)
{
    p_character->setVelocity({ p_character->velocity().x, -force });
}

//------------------------------------------------------------------//
