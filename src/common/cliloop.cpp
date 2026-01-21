#include "cliloop.hpp"

#include "cli.hpp"
#include "logger.hpp"

namespace PitchQuest {

CliLoop::CliLoop(std::istream& in, bool start_running)
    :   m_in{in},
        m_running{false},
        m_stopped{true} {
    if (start_running) {
        start();
    }
}

CliLoop::~CliLoop() {
    if (m_worker.joinable()) {
        m_worker.join();
    }
    m_cv_stopped.notify_all();
}

int CliLoop::count_commands() const {
    return m_commands.size();
}

bool CliLoop::has_command(std::string command) const {
    return m_commands.find(command) != m_commands.end();
}

bool CliLoop::is_running() const {
    return m_running;
}

bool CliLoop::is_stopped() const {
    return m_stopped;
}

void CliLoop::register_command(std::string_view command, CommandFunction function) {
    const bool success {m_commands.emplace(command, function).second};

    if (success) {
        log_debug("Registered command '{}'", command);
    } else {
        log_debug("Failed to register command '{}'", command);
    }
}

void CliLoop::start() {
    if (m_running) {
        return;
    }

    m_running = true;
    m_stopped = false;
    m_worker = std::thread {&CliLoop::work_loop, this};
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
        std::string line {};
        std::getline(m_in, line);
        cli::sanitize(line);
        std::vector<std::string_view> tokens {cli::tokenize_view(line)};

        if (tokens.size() > 0) {
            auto res = m_commands.find(std::string{tokens.at(0)});
            if (res != m_commands.end()) {
                log_info("Recognized command '{}'", tokens.at(0));
                res->second({tokens.begin() + 1, tokens.end()});
            } else {
                log_info("Could not find your command '{}'", tokens.at(0));
            }
        }
    }

    m_stopped = true;
    m_cv_stopped.notify_all();
}

}   // namespace PitchQuest
