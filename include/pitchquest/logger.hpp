#pragma once

#include "spdlog/spdlog.h"

namespace PitchQuest {

    void setup_logger();

    template <typename... Args>
    void log_trace(spdlog::format_string_t<Args...> fmt, Args &&...args) {
        spdlog::trace(fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void log_debug(spdlog::format_string_t<Args...> fmt, Args &&...args) {
        spdlog::debug(fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void log_info(spdlog::format_string_t<Args...> fmt, Args &&...args) {
        spdlog::info(fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void log_warn(spdlog::format_string_t<Args...> fmt, Args &&...args) {
        spdlog::warn(fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void log_error(spdlog::format_string_t<Args...> fmt, Args &&...args) {
        spdlog::error(fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void log_critical(spdlog::format_string_t<Args...> fmt, Args &&...args) {
        spdlog::critical(fmt, std::forward<Args>(args)...);
    }

}   // namespace PitchQuest
