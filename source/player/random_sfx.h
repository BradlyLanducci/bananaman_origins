#pragma once

#include <objects/object.h>
#include <audio/audio_player.h>

#include <vector>
#include <memory>
#include <random>

//------------------------------------------------------------------//

class RandomSfx final : public AE::Object
{
public:
    RandomSfx(const std::vector<std::string> &sounds);

    void setVolumeDb(double db);

    void play();

private:
    void idleUpdate(double deltaTime);

    std::vector<std::unique_ptr<AE::AudioPlayer>> m_sfx;

    std::random_device m_rd;
    std::minstd_rand m_engine{ m_rd() };

    double m_interval{ 0.25 };
    double m_accumulator{};
    bool m_playing{ false };
};

//------------------------------------------------------------------//
