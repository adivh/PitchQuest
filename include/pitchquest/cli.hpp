#pragma once

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

namespace PitchQuest::cli {

    /**
     *  Value is used to improve performance by avoiding allocations.
     *  Changing to any positive value or zero is safe.
     */
    inline const int heuristic_command_token_count {3};

    inline const char delimiter {' '};

    inline void sanitize(std::string& command) {
        std::transform(command.begin(), command.end(), command.begin(), [](unsigned char c){ return std::tolower(c); });
    }

    inline std::string sanitize(std::string&& command) {
        std::string s {command};
        sanitize(s);
        return s;
    }

    inline std::vector<std::string> tokenize(std::string_view command) {
        std::vector<std::string> tokens {};
        tokens.reserve(heuristic_command_token_count);

        size_t index_start {};
        size_t index_end {};

        while (index_start < command.size()) {
            index_end = command.find(delimiter, index_start);

            if (index_end == std::string::npos) {
                tokens.emplace_back(command.substr(index_start, command.size() - index_start));
                return tokens;
            } else if (index_end > index_start) {
                tokens.emplace_back(command.substr(index_start, index_end - index_start));
                index_start += index_end - index_start;
            } else {
                index_start++;
            }
        }

        return tokens;
    }
    
}   // namespace PitchQuest::cli
