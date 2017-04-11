#pragma once

// std
#include <string>
#include <vector>

namespace apptimate {
    namespace util {
        std::string replaceAll(std::string str, const std::string& from, const std::string& to);
        std::vector<std::string> split(const std::string& str, const std::string& delimiter);
        std::vector<std::string> split(const std::string& str, char delimiter);
    }
}