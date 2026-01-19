#ifndef PITCHQUEST_PACKETHANDLER_HPP_
#define PITCHQUEST_PACKETHANDLER_HPP_

#include "intervalchallengepacket.hpp"

namespace PitchQuest {

class PacketHandler {
    public:
        virtual ~PacketHandler() = default;

        virtual void on_interval_challenge(IntervalChallengePacket packet) = 0;
};

}   // namespace PitchQuest

#endif  // PITCHQUEST_CLI_HPP_
