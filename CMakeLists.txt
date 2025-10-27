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
option(PITCHQUEST_ENABLE_AUDIO_TESTS "Enable tests that require audio" ON)

# -------------------------------------------------
# Compiler settings
# -------------------------------------------------
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -------------------------------------------------
# Sources
# -------------------------------------------------
add_executable(PitchQuestClient
    src/client/alsaaudioplayer.cpp
    src/client/client.cpp
    src/client/main.cpp
    src/common/logger.cpp
)

add_executable(PitchQuestServer
    src/common/logger.cpp
    src/server/main.cpp
    src/server/server.cpp
)

if (MSVC)
    target_compile_options(PitchQuestClient PRIVATE /W4 /permissive-)
    target_compile_options(PitchQuestServer PRIVATE /W4 /permissive-)
else()
    target_compile_options(PitchQuestClient PRIVATE -Wall -Wextra -Wpedantic -lasound)
    target_compile_options(PitchQuestServer PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_include_directories(PitchQuestClient PRIVATE include/pitchquest)
target_include_directories(PitchQuestServer PRIVATE include/pitchquest)

find_package(ALSA REQUIRED)
target_link_libraries(PitchQuestClient PRIVATE ALSA::ALSA)

find_package(spdlog REQUIRED)
target_link_libraries(PitchQuestClient PRIVATE spdlog::spdlog)
target_link_libraries(PitchQuestServer PRIVATE spdlog::spdlog)

# -------------------------------------------------
# Testing
# -------------------------------------------------
if (PITCHQUEST_BUILD_TESTS)
    enable_testing()

    add_subdirectory(extern/googletest)

    # Collect test sources
    set(PITCHQUEST_TEST_SOURCES
        test/test_ringbuffer.cpp
        test/test_scale.cpp
    )

    if(PITCHQUEST_ENABLE_AUDIO_TESTS)
        list(APPEND PITCHQUEST_TEST_SOURCES
            src/client/alsaaudioplayer.cpp
            test/test_alsaaudioplayer.cpp
        )
        message(STATUS "Audio tests enabled.")
    else()
        message(STATUS "Audio tests disabled.")
    endif()

    add_executable(PitchQuestTests
        ${PITCHQUEST_TEST_SOURCES}
    )


    target_link_libraries(PitchQuestTests
        gtest_main
        ALSA::ALSA
        spdlog::spdlog
    )

    target_include_directories(PitchQuestTests
        PRIVATE include/pitchquest
        PRIVATE test/
    )

    include(GoogleTest)
    gtest_discover_tests(PitchQuestTests)
endif()
