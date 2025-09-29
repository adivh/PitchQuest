#pragma once

#include <chrono>

namespace PitchQuest {

class Note {
    public:
        using Seconds = std::chrono::duration<double>;

        constexpr explicit Note(double frequency, Seconds duration) noexcept : m_frequency{frequency}, m_duration{duration} {}

        constexpr double frequency() const noexcept { return m_frequency; }
        constexpr Seconds duration() const noexcept { return m_duration; }

        constexpr bool operator==(const Note&) const noexcept = default;

    private:
        const double m_frequency;           // Hz
        const Seconds m_duration;          // Seconds
};

}   // namespace PitchQuest
