#include <common/gravity.h>

//------------------------------------------------------------------//

void Gravity::apply(double deltaTime, double force, AE::Object *p_object)
{
    AE::Vector2 gp{ p_object->globalPosition() };
    gp.y += deltaTime * force;
    p_object->setGlobalPosition(gp);
}

//------------------------------------------------------------------//
