#pragma once

#include <stdint.h>
#include <array>

namespace PitchQuest {

struct IntervalChallengePacket {
    IntervalChallengePacket(uint8_t sound1, uint8_t sound2);
    IntervalChallengePacket(uint8_t note1, uint8_t octave1, uint8_t note2, uint8_t octave2);

    static inline const uint8_t packet_type {0xb1};
    const uint8_t note1;
    const uint8_t octave1;
    const uint8_t note2;
    const uint8_t octave2;

    constexpr std::array<uint8_t, 3> to_bytes() const;
};

}   // namespace PitchQuest
