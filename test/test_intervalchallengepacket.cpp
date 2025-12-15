#include "gtest/gtest.h"

#include "intervalchallengepacket.hpp"

using namespace PitchQuest;

TEST(IntervalChallengePacketTest, PacketType) {
    EXPECT_EQ(IntervalChallengePacket::packet_type, 0xb1);
}

TEST(IntervalChallengePacketTest, 2valCTOR) {
    IntervalChallengePacket packet {20, 164};    // c4, a4
    EXPECT_EQ(packet.note1, 1);
    EXPECT_EQ(packet.octave1, 4);
    EXPECT_EQ(packet.note2, 10);
    EXPECT_EQ(packet.octave2, 4);
}

TEST(IntervalChallengePacketTest, 4valCTOR) {
    IntervalChallengePacket packet {1, 4, 10, 4};
    EXPECT_EQ(packet.note1, 1);
    EXPECT_EQ(packet.octave1, 4);
    EXPECT_EQ(packet.note2, 10);
    EXPECT_EQ(packet.octave2, 4);
}
