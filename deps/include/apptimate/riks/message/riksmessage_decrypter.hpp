#pragma once

// RIKS++
#include "encrypted_riksmessage.hpp"
#include "riksmessage.hpp"
#include "apptimate/riks/keys/nonce.hpp"
#include "apptimate/riks/keys/symkey.hpp"

// std
#include <functional>

namespace apptimate {
    namespace riks {
        class RiksMessageDecrypter {
        public:
            using DecryptFunction = std::function<RiksMessage(const EncryptedRiksMessage& message)>;

            RiksMessageDecrypter(const SymKey& key, const Nonce& nonce);
            RiksMessageDecrypter(const DecryptFunction& decryptFunction);

            RiksMessage decrypt(const EncryptedRiksMessage& message);

        private:
            static std::string decrypt(const std::string& b64encryptedData,
                                       const SymKey&      key,
                                       const Nonce&       nonce,
                                       const std::string& uid);

            DecryptFunction m_decryptFunction;
        };
    }
}