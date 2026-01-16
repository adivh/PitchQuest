#include "audioplayer.hpp"
#include "logger.hpp"
#include "clientpackethandler.hpp"
#include "scale.hpp"

namespace PitchQuest {

ClientPacketHandler::ClientPacketHandler(AudioPlayer& player) : m_player{player} {};

void ClientPacketHandler::on_interval_challenge(IntervalChallengePacket packet) {
    log_debug("{}", packet.to_string());
    std::vector<Note> sequence {
        Note{Scale::heptatonic(packet.note1, packet.octave1), std::chrono::duration<double>(1.0)},
        Note{Scale::heptatonic(packet.note2, packet.octave2), std::chrono::duration<double>(1.0)},
        Note{0.0, std::chrono::duration<double>(2.0)},
        Note{Scale::heptatonic(packet.note1, packet.octave1), std::chrono::duration<double>(1.0)},
        Note{Scale::heptatonic(packet.note2, packet.octave2), std::chrono::duration<double>(1.0)}
    };
    m_player.play(sequence);
}

}   // namespace PitchQuest
