#include <gtest/gtest.h>

#include "scale.hpp"

using namespace pitchquest;

const double EPSILON {1e-2};

TEST(ScaleTest, HeptatonicC0) {
    EXPECT_NEAR(Scale::Heptatonic(0, 0), 16.35, EPSILON);
}

TEST(ScaleTest, HeptatonicC8) {
    EXPECT_NEAR(Scale::Heptatonic(0, 8), 4186.0, EPSILON);
}

TEST(ScaleTest, HeptatonicFs3) {
    EXPECT_NEAR(Scale::Heptatonic(6, 3), 185.0, EPSILON);
}

TEST(ScaleTest, HeptatonicA0) {
    EXPECT_NEAR(Scale::Heptatonic(9, 0), 27.5, EPSILON);
}

TEST(ScaleTest, HeptatonicA4) {
    EXPECT_NEAR(Scale::Heptatonic(9, 4), 440.0, EPSILON);
}

TEST(ScaleTest, HeptatonicA5) {
    EXPECT_NEAR(Scale::Heptatonic(9, 5), 880.0, EPSILON);
}

TEST(ScaleTest, HeptatonicAs4) {
    EXPECT_NEAR(Scale::Heptatonic(10, 4), 466.16, EPSILON);
}

TEST(ScaleTest, HeptatonicB0) {
    EXPECT_NEAR(Scale::Heptatonic(11, 0), 30.87, EPSILON);
}

TEST(ScaleTest,HeptatonicB7) {
    EXPECT_NEAR(Scale::Heptatonic(11, 7), 3951.07, EPSILON);
}

TEST(ScaleTest, HeptatonicB8) {
    EXPECT_NEAR(Scale::Heptatonic(11, 8), 7902.13, EPSILON);
}
