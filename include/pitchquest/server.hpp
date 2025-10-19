#pragma once

#include <netinet/in.h>
#include <thread>

namespace PitchQuest {

class Server {
    public:
        Server();
        ~Server();
    private:
        void recv_loop();

        std::thread m_worker;
        bool m_running;
        int m_server_socket;
        sockaddr_in m_server_address;
        int m_client_socket;
};

}   // namespace PitchQuest
