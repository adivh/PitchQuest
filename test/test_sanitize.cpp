#include <gtest/gtest.h>

#include "cli.hpp"

TEST(SanitizeTest, Empty) {
    std::string s {PitchQuest::cli::sanitize("")};
    EXPECT_EQ(s, "");
}

TEST(SanitizeTest, AllLowerCase) {
    std::string s {PitchQuest::cli::sanitize("lower")};
    EXPECT_EQ(s, "lower");
}

TEST(SanitizeTest, AllUpperCase) {
    std::string s {PitchQuest::cli::sanitize("UPPER")};
    EXPECT_EQ(s, "upper");
}

TEST(SanitizeTest, MixedCase) {
    std::string s {PitchQuest::cli::sanitize("mIxEd")};
    EXPECT_EQ(s, "mixed");
}
