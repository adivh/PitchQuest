#include "logger.hpp"

#include <filesystem>

namespace PitchQuest {

void setup_logger() {
    std::filesystem::create_directories("logs");

    auto console_sink {std::make_shared<spdlog::sinks::stdout_color_sink_mt>()};
    console_sink->set_level(spdlog::level::debug);

    auto file_sink {std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/log.txt")};
    file_sink->set_level(spdlog::level::info);

    auto logger {std::make_shared<spdlog::logger>("multi_sink", spdlog::sinks_init_list{console_sink, file_sink})};
    logger->set_level(spdlog::level::trace);
    spdlog::set_default_logger(logger);
}

}   // namespace PitchQuest
