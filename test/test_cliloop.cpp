#include <gtest/gtest.h>

#include "cliloop.hpp"

TEST(CliLoopTest, NewCliLoopIsEmpty) {
    PitchQuest::CliLoop cli {};

    EXPECT_EQ(cli.count_commands(), 0);
}

TEST(CliLoopTest, RegisterUniqueCommands) {
    PitchQuest::CliLoop cli {};
    cli.register_command("do_nothing", [] (std::span<std::string_view>) { return true; });

    EXPECT_EQ(cli.count_commands(), 1);
    EXPECT_EQ(cli.has_command("do_nothing"), true);

    cli.register_command("no_op", [] (std::span<std::string_view>) { return true; });

    EXPECT_EQ(cli.count_commands(), 2);
    EXPECT_EQ(cli.has_command("no_op"), true);
}

TEST(CliLoopTest, RegisterDuplicateCommands) {
    PitchQuest::CliLoop cli {};
    cli.register_command("do_nothing", [] (std::span<std::string_view>) { return true; });
    cli.register_command("do_nothing", [] (std::span<std::string_view>) { return true; });

    EXPECT_EQ(cli.count_commands(), 1);
    EXPECT_EQ(cli.has_command("do_nothing"), true);
}

TEST(CliLoopTest, FindCommandInEmptyCliLoop) {
    PitchQuest::CliLoop cli {};

    EXPECT_EQ(cli.has_command("do_nothing"), false);
}

TEST(CliLoopTest, FindMissingCommandInCliLoop) {
    PitchQuest::CliLoop cli {};
    cli.register_command("do_nothing", [] (std::span<std::string_view>) { return true; });

    EXPECT_EQ(cli.has_command("missing_command"), false);
}

TEST(CliLoopTest, UnregisterCommandInEmptyCliLoop) {
    PitchQuest::CliLoop cli {};
    cli.unregister_command("missing");

    EXPECT_EQ(cli.count_commands(), 0);
    EXPECT_EQ(cli.has_command("missing"), false);
}

TEST(CliLoopTest, UnregisterExistingCommand) {
    PitchQuest::CliLoop cli {};
    cli.register_command("do_nothing", [] (std::span<std::string_view>) { return true; });
    cli.unregister_command("do_nothing");

    EXPECT_EQ(cli.count_commands(), 0);
    EXPECT_EQ(cli.has_command("do_nothing"), false);
}

TEST(CliLoopTest, UnregisterMissingCommand) {
    PitchQuest::CliLoop cli {};
    cli.register_command("do_nothing", [] (std::span<std::string_view>) { return true; });
    cli.unregister_command("missing");

    EXPECT_EQ(cli.count_commands(), 1);
    EXPECT_EQ(cli.has_command("do_nothing"), true);
    EXPECT_EQ(cli.has_command("missing"), false);
}

TEST(CliLoopTest, IsRunning) {
    PitchQuest::CliLoop cli {};

    EXPECT_EQ(cli.is_running(), true);
}

TEST(CliLoopTest, IsRunningAfterStop) {
    PitchQuest::CliLoop cli {};
    cli.stop();

    EXPECT_EQ(cli.is_running(), false);
}

TEST(CliLoopTest, StopAndWait) {
    PitchQuest::CliLoop cli{};
    cli.stop();
    cli.wait();

    EXPECT_EQ(cli.is_running(), false);
    EXPECT_EQ(cli.is_stopped(), true);
}
