#include <memory>

#include "alsaaudioplayer.hpp"
#include "client.hpp"
#include "clientpackethandler.hpp"
#include "cliloop.hpp"
#include "logger.hpp"
#include "scale.hpp"

#include <iostream>

using namespace PitchQuest;

void test_alsa(int argc, char* argv[]) {

    if (argc != 2) {
        return;
    }

    std::unique_ptr<AudioPlayer> player {std::make_unique<AlsaAudioPlayer>()};
    std::vector<Note> sequence {
        Note{440.0, std::chrono::duration<double>(2.0)},
        Note{Scale::heptatonic(10, 6), std::chrono::duration<double>(1.0)},
        Note{0.0, std::chrono::duration<double>(2.0)},
        Note{Scale::heptatonic(9, 3), std::chrono::duration<double>(2.0)}
    };
    player->play(sequence);
    player->play(std::vector<Note> {Note{Scale::heptatonic(0,3), std::chrono::duration<double>(5.0)}});

//  no sleep -> nothing gets playes,
//  since end of main is typically reached before the AlsaAudioPlayer worker entered its work loop.
//
//  sleep ends between sequences -> playing sequence is finished, rest gets ignored and worker finishes loop.

    std::this_thread::sleep_for(std::chrono::seconds(atoi(argv[1])));
}

int main() {

    PitchQuest::setup_logger("client.txt");

    AlsaAudioPlayer player;

    ClientPacketHandler handler{player};
    Client client {handler};

    CliLoop cli {};
    cli.register_command("connect", [&client] (std::span<std::string_view>) {
        client.connect();
        return true;
    });
    cli.register_command("quit", [&cli, &client] (std::span<std::string_view>) {
        client.stop();
        cli.stop();
        return true;
    });

    client.wait();
    cli.wait();

    return 0;
}
