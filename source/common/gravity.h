#pragma once

//------------------------------------------------------------------//

#include <objects/character.h>

//------------------------------------------------------------------//

class Gravity
{
public:
    static void apply(double deltaTime, double force, AE::Character *p_character);
};

//------------------------------------------------------------------//
