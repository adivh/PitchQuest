#ifndef PITCHQUEST_CLILOOP_HPP_
#define PITCHQUEST_CLILOOP_HPP_

#include <condition_variable>
#include <functional>
#include <iostream>
#include <istream>
#include <mutex>
#include <span>
#include <string_view>
#include <thread>

namespace PitchQuest {

class CliLoop {
    public:
        using CommandFunction = std::function<bool(std::span<std::string_view>)>;
        explicit CliLoop(std::istream& in = std::cin);
        ~CliLoop() = default;

        int count_commands();
        bool has_command(std::string command);
        bool is_running();
        bool is_stopped();
        void register_command(
                std::string_view command, CommandFunction function);
        void stop();
        void unregister_command(std::string command);
        void wait();

    private:
        void work_loop();

        std::unordered_map<std::string, CommandFunction> m_commands;
        std::istream& m_in;
        std::thread m_worker;
        std::mutex m_mutex;
        std::condition_variable m_cv_stopped;
        bool m_running;
        bool m_stopped;
};

}   // namespace PitchQuest

#endif  // PITCHQUEST_CLILOOP_HPP_
