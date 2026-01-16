#pragma once

#include <atomic>
#include <condition_variable>
#include <netinet/in.h>
#include <thread>

#include "packethandler.hpp"

namespace PitchQuest {

class Client {
    public:
        explicit Client(PacketHandler& handler);
        ~Client();

        void send(const char* msg, size_t len);
        void stop();
        void wait();

    private:
        void recv_loop();

        std::thread m_worker;
        std::atomic<bool> m_running;
        std::mutex m_mutex;
        std::condition_variable m_stopped_cv;
        int m_client_socket;
        sockaddr_in m_server_address;
        PacketHandler& m_handler;
};

}   // namespace PitchQuest
