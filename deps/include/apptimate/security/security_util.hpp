#pragma once

// std
#include <string>

namespace apptimate {
    namespace cryptobox {
        class SecurityUtil {
        public:
            static std::string generateString(int length);
        };
    };
};