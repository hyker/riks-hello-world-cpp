#pragma once

// std
#include <string>

namespace hyker {
    namespace util {
        namespace base64 {
            std::string decode(std::string data);
            std::string encode(const std::string &data);
        }
    }
}