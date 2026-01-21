#include "server.hpp"

#include <array>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>

#include "logger.hpp"

namespace PitchQuest {

Server::Server()
    :   m_running{true},
        m_server_socket{0},
        m_server_address{AF_INET, 8080, {INADDR_ANY}, 0},
        m_client_socket{0} {
    m_server_socket = socket(AF_INET, SOCK_STREAM, 0);
    int enable = 1;
    setsockopt(m_server_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));
    int err = bind(m_server_socket, (struct sockaddr*) &m_server_address, sizeof(m_server_address));

    if (err) {
        m_running = false;
        log_error("Binding failed: {}", strerror(errno));
    } else {
        m_worker = std::thread(&Server::recv_loop, this);
    }
}

Server::~Server() {
    stop();
    shutdown(m_server_socket, SHUT_RDWR);

    if (m_worker.joinable()) {
        m_worker.join();
    }
    
    close(m_server_socket);
}

void Server::broadcast(IntervalChallengePacket packet) const {
    log_debug("Sending IntervalChallengePacket to client");
    if (m_client_socket) {
        log_debug("{}", packet.to_string());
        ::send(m_client_socket, packet.to_bytes().data(), packet.to_bytes().size(), 0);
    } else {
        log_debug("no client connected");
    }
}

void Server::stop() {
    std::lock_guard lock{m_mutex};
    m_running = false;
}

void Server::wait() {
    std::unique_lock lock{m_mutex};
    m_stopped_cv.wait(lock, [this] { return !m_running; });
}

void Server::recv_loop() {
    
    int err = listen(m_server_socket, 1);

    if (err) {
        log_debug("Error listening: {}", strerror(errno));
        return;
    }

    sockaddr client_address {};
    socklen_t client_address_len {sizeof(client_address)};
    m_client_socket = accept(m_server_socket, (struct sockaddr*) &client_address, &client_address_len);

    if (m_running) {
        log_debug("Connection accepted");
    }

    pollfd pfds {m_client_socket, POLLIN, 0};
    std::array<char, 1024> buffer {};

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
                buffer.at(bytes) = '\0';
                log_debug("Received message: {}", buffer.data());
            } else if (bytes == 0) {
                log_debug("Client closed connection");
                stop();
                break;
            } else {
                log_warn("recv() error: {}", strerror(errno));
                stop();
                break;
            }
        } else if (pfds.revents & POLLHUP) {
            stop();
            log_debug("Connection closed");
            break;
        } else if (pfds.revents & (POLLERR | POLLNVAL)) {
            stop();
            log_warn("Socket error or invalid fd");
            break;
        }
    }

    close(m_client_socket);
    m_client_socket = 0;
    m_stopped_cv.notify_all();
}

}   // namespace PitchQuest
