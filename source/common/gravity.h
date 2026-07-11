#pragma once

//------------------------------------------------------------------//

#include <objects/object.h>

//------------------------------------------------------------------//

class Gravity
{
public:
    static void apply(double deltaTime, double force, AE::Object *p_object);
};

//------------------------------------------------------------------//
