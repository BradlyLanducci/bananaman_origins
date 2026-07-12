#include <player/jumper.h>

#include <physics/aabb.h>

//------------------------------------------------------------------//

Jumper::Jumper(AE::Character *p_subject, AE::Collision *p_subject_collision)
    : mp_subject(p_subject)
    , mp_subjectCollision(p_subject_collision)
    , m_onFloorChanged(
          [this](bool isOnFloor)
          {
              if (m_state == State::Falling && isOnFloor)
              {
                  m_state = State::Idle;
              }
          })
    , m_jumpSfx("examples/platformer/grass_scene/audio/jump.wav")
{
    mp_subject->isOnFloorChanged.connect(m_onFloorChanged);

    addPhysicsCb([this](double deltaTime) { physicsUpdate(deltaTime); });
}

//------------------------------------------------------------------//

void Jumper::begin(double jumpSeconds, double jumpForce)
{
    if (m_state == State::Idle)
    {
        m_jumpSfx.play();

        m_accumulator = 0.0;
        m_jumpSeconds = jumpSeconds;
        m_jumpForce = jumpForce;
        m_state = State::Jumping;
    }
}

//------------------------------------------------------------------//

Jumper::State Jumper::state() const
{
    return m_state;
}

//------------------------------------------------------------------//

void Jumper::physicsUpdate(double delta)
{
    if (m_state == State::Jumping)
    {
        m_accumulator += delta;

        if (m_accumulator <= m_jumpSeconds)
        {
            mp_subject->setVelocity(mp_subject->velocity() + AE::Vector2(0, -m_jumpForce));
            // double progress{ 1.0 - (m_accumulator / m_jumpSeconds) };
            // auto gp{ mp_subject->globalPosition() };
            // gp.y -= m_jumpForce * delta * progress;
            // mp_subject->setGlobalPosition(gp);
        }
        else
        {
            m_state = State::Falling;
        }
    }
}

//------------------------------------------------------------------//