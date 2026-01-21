#include <gtest/gtest.h>

#include <sstream>

#include "cliloop.hpp"

TEST(CliLoopTest, NewCliLoopIsEmpty) {
    PitchQuest::CliLoop cli {std::cin, false};

    EXPECT_EQ(cli.count_commands(), 0);
}

TEST(CliLoopTest, RegisterUniqueCommands) {
    PitchQuest::CliLoop cli {std::cin, false};
    cli.register_command("do_nothing", [] (std::span<std::string_view>) { return true; });

    EXPECT_EQ(cli.count_commands(), 1);
    EXPECT_EQ(cli.has_command("do_nothing"), true);

    cli.register_command("no_op", [] (std::span<std::string_view>) { return true; });

    EXPECT_EQ(cli.count_commands(), 2);
    EXPECT_EQ(cli.has_command("no_op"), true);
}

TEST(CliLoopTest, RegisterDuplicateCommands) {
    PitchQuest::CliLoop cli {std::cin, false};
    cli.register_command("do_nothing", [] (std::span<std::string_view>) { return true; });
    cli.register_command("do_nothing", [] (std::span<std::string_view>) { return true; });

    EXPECT_EQ(cli.count_commands(), 1);
    EXPECT_EQ(cli.has_command("do_nothing"), true);
}

TEST(CliLoopTest, FindCommandInEmptyCliLoop) {
    PitchQuest::CliLoop cli {std::cin, false};

    EXPECT_EQ(cli.has_command("do_nothing"), false);
}

TEST(CliLoopTest, FindMissingCommandInCliLoop) {
    PitchQuest::CliLoop cli {std::cin, false};
    cli.register_command("do_nothing", [] (std::span<std::string_view>) { return true; });

    EXPECT_EQ(cli.has_command("missing_command"), false);
}

TEST(CliLoopTest, UnregisterCommandInEmptyCliLoop) {
    PitchQuest::CliLoop cli {std::cin, false};
    cli.unregister_command("missing");

    EXPECT_EQ(cli.count_commands(), 0);
    EXPECT_EQ(cli.has_command("missing"), false);
}

TEST(CliLoopTest, UnregisterExistingCommand) {
    PitchQuest::CliLoop cli {std::cin, false};
    cli.register_command("do_nothing", [] (std::span<std::string_view>) { return true; });
    cli.unregister_command("do_nothing");

    EXPECT_EQ(cli.count_commands(), 0);
    EXPECT_EQ(cli.has_command("do_nothing"), false);
}

TEST(CliLoopTest, UnregisterMissingCommand) {
    PitchQuest::CliLoop cli {std::cin, false};
    cli.register_command("do_nothing", [] (std::span<std::string_view>) { return true; });
    cli.unregister_command("missing");

    EXPECT_EQ(cli.count_commands(), 1);
    EXPECT_EQ(cli.has_command("do_nothing"), true);
    EXPECT_EQ(cli.has_command("missing"), false);
}

TEST(CliLoopTest, IsRunning) {
    std::istringstream input {};
    PitchQuest::CliLoop cli {input};

    EXPECT_EQ(cli.is_running(), true);

    cli.stop();
    input.str("\n");
    input.clear();

    EXPECT_EQ(cli.is_running(), false);
}

TEST(CliLoopTest, StopAndWait) {
    std::istringstream input {};
    PitchQuest::CliLoop cli {input};
    cli.stop();
    input.str("\n");
    input.clear();
    cli.wait();

    SUCCEED();
}

TEST(CliLoopTest, IsStopped) {
    std::istringstream input {};
    PitchQuest::CliLoop cli {input};

    EXPECT_EQ(cli.is_stopped(), false);

    cli.stop();
    input.str("\n");
    input.clear();

    cli.wait();

    EXPECT_EQ(cli.is_stopped(), true);
}

TEST(CliLoopTest, CanQuitViaCommand) {
    std::istringstream input {};
    PitchQuest::CliLoop cli {input};
    cli.register_command("quit", [&cli] (std::span<std::string_view>) { cli.stop(); return true; });

    input.str("quit\n");
    input.clear();

    cli.wait();
    SUCCEED();
}
