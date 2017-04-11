#pragma once

// Cryptobox++
namespace apptimate { namespace cryptobox {
    class Certificate;
}}

// Toolbox++
namespace apptimate {
    class Values;
}

// std
#include <string>

namespace apptimate {
    namespace cryptobox {
        class HandshakeSigner {
        public:
            static std::string sign(const Values& payload, const std::string& privateKey);
            static bool verify(const Values& payload, const Certificate& certificate);

        private:
            static std::string generateHSConcatenatedString(const Values& payload);
        };
    };
};