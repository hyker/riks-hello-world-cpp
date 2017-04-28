#pragma once

// std
#include <string>

namespace hyker {
    namespace util {
        namespace random {
            std::string generateString(int length, const std::string&character_set = "abcdefghijklmnopqrstuvwzyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
        }
    }
}