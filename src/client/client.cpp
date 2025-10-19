#include "client.hpp"

#include <sys/socket.h>
#include <unistd.h>

#include "logger.hpp"

namespace PitchQuest {

Client::Client() : m_server_address{AF_INET, 8080, in_addr{INADDR_ANY}, 0} {
    m_client_socket = socket(AF_INET, SOCK_STREAM, 0);
    int err = connect(m_client_socket, (struct sockaddr*) &m_server_address, sizeof(m_server_address));
    if (err) {
        spdlog::debug("Error connecting to server: {}", strerror(errno));
    }
}

Client::~Client() {
    close(m_client_socket);
}

void Client::send(const char* const msg, size_t len) {
   ::send(m_client_socket, msg, len, 0);
}

}   // namespace PitchQuest
