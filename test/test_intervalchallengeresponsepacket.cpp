#include "gtest/gtest.h"

#include "intervalchallengeresponsepacket.hpp"

using namespace PitchQuest;

TEST(IntervalChallengeResponsePacketTest, PacketType) {
    EXPECT_EQ(IntervalChallengeResponsePacket::packet_type, 0x21);
}

TEST(IntervalChallengeResponsePacketTest, 2valCTOR) {
    IntervalChallengeResponsePacket packet {0x1a, 0x0a};    // cn-an
    EXPECT_EQ(packet.note1, 1);
    EXPECT_EQ(packet.note2, 10);
    EXPECT_EQ(packet.octave_difference, 0);
    EXPECT_EQ(packet.response, 10);
}

TEST(IntervalChallengeResponsePacketTest, 4valCTOR) {
    IntervalChallengeResponsePacket packet {1, 10, 0, 10};
    EXPECT_EQ(packet.note1, 1);
    EXPECT_EQ(packet.note2, 10);
    EXPECT_EQ(packet.octave_difference, 0);
    EXPECT_EQ(packet.response, 10);
}

TEST(IntervalChallengeResponsePacketTest, to_bytesSize) {
    IntervalChallengeResponsePacket packet {1, 10, 0, 10};
    EXPECT_EQ(packet.to_bytes().size(), 3);
}

TEST(IntervalChallengeResponsePacketTest, to_bytesData2valCTOR) {
    IntervalChallengeResponsePacket p1 {0x1a, 0x0a};   // cn-an
    IntervalChallengeResponsePacket p2 {0x33, 0x1d};   // dn, d(n+1)
    EXPECT_EQ(p1.to_bytes().at(0), 0x21);
    EXPECT_EQ(p1.to_bytes().at(1), 0x1a);
    EXPECT_EQ(p1.to_bytes().at(2), 0x0a);
    EXPECT_EQ(p2.to_bytes().data()[0], 0x21);
    EXPECT_EQ(p2.to_bytes().data()[1], 0x33);
    EXPECT_EQ(p2.to_bytes().data()[2], 0x1d);
}

TEST(IntervalChallengeResponsePacketTest, to_bytesData4valCTOR) {
    IntervalChallengeResponsePacket p1 {0x1, 0xa, 0x0, 0xa};   // cn-an
    IntervalChallengeResponsePacket p2 {0x3, 0x3, 0x1, 0xd};   // dn, d(n+1)
    EXPECT_EQ(p1.to_bytes().at(0), 0x21);
    EXPECT_EQ(p1.to_bytes().at(1), 0x1a);
    EXPECT_EQ(p1.to_bytes().at(2), 0x0a);
    EXPECT_EQ(p2.to_bytes().data()[0], 0x21);
    EXPECT_EQ(p2.to_bytes().data()[1], 0x33);
    EXPECT_EQ(p2.to_bytes().data()[2], 0x1d);
}

TEST(IntervalChallengeResponsePacketTest, to_string) {
    IntervalChallengeResponsePacket packet {1, 10, 0, 10};
    EXPECT_EQ(packet.to_string(), std::string("type: ") + std::to_string(IntervalChallengeResponsePacket::packet_type) + ", note1: 1, note2: 10, octave_difference: 0, response: 10");
}
