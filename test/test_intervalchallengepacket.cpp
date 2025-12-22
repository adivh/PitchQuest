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

TEST(IntervalChallengePacketTest, to_bytesSize) {
    IntervalChallengePacket packet {1, 4, 10, 4};
    EXPECT_EQ(packet.to_bytes().size(), 3);
}

TEST(IntervalChallengePacketTest, to_bytesData2valCTOR) {
    IntervalChallengePacket p1 {0x14, 0xa4};   // c4, a4
    IntervalChallengePacket p2 {0x33, 0xa3};   // d3, a3
    EXPECT_EQ(p1.to_bytes().at(0), 0xb1);
    EXPECT_EQ(p1.to_bytes().at(1), 0x14);
    EXPECT_EQ(p1.to_bytes().at(2), 0xa4);
    EXPECT_EQ(p2.to_bytes().data()[0], 0xb1);
    EXPECT_EQ(p2.to_bytes().data()[1], 0x33);
    EXPECT_EQ(p2.to_bytes().data()[2], 0xa3);
}

TEST(IntervalChallengePacketTest, to_bytesData4valCTOR) {
    IntervalChallengePacket p1 {1, 4, 10, 4};   // c4, a4
    IntervalChallengePacket p2 {3, 3, 10, 3};   // d3, a3
    EXPECT_EQ(p1.to_bytes().at(0), 0xb1);
    EXPECT_EQ(p1.to_bytes().at(1), 0x14);
    EXPECT_EQ(p1.to_bytes().at(2), 0xa4);
    EXPECT_EQ(p2.to_bytes().data()[0], 0xb1);
    EXPECT_EQ(p2.to_bytes().data()[1], 0x33);
    EXPECT_EQ(p2.to_bytes().data()[2], 0xa3);
}

TEST(IntervalChallengePacketTest, to_string) {
    IntervalChallengePacket packet {1, 4, 10, 4};
    EXPECT_EQ(packet.to_string(), std::string("type: ") + std::to_string(IntervalChallengePacket::packet_type) + ", note1: 1, octave1: 4, note2: 10, octave2: 4");
}
