#ifndef PITCHQUEST_ALSAAUDIOPLAYER_HPP_
#define PITCHQUEST_ALSAAUDIOPLAYER_HPP_

#include "audioplayer.hpp"

#include "alsa/asoundlib.h"
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <string_view>
#include <thread>

namespace PitchQuestTest {

class AlsaAudioPlayer_TestFriend;

}   // namespace PitchQuestTest

namespace PitchQuest {

class AlsaAudioPlayer final : public AudioPlayer {

    friend class PitchQuestTest::AlsaAudioPlayer_TestFriend;

    public:
        AlsaAudioPlayer();
        ~AlsaAudioPlayer() override;

        void play(std::vector<Note> notes) override;
        void wait_for_idle() override;

    private:
        void worker_loop();
        static constexpr std::string_view snd_pcm_state_to_string(snd_pcm_state_t state);

        const char* m_device;
        snd_pcm_t* m_handle;
        snd_pcm_hw_params_t* m_params;
        unsigned int m_sample_rate;
        const unsigned int m_channels;
        const double m_max_amplitude;
        std::queue<std::vector<Note>> m_queue;
        std::thread m_worker;
        std::atomic<bool> m_running;
        std::mutex m_mutex;
        std::condition_variable m_cv_notify_worker;
        std::condition_variable m_cv_notify_idle;
    };

}   // namespace PitchQuest

#endif  // PITCHQUEST_ALSAAUDIOPLAYER_HPP_
