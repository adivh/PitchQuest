# PitchQuest
Pitch Quest - A multiplayer ear training cli game

## Features

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
sudo apt install make cmake gcc-14 libspdlog-dev
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

cmake -DCMAKE_CXX_Compiler=g++-14 ..
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
