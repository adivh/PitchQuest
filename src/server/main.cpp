#include <iostream>
#include <string>

#include "logger.hpp"
#include "server.hpp"

int main() {
    PitchQuest::setup_logger();

    PitchQuest::Server server {};
    std::this_thread::sleep_for(std::chrono::seconds(2));
    server.broadcast(PitchQuest::IntervalChallengePacket {(1 << 4) | 2, (3 << 4) | 4});
    server.broadcast(PitchQuest::IntervalChallengePacket {5, 6, 7, 8});
    server.wait();

    return 0;
}
