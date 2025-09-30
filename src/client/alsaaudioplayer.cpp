#include "alsaaudioplayer.hpp"

#include <cmath>
#include <print>

namespace PitchQuest {

AlsaAudioPlayer::AlsaAudioPlayer()
    : m_device{"default"}, m_sample_rate{44'100}, m_channels{1}, m_max_amplitude{32'000} {

    snd_pcm_open(&m_handle, m_device, SND_PCM_STREAM_PLAYBACK, 0);
    snd_pcm_hw_params_alloca(&m_params);
    snd_pcm_hw_params_any(m_handle, m_params);
    snd_pcm_hw_params_set_access(m_handle, m_params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(m_handle, m_params, SND_PCM_FORMAT_S16_LE);
    snd_pcm_hw_params_set_channels(m_handle, m_params, m_channels);
    snd_pcm_hw_params_set_rate_near(m_handle, m_params, &m_sample_rate, 0);
    snd_pcm_hw_params(m_handle, m_params);

    m_running = true;
    m_worker = std::thread{&AlsaAudioPlayer::worker_loop, this};
}

AlsaAudioPlayer::~AlsaAudioPlayer() {
    m_running = false;
    m_cv.notify_all();

    if (m_worker.joinable()) {
        m_worker.join();
    }

    if (m_handle) {
        snd_pcm_drain(m_handle);
        snd_pcm_close(m_handle);
        m_handle = nullptr;
    }
}

void AlsaAudioPlayer::play(std::vector<Note> notes) {
    {
        std::unique_lock<std::mutex> lock{m_mutex};
        m_queue.push(std::move(notes));
    }
    m_cv.notify_one();
}

void AlsaAudioPlayer::worker_loop() {

    const size_t buffer_size = m_sample_rate / 100;  // 10ms
    std::vector<short> buffer(buffer_size);

    while (m_running) {

        std::vector<Note> notes {};

        {
            std::unique_lock<std::mutex> lock{m_mutex};
            m_cv.wait(lock, [this]() { return !m_queue.empty() || !m_running.load(); });

            if (!m_running && m_queue.empty()) {
                break;
            }

            notes = std::move(m_queue.front());
            m_queue.pop();
        }

        if (snd_pcm_state(m_handle) != SND_PCM_STATE_PREPARED) {
            int err {snd_pcm_prepare(m_handle)};
            if (err) {
                std::print("Failed to enter prepared state: {}\n"
                   "Current state: {}\n",
                   snd_strerror(err),
                   snd_pcm_state_to_string(snd_pcm_state(m_handle)));
            }
        }

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
        snd_pcm_drain(m_handle);
    }
}

constexpr std::string_view AlsaAudioPlayer::snd_pcm_state_to_string(const snd_pcm_state_t state) {
    switch (state) {
    case SND_PCM_STATE_OPEN:
        return "OPEN";
    case SND_PCM_STATE_SETUP:
        return "SETUP";
    case SND_PCM_STATE_PREPARED:
        return "PREPARED";
    case SND_PCM_STATE_RUNNING:
        return "RUNNING";
    case SND_PCM_STATE_XRUN:
        return "XRUN";
    case SND_PCM_STATE_DRAINING:
        return "DRAINING";
    case SND_PCM_STATE_PAUSED:
        return "PAUSED";
    case SND_PCM_STATE_SUSPENDED:
        return "SUSPENDED";
    case SND_PCM_STATE_DISCONNECTED:
        return "DISCONNECTED";
    default:
        return "UNKNOWN";
    }
}

}   // namespace PitchQuest
