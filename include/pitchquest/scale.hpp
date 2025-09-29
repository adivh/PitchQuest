#pragma once

#include <cmath>

namespace pitchquest {
    class Scale {
        public:
            Scale() = delete;
            Scale(const Scale& other) = delete;
            Scale(const Scale&& other) = delete;
            ~Scale() = delete;

            static constexpr double Heptatonic(int note, int octave) noexcept {
                return 440.0 * std::pow(2.0, ((note - 9) + 12 * (octave - 4)) / 12.0);        // A4 <= Heptatonic(9, 4)
            }
    };
}
