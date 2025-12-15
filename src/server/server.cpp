#include "server.hpp"

#include <array>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>

#include "logger.hpp"

namespace PitchQuest {

Server::Server() : m_running{true}, m_server_address{AF_INET, 8080, {INADDR_ANY}, 0} {

    m_server_socket = socket(AF_INET, SOCK_STREAM, 0);
    int err = bind(m_server_socket, (struct sockaddr*) &m_server_address, sizeof(m_server_address));

    if (err) {
        m_running = false;
        log_error("Binding failed: {}", strerror(errno));
    } else {
        m_worker = std::thread(&Server::recv_loop, this);
    }
}

Server::~Server() {
    m_running = false;
    shutdown(m_server_socket, SHUT_RDWR);

    if (m_worker.joinable()) {
        m_worker.join();
    }
    
    close(m_server_socket);
}

void Server::recv_loop() {
    
    int err = listen(m_server_socket, 1);

    if (err) {
        log_debug("Error listening: {}", strerror(errno));
        return;
    }

    sockaddr client_address {};
    socklen_t client_address_len {sizeof(client_address)};
    int fd_client = accept(m_server_socket, (struct sockaddr*) &client_address, &client_address_len);

    if (m_running) {
        log_info("Connection accepted");
    }

    pollfd pfds {fd_client, POLLIN, 0};
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

            ssize_t bytes = recv(fd_client, buffer.data(), buffer.size() - 1, 0);

            if (bytes > 0) {
                buffer.at(bytes) = '\0';
                log_info("Received message: {}", buffer.data());
            } else if (bytes == 0) {
                log_info("Client closed connection");
                break;
            } else {
                log_warn("recv() error: {}", strerror(errno));
                break;
            }
        } else if (pfds.revents & POLLHUP) {
            m_running = false;
            log_info("Connection closed");
            break;
        } else if (pfds.revents & (POLLERR | POLLNVAL)) {
            m_running = false;
            log_info("Socket error or invalid fd");
            break;
        }
    }

    close(fd_client);
}

}   // namespace PitchQuest
