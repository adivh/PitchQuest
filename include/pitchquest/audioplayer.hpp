#pragma once

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
