#pragma once

#include <string>

namespace apptimate {
    class Base64 {
    public:
        static std::string decode(std::string data);
        static std::string encode(const std::string& data);
    };
}