# ====================================================================
# Pitch Quest - A multiplayer ear training game
# Copyright (c) 2025 <Your Name>
#
# Licensed under the MIT License. See LICENSE file in the project root
# for full license information.
# ====================================================================

cmake_minimum_required(VERSION 3.15)

# -------------------------------------------------
# Project setup
# -------------------------------------------------
project(PitchQuest
    VERSION 0.1.0
    LANGUAGES CXX
)

# -------------------------------------------------
# Options
# -------------------------------------------------
option(PITCHQUEST_BUILD_TESTS "Build Pitch Quest tests" ON)

# -------------------------------------------------
# Compiler settings
# -------------------------------------------------
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# -------------------------------------------------
# Sources
# -------------------------------------------------
add_executable(PitchQuestServer
    src/server/main.cpp
)

# -------------------------------------------------
# Includes
# -------------------------------------------------
target_include_directories(PitchQuestServer
    PRIVATE include/pitchquest
)

# -------------------------------------------------
# Testing
# -------------------------------------------------
if (PITCHQUEST_BUILD_TESTS)
    enable_testing()

    add_subdirectory(extern/googletest)

    add_executable(PitchQuestTests
        test/test_scale.cpp
    )

    target_link_libraries(PitchQuestTests
        gtest_main
    )

    target_include_directories(PitchQuestTests
        PRIVATE include/pitchquest
    )

    include(GoogleTest)
    gtest_discover_tests(PitchQuestTests)
endif()
