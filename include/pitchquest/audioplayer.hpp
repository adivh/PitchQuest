#pragma once

#include <vector>

#include "note.hpp"

namespace PitchQuest {
    
class AudioPlayer {
    public:
        virtual ~AudioPlayer() = default;

        virtual void play(std::vector<Note> notes) const = 0;
};

}   // namespace PitchQuest
