#pragma once

// Cryptobox++
namespace hyker { namespace cryptobox {
    class Certificate;
}}

// Toolbox++
namespace hyker {
    class Values;
}

// std
#include <string>

namespace hyker {
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