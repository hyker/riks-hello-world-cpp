#pragma once

// RIKS++
#include "signed_riksmessage.hpp"

// std
#include <string>

namespace hyker {
    namespace riks {
        class RiksMessageVerifier {
        public:
            using VerifyFunction = std::function<bool(const std::string& b64Data,
                                                      const std::string& b64Signature,
                                                      const std::string& uid)>;

            RiksMessageVerifier(const VerifyFunction& verifyFunction);

            bool verify(const SignedRiksMessage& message);

        private:
            VerifyFunction m_verifyFunction;
        };
    }
}