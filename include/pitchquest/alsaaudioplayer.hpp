#pragma once

#include "audioplayer.hpp"

#include "alsa/asoundlib.h"

namespace PitchQuest {

class AlsaAudioPlayer final : public AudioPlayer {
    public:
        AlsaAudioPlayer();
        ~AlsaAudioPlayer() override;

        void play(std::vector<Note> notes) const override;

    private:
        const char* m_device;
        snd_pcm_t* m_handle;
        snd_pcm_hw_params_t* m_params;
        unsigned int m_sample_rate;
        const unsigned int m_channels;
        const double m_max_amplitude;
    };

}   // namespace PitchQuest
