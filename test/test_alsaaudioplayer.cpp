#include "gtest/gtest.h"

#include "alsaaudioplayer_testfriend.hpp"

using namespace PitchQuest;
using namespace PitchQuestTest;
using namespace std::chrono_literals;

const Note silent_short {Note{0.0, std::chrono::duration<double>(.1)}};

TEST(AlsaAudioPlayerTest, QueueStartsEmpty) {
    AlsaAudioPlayer player;
    EXPECT_EQ(AlsaAudioPlayer_TestFriend::queue_size(player), 0);
}

TEST(AlsaAudioPlayerTest, QueueIncrementsOnPlay) {
    AlsaAudioPlayer player {};
    player.play(std::vector<Note> {silent_short});
    EXPECT_EQ(AlsaAudioPlayer_TestFriend::queue_size(player), 1);

    player.play(std::vector<Note> {silent_short});
    EXPECT_EQ(AlsaAudioPlayer_TestFriend::queue_size(player), 2);
}

TEST(AlsaAudioPlayerTest, QueueDepletesOverTime) {
    AlsaAudioPlayer player {};
    player.play(std::vector<Note> {silent_short});
    player.play(std::vector<Note> {silent_short});
    EXPECT_EQ(AlsaAudioPlayer_TestFriend::queue_size(player), 2);

    std::this_thread::sleep_for(.1s);
    EXPECT_EQ(AlsaAudioPlayer_TestFriend::queue_size(player), 1);

    std::this_thread::sleep_for(.1s);
    EXPECT_EQ(AlsaAudioPlayer_TestFriend::queue_size(player), 0);
}

TEST(AlsaAudioPlayerTest, MultipleConcurrentPlayCalls) {
    AlsaAudioPlayer player;

    const int num_threads {5};
    const int num_play_per_thread {3};
    std::vector<std::thread> threads(num_threads * num_play_per_thread);

    for (int i {0}; i < num_threads; ++i) {
        threads.emplace_back([&player, num_play_per_thread]() {
            for (int j {0}; j < num_play_per_thread; ++j) {
                player.play(std::vector<Note> {silent_short});
            }
        });
    }

    for (std::thread& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    int waited_ms {};
    const int step_ms {500};
    const int max_waited_ms {3'500};
    while (AlsaAudioPlayer_TestFriend::queue_size(player) > 0 && waited_ms < max_waited_ms) {
        std::this_thread::sleep_for(std::chrono::milliseconds(step_ms));
        waited_ms += step_ms;
    }

    EXPECT_EQ(AlsaAudioPlayer_TestFriend::queue_size(player), 0);
}
