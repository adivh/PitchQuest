#include <memory>
#include <print>

#include "alsaaudioplayer.hpp"
#include "client.hpp"
#include "logger.hpp"
#include "scale.hpp"

using namespace PitchQuest;

void test_alsa(int argc, char* argv[]) {

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

    if (argc == 2) {
        std::this_thread::sleep_for(std::chrono::seconds(atoi(argv[1])));
    }
}

int main(int argc, char* argv[]) {

    PitchQuest::setup_logger();

    test_alsa(argc, argv);

    Client client {};
    client.send("Hello from client!", 19);

    std::this_thread::sleep_for(std::chrono::seconds(5));

    client.send("Good bye!", 9);

    return 0;
}
