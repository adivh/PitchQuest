#pragma once

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <netinet/in.h>
#include <thread>

namespace PitchQuest {

class Server {
    public:
        Server();
        ~Server();

        bool running() { return m_running.load(); }
        void stop();
        void wait();

    private:
        void recv_loop();

        std::thread m_worker;
        std::atomic<bool> m_running;
        std::mutex m_mutex;
        std::condition_variable m_stopped_cv;
        int m_server_socket;
        sockaddr_in m_server_address;
        int m_client_socket;
};

}   // namespace PitchQuest
