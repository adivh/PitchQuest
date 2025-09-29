#include <gtest/gtest.h>

#include "scale.hpp"

using namespace PitchQuest;

const double epsilon {1.0e-2};

TEST(ScaleTest, heptatonicC0) {
    EXPECT_NEAR(Scale::heptatonic(0, 0), 16.35, epsilon);
}

TEST(ScaleTest, heptatonicC8) {
    EXPECT_NEAR(Scale::heptatonic(0, 8), 4186.0, epsilon);
}

TEST(ScaleTest, heptatonicFs3) {
    EXPECT_NEAR(Scale::heptatonic(6, 3), 185.0, epsilon);
}

TEST(ScaleTest, heptatonicA0) {
    EXPECT_NEAR(Scale::heptatonic(9, 0), 27.5, epsilon);
}

TEST(ScaleTest, heptatonicA4) {
    EXPECT_NEAR(Scale::heptatonic(9, 4), 440.0, epsilon);
}

TEST(ScaleTest, heptatonicA5) {
    EXPECT_NEAR(Scale::heptatonic(9, 5), 880.0, epsilon);
}

TEST(ScaleTest, heptatonicAs4) {
    EXPECT_NEAR(Scale::heptatonic(10, 4), 466.16, epsilon);
}

TEST(ScaleTest, heptatonicB0) {
    EXPECT_NEAR(Scale::heptatonic(11, 0), 30.87, epsilon);
}

TEST(ScaleTest,heptatonicB7) {
    EXPECT_NEAR(Scale::heptatonic(11, 7), 3951.07, epsilon);
}

TEST(ScaleTest, heptatonicB8) {
    EXPECT_NEAR(Scale::heptatonic(11, 8), 7902.13, epsilon);
}
