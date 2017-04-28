#pragma once

// Toolbox++
#include "../values.hpp"

// std
#include <string>

namespace hyker {
    namespace util {
        namespace json {
            std::string encode(const Values &values);
            Values decode(const std::string &jsonString);
        }
    }
}