#include "alsaaudioplayer.hpp"

#include <cmath>
#include <print>

namespace PitchQuest {

AlsaAudioPlayer::AlsaAudioPlayer()
    :   m_device{"default"},
        m_sample_rate{44'100},
        m_channels{1},
        m_max_amplitude{32'000} {
    snd_pcm_open(&m_handle, m_device, SND_PCM_STREAM_PLAYBACK, 0);
    snd_pcm_hw_params_alloca(&m_params);
    snd_pcm_hw_params_any(m_handle, m_params);
    snd_pcm_hw_params_set_access(m_handle, m_params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(m_handle, m_params, SND_PCM_FORMAT_S16_LE);
    snd_pcm_hw_params_set_channels(m_handle, m_params, m_channels);
    snd_pcm_hw_params_set_rate_near(m_handle, m_params, &m_sample_rate, 0);
    snd_pcm_hw_params(m_handle, m_params);
}

AlsaAudioPlayer::~AlsaAudioPlayer() {
    if (m_handle) {
        snd_pcm_drain(m_handle);
        snd_pcm_close(m_handle);
        m_handle = nullptr;
    }
}

void AlsaAudioPlayer::play(const std::vector<Note> notes) const {

    if (snd_pcm_state(m_handle) != SND_PCM_STATE_PREPARED) {
        snd_pcm_prepare(m_handle);
    }

    const size_t buffer_size = m_sample_rate / 100;  // 10ms
    std::vector<short> buffer(buffer_size);

    for (Note note : notes) {
        const int duration {static_cast<int>(note.duration().count() * m_sample_rate)};
        for (size_t i {}; i <= duration - buffer_size; i += buffer_size) {
            for (size_t j {}; j < buffer_size; ++j) {
                double t = static_cast<double>(i + j) / m_sample_rate;
                buffer.at(j) = static_cast<short>(m_max_amplitude * sin(2.0 * M_PI * note.frequency() * t));
            }
            snd_pcm_writei(m_handle, &buffer[0], buffer_size);
        }
    }


}

}   // namespace PitchQuest
