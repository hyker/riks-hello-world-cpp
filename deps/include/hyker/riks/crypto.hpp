#pragma once

// RIKS++
#include "hyker/riks/keys/nonce.hpp"
#include "hyker/riks/keys/symkey.hpp"

// std
#include <string>

namespace hyker {
    namespace riks {
        class Crypto {
        public:
            static std::string encrypt(const std::string& data,
                                       const SymKey&      key,
                                       const Nonce&       nonce,
                                       const std::string& uid);

            static std::string decrypt(const std::string& encryptedData,
                                       const SymKey&      key,
                                       const Nonce&       nonce,
                                       const std::string& uid);

        private:
            static std::string getIV(const SymKey& key, const Nonce& nonce);
            static std::string getAAD(const std::string& uid);
        };
    }
}