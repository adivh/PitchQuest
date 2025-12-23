#pragma once

#include <array>
#include <format>
#include <stdint.h>

namespace PitchQuest {

struct IntervalChallengeResponsePacket {
    constexpr IntervalChallengeResponsePacket(uint8_t notes, uint8_t octdiff_and_res)
        : IntervalChallengeResponsePacket {
            static_cast<uint8_t>(notes >> 4),
            static_cast<uint8_t>(notes & 0x0f),
            static_cast<uint8_t>(octdiff_and_res >> 4),
            static_cast<uint8_t>(octdiff_and_res & 0x0f)
    } {};

    constexpr IntervalChallengeResponsePacket(uint8_t note1, uint8_t note2, uint8_t octave_difference, uint8_t response)
        :   note1{note1},
            note2{note2},
            octave_difference{octave_difference},
            response{response} {};

    static inline const uint8_t packet_type {0x21};
    const uint8_t note1;
    const uint8_t note2;
    const uint8_t octave_difference;
    const uint8_t response;

    constexpr std::array<uint8_t, 3> to_bytes() const {
        return {
            IntervalChallengeResponsePacket::packet_type,
            static_cast<uint8_t>((note1 << 4) | note2),
            static_cast<uint8_t>((octave_difference << 4) | response)
        };
    }

    constexpr std::string to_string() const {
        return std::format("type: {}, note1: {}, note2: {}, octave_difference: {}, response: {}",
                            IntervalChallengeResponsePacket::packet_type,
                            note1,
                            note2,
                            octave_difference,
                            response);
    }
};

}   // namespace PitchQuest
