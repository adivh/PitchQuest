#ifndef PITCHQUEST_INTERVALCHALLENGEPACKET_HPP_
#define PITCHQUEST_INTERVALCHALLENGEPACKET_HPP_

#include <array>
#include <format>
#include <stdint.h>

namespace PitchQuest {

struct IntervalChallengePacket {
    constexpr IntervalChallengePacket(uint8_t sound1, uint8_t sound2)
        : IntervalChallengePacket {
            static_cast<uint8_t>(sound1 >> 4),
            static_cast<uint8_t>(sound1 & 0x0f),
            static_cast<uint8_t>(sound2 >> 4),
            static_cast<uint8_t>(sound2 & 0x0f)
        } {};

    constexpr IntervalChallengePacket(uint8_t note1, uint8_t octave1, uint8_t note2, uint8_t octave2)
        :   note1{note1},
            octave1{octave1},
            note2{note2},
            octave2{octave2} {};

    static inline const uint8_t packet_type {0xb1};
    const uint8_t note1;
    const uint8_t octave1;
    const uint8_t note2;
    const uint8_t octave2;

    constexpr std::array<uint8_t, 3> to_bytes() const {
        return {
            IntervalChallengePacket::packet_type,
            static_cast<uint8_t>((note1 << 4) | octave1),
            static_cast<uint8_t>((note2 << 4) | octave2)
        };
    }

    constexpr std::string to_string() const {
        return std::format("type: {}, note1: {}, octave1: {}, note2: {}, octave2: {}",
                            IntervalChallengePacket::packet_type,
                            note1,
                            octave1,
                            note2,
                            octave2);
    }
};

}   // namespace PitchQuest

#endif  // PITCHQUEST_CLI_HPP_
