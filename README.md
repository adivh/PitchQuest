![Build and Tests](https://github.com/adivh/PitchQuest/actions/workflows/cmake-single-platform.yml/badge.svg)

# PitchQuest
Pitch Quest - A multiplayer ear training cli game

## Implemented Features

### Networking

Simple client/server

### Audio

Async audio player for Linux/Alsa.

### Logging

Configurable logging to console and log file using [spdlog](https://github.com/gabime/spdlog/) under the hood.

## Installation

### Prerequisits

#### Ubuntu

```
sudo apt update
sudo apt install build-essential cmake libspdlog-dev
```

#### Arch Linux

```
sudo pacman -S base-devel cmake spdlog
```

### Building

#### Ubuntu
```
git clone --recurse-submodules https://github.com/adivh/PitchQuest.git

mkdir PitchQuest/build
cd PitchQuest/build

cmake ..
make -j`nproc`
```

#### Arch Linux
```
git clone --recurse-submodules https://github.com/adivh/PitchQuest.git

mkdir PitchQuest/build
cd PitchQuest/build

cmake ..
make -j`nproc`
```

### Usage
