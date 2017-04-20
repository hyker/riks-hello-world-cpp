#pragma once

// std
#include <string>

namespace hyker {
    namespace cryptobox {
        class SecurityUtil {
        public:
            static std::string generateString(int length);
        };
    };
};