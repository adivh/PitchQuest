#pragma once

#include "audioplayer.hpp"
#include "packethandler.hpp"

namespace PitchQuest {

class ClientPacketHandler : public PacketHandler {
    public:
        explicit ClientPacketHandler(AudioPlayer& player);

        void on_interval_challenge(IntervalChallengePacket packet) override;

    private:
        AudioPlayer& m_player;
};

}   // namespace PitchQuest
