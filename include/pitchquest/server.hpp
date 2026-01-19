#ifndef PITCHQUEST_SERVER_HPP_
#define PITCHQUEST_SERVER_HPP_

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <netinet/in.h>
#include <thread>

#include "intervalchallengepacket.hpp"

namespace PitchQuest {

class Server {
    public:
        Server();
        ~Server();

        void broadcast(IntervalChallengePacket packet) const;
        bool running() const { return m_running.load(); }
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

#endif  // PITCHQUEST_CLI_HPP_
