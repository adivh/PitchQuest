#include "client.hpp"

#include <array>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>

#include "intervalchallengepacket.hpp"
#include "logger.hpp"

namespace PitchQuest {

Client::Client()
    :   m_running{true},
        m_client_socket{0},
        m_server_address{AF_INET, 8080, in_addr{INADDR_ANY}, 0} {
    m_client_socket = socket(AF_INET, SOCK_STREAM, 0);
    int err = connect(m_client_socket, (struct sockaddr*) &m_server_address, sizeof(m_server_address));
    if (err) {
        log_debug("Error connecting to server: {}", strerror(errno));
        exit(0);
    }

    m_worker = std::thread(&Client::recv_loop, this);
}

Client::~Client() {
    stop();
    close(m_client_socket);
    if (m_worker.joinable()) {
        m_worker.join();
    }
}

void Client::send(const char* const msg, size_t len) {
   ::send(m_client_socket, msg, len, 0);
}

void Client::stop() {
    std::lock_guard lock{m_mutex};
    m_running = false;
}

void Client::wait() {
    std::unique_lock lock{m_mutex};
    m_stopped_cv.wait(lock, [this] { return !m_running; });
}

void Client::recv_loop() {
    pollfd pfds {m_client_socket, POLLIN, 0};
    std::array<uint8_t, 1024> buffer {};

    while (m_running) {

        int ready = poll(&pfds, static_cast<nfds_t>(1), 2'000);

        if (ready < 0) {
            log_debug("Polling failed: {}", strerror(errno));
            continue;
        }

        if (ready == 0) {
            continue;
        }

        if (pfds.revents & POLLIN) {

            ssize_t bytes = recv(m_client_socket, buffer.data(), buffer.size() - 1, 0);

            if (bytes > 0) {
                log_info("Received {} bytes", bytes);
                if (buffer.at(0) == IntervalChallengePacket::packet_type) {
                    IntervalChallengePacket packet {buffer.at(1), buffer.at(2)};
                    log_info("{}", packet.to_string());
                }
            } else if (bytes == 0) {
                log_info("Server closed connection");
                stop();
            } else {
                log_warn("recv() error: {}", strerror(errno));
                stop();
            }
        } else if (pfds.revents & POLLHUP) {
            stop();
            log_info("Connection closed");
            break;
        } else if (pfds.revents & (POLLERR | POLLNVAL)) {
            if (m_running) {
                stop();
                log_info("Socket error or invalid fd");
            }
            break;
        }
    }

    close(m_client_socket);
}

}   // namespace PitchQuest
