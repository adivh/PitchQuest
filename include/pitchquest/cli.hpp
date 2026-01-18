#pragma once

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

namespace PitchQuest::cli {

    inline const char delimiter = ' ';

    inline void sanitize(std::string& command) {
        std::transform(command.begin(), command.end(), command.begin(), [](unsigned char c){ return std::tolower(c); });
    }

    inline std::string sanitize(std::string&& command) {
        std::string s {command};
        sanitize(s);
        return s;
    }
    
}   // namespace PitchQuest::cli
