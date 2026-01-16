#pragma once

#include "intervalchallengepacket.hpp"

namespace PitchQuest {

class PacketHandler {
    public:
        virtual ~PacketHandler() = default;

        virtual void on_interval_challenge(IntervalChallengePacket packet) = 0;
};

}   // namespace PitchQuest
