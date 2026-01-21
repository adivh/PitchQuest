#include <iostream>
#include <string>

#include "cliloop.hpp"
#include "logger.hpp"
#include "server.hpp"

int main() {
    PitchQuest::setup_logger("server.txt");

    PitchQuest::Server server {};

    PitchQuest::CliLoop cli {};
    cli.register_command("interval", [&server] (std::span<std::string_view> args) {
        if (args.size() == 2) {
            if (args[0].size() != 1 || args[1].size() != 1) {
                return false;
            }
            uint8_t n[2];
            for (int i {}; i < 2; ++i) {
                switch (args[i][0]) {
                    case 'c':
                        n[i] = 1;
                        break;
                    case 'd':
                        n[i] = 3;
                        break;
                    case 'e':
                        n[i] = 5;
                            break;
                    case 'f':
                        n[i] = 6;
                        break;
                    case 'g':
                        n[i] = 8;
                        break;
                    case 'a':
                        n[i] = 10;
                            break;
                    case 'b':
                        n[i] = 11;
                        break;
                    default:
                        return false;
                }
            }
            server.broadcast(PitchQuest::IntervalChallengePacket {n[0], 4, n[1], 4});
            return true;
        }
        return false;
    });
    cli.register_command("quit", [&cli, &server] (std::span<std::string_view>) {
        server.stop();
        cli.stop();
        return true;
    });

    server.wait();
    cli.stop();
    cli.wait();

    return 0;
}
