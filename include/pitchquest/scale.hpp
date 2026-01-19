#ifndef PITCHQUEST_SCALE_HPP_
#define PITCHQUEST_SCALE_HPP_

#include <cmath>

namespace PitchQuest {

namespace Scale {

constexpr double heptatonic(int note, int octave) noexcept {
    return 440.0 * std::pow(2.0, ((note - 9) + 12 * (octave - 4)) / 12.0);        // A4 <= Heptatonic(9, 4)
}

}   // namespace Scale

}   // namespace PitchQuest

#endif  // PITCHQUEST_CLI_HPP_
