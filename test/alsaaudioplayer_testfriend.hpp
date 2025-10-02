#include "alsaaudioplayer.hpp"

namespace PitchQuestTest {

class AlsaAudioPlayer_TestFriend {
    public:
        AlsaAudioPlayer_TestFriend() = delete;
        ~AlsaAudioPlayer_TestFriend() = delete;

        static size_t queue_size(PitchQuest::AlsaAudioPlayer& player) {
            std::scoped_lock lock{player.m_mutex};
            return player.m_queue.size();
        }
};

}   // namespace PitchQuest
