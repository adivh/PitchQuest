# PitchQuest
Pitch Quest - A multiplayer ear training game

## Features

## Installation

### Prerequisits

#### Ubuntu

```
sudo apt update
sudo apt install make cmake gcc-14 libspdlog-dev
```

#### Arch

```
sudo pacman -S base-devel cmake spdlog
```

### Building

#### Ubuntu
```
git clone --recurse-submodules https://github.com/adivh/PitchQuest.git

mkdir PitchQuest/build
cd PitchQuest/build

cmake -DCMAKE\_CXX\_Compiler=g++-14 ..
make -j`nproc`
```

#### Arch
```
git clone --recurse-submodules https://github.com/adivh/PitchQuest.git

mkdir PitchQuest/build
cd PitchQuest/build

cmake ..
make -j`nproc`
```

### Usage
