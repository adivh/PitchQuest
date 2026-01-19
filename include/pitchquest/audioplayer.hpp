#ifndef PITCHQUEST_AUDIOPLAYER_HPP_
#define PITCHQUEST_AUDIOPLAYER_HPP_

#include <vector>

#include "note.hpp"

namespace PitchQuest {
    
class AudioPlayer {
    public:
        virtual ~AudioPlayer() = default;

        virtual void play(std::vector<Note> notes) = 0;
        virtual void wait_for_idle() = 0;
};

}   // namespace PitchQuest

#endif  // PITCHQUEST_AUDIOPLAYER_HPP_
