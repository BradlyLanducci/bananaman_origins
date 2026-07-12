#include <player/random_sfx.h>

//------------------------------------------------------------------//

RandomSfx::RandomSfx(const std::vector<std::string> &sounds)
{
    addIdleCb([this](double deltaTime) { idleUpdate(deltaTime); });

    for (auto &sound : sounds)
    {
        m_sfx.emplace_back(std::make_unique<AE::AudioPlayer>(sound));
    }
}

//------------------------------------------------------------------//

void RandomSfx::setVolumeDb(double db)
{
    for (auto &sfx : m_sfx)
    {
        sfx->setVolumeDb(db);
    }
}

//------------------------------------------------------------------//

void RandomSfx::play()
{
    if (m_playing)
    {
        return;
    }

    int index{ std::uniform_int_distribution<int>{ 0, static_cast<int>(m_sfx.size()) - 1 }(m_engine) };
    m_sfx.at(index)->play();

    m_playing = true;
}

//------------------------------------------------------------------//

void RandomSfx::idleUpdate(double deltaTime)
{
    m_accumulator += deltaTime;
    if (m_accumulator > m_interval)
    {
        m_playing = false;
        m_accumulator = 0.0;
        m_interval = std::uniform_real_distribution<double>{ 0.3, 0.4 }(m_engine);
    }
}

//------------------------------------------------------------------//
