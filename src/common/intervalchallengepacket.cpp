#include "intervalchallengepacket.hpp"

namespace PitchQuest {

IntervalChallengePacket::IntervalChallengePacket(const uint8_t sound1, const uint8_t sound2) 
    : IntervalChallengePacket {
        static_cast<uint8_t>(sound1 >> 4),
        static_cast<uint8_t>(sound1 & 0x0f),
        static_cast<uint8_t>(sound2 >> 4),
        static_cast<uint8_t>(sound2 & 0x0f)
    } {}

IntervalChallengePacket::IntervalChallengePacket(const uint8_t note1, const uint8_t octave1, const uint8_t note2, const uint8_t octave2)
    : note1{note1}, octave1{octave1}, note2{note2}, octave2{octave2} {}

}   // namespace PitchQuest
