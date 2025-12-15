#include <iostream>
#include <string>

#include "logger.hpp"
#include "server.hpp"

int main() {
    PitchQuest::setup_logger();

    PitchQuest::Server server {};
    server.wait();

    return 0;
}
