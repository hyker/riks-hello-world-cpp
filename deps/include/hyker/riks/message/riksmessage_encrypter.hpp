#pragma once

// RIKS++
#include "encrypted_riksmessage.hpp"
#include "riksmessage.hpp"
#include "hyker/riks/keys/nonce.hpp"
#include "hyker/riks/keys/symkey.hpp"

// std
#include <functional>

namespace hyker {
    namespace riks {
        class RiksMessageEncrypter {
        public:
            using EncryptFunction = std::function<EncryptedRiksMessage(const RiksMessage& message)>;

            RiksMessageEncrypter(const SymKey& key, const Nonce& nonce);
            RiksMessageEncrypter(const EncryptFunction& encryptFunction);

            EncryptedRiksMessage encrypt(const RiksMessage& message);

        private:
            static std::string encrypt(const std::string& data,
                                       const SymKey&      key,
                                       const Nonce&       nonce,
                                       const std::string& uid);

            EncryptFunction m_encryptFunction;
        };
    }
}