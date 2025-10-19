#include <iostream>
#include <string>

#include "logger.hpp"
#include "server.hpp"

int main() {
    PitchQuest::setup_logger();

    PitchQuest::Server server {};

    std::string s {};
    while (s != "exit") {
        std::getline(std::cin, s);
    }

    return 0;
}
