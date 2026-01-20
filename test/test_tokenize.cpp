#include <gtest/gtest.h>

#include "cli.hpp"

TEST(TokenizeTest, TokenizeEmpty) {
    std::vector<std::string> tokens {PitchQuest::cli::tokenize_copy("")};
    EXPECT_EQ(tokens.size(), 0);
}

TEST(TokenizeTest, TokenizeOneSpace) {
    std::vector<std::string> tokens {PitchQuest::cli::tokenize_copy(" ")};
    EXPECT_EQ(tokens.size(), 0);
}

TEST(TokenizeTest, TokenizeThreeSpaces) {
    std::vector<std::string> tokens {PitchQuest::cli::tokenize_copy("   ")};
    EXPECT_EQ(tokens.size(), 0);
}

TEST(TokenizeTest, TokenizeOne) {
    std::vector<std::string> tokens_quit {PitchQuest::cli::tokenize_copy("quit")};
    EXPECT_EQ(tokens_quit.size(), 1);
    EXPECT_EQ(tokens_quit[0], "quit");
    
    std::vector<std::string> tokens_exit {PitchQuest::cli::tokenize_copy("exit")};
    EXPECT_EQ(tokens_exit.size(), 1);
    EXPECT_EQ(tokens_exit[0], "exit");
}

TEST(TokenizeTest, TokenizeOneLeadingSpace) {
    std::vector<std::string> tokens {PitchQuest::cli::tokenize_copy(" leading")};
    EXPECT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0], "leading");
}

TEST(TokenizeTest, TokenizeOneTrailingSpace) {
    std::vector<std::string> tokens {PitchQuest::cli::tokenize_copy("trailing ")};
    EXPECT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0], "trailing");
}

TEST(TokenizeTest, TokenizeSentence) {
    std::vector<std::string> tokens {PitchQuest::cli::tokenize_copy("A good listener is a silent flatterer")};
    EXPECT_EQ(tokens.size(), 7);
    EXPECT_EQ(tokens[0], "A");
    EXPECT_EQ(tokens[1], "good");
    EXPECT_EQ(tokens[2], "listener");
    EXPECT_EQ(tokens[3], "is");
    EXPECT_EQ(tokens[4], "a");
    EXPECT_EQ(tokens[5], "silent");
    EXPECT_EQ(tokens[6], "flatterer");
}

TEST(TokenizeTest, TokenizeSentenceExcessSpaces) {
    std::vector<std::string> tokens {PitchQuest::cli::tokenize_copy("   All that   glitters  ")};
    EXPECT_EQ(tokens.size(), 3);
    EXPECT_EQ(tokens[0], "All");
    EXPECT_EQ(tokens[1], "that");
    EXPECT_EQ(tokens[2], "glitters");
}
