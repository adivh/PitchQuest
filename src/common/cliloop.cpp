#include "cliloop.hpp"

#include "logger.hpp"

namespace PitchQuest {

CliLoop::CliLoop(std::istream& in)
    :   m_in{in},
        m_running{true},
        m_stopped{false} {
    m_stopped = true;   // TODO
}

int CliLoop::count_commands() {
    return m_commands.size();
}

bool CliLoop::has_command(std::string command) {
    return m_commands.find(command) != m_commands.end();
}

bool CliLoop::is_running() {
    return m_running;
}

bool CliLoop::is_stopped() {
    return m_stopped;
}

void CliLoop::register_command(std::string_view command, CommandFunction function) {
    const bool success {m_commands.emplace(command, function).second};

    if (!success) {
        log_debug("Failed to register command \"{}\"", command);
    }
}

void CliLoop::stop() {
    std::lock_guard lock{m_mutex};
    m_running = false;
}

void CliLoop::unregister_command(std::string command) {
    const size_t success {m_commands.erase(command)};

    if (!success) {
        log_debug("Failed to unregister command \"{}\"", command);
    }
}

void CliLoop::wait() {
    std::unique_lock lock{m_mutex};
    m_cv_stopped.wait(lock, [this] { return m_stopped; });
}

void CliLoop::work_loop() {
    while(m_running) {

    }
}

}   // namespace PitchQuest
