#pragma once

// RIKS++
#include "encrypted_riksmessage.hpp"
#include "signed_riksmessage.hpp"

// std
#include <functional>
#include <string>

namespace hyker {
    namespace riks {
        class RiksMessageSigner {
        public:
            using SignFunction = std::function<std::string(const std::string& b64Data)>;

            RiksMessageSigner(const SignFunction& signFunction);

            SignedRiksMessage sign(const EncryptedRiksMessage& message);

        private:
            SignFunction m_signFunction;
        };
    }
}