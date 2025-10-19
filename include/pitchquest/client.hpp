#pragma once

#include <netinet/in.h>

namespace PitchQuest {

class Client {
    public:
        Client();
        ~Client();

        void send(const char* msg, size_t len);
    private:
       int m_client_socket;
       sockaddr_in m_server_address;
};

}   // namespace PitchQuest
