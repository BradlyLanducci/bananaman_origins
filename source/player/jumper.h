#pragma once

#include <objects/character.h>
#include <objects/collision.h>

//------------------------------------------------------------------//

class Jumper final : public AE::Object
{
public:
    Jumper(AE::Character *p_subject, AE::Collision *p_subject_collision);

    enum class State : int
    {
        Idle,
        Jumping,
        Falling
    };

    State state() const;

    void begin(double jumpTime, double jumpForce);

private:
    void physicsUpdate(double delta);

    State m_state{ State::Idle };

    AE::Character *mp_subject{ nullptr };
    AE::Collision *mp_subjectCollision{ nullptr };
    AE::Slot<bool> m_onFloorChanged;

    double m_accumulator{};
    double m_jumpForce{};
    double m_jumpSeconds{};
};

//------------------------------------------------------------------//
