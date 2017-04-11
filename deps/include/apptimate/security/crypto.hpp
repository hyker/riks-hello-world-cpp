#pragma once

// Cryptobox++
#include "apptimate/cryptobox/exception.hpp"
namespace apptimate { namespace cryptobox {
    class KeyPair;
}}

// std
#include <string>

namespace apptimate {
    namespace cryptobox {
        class Crypto {
        public:
            class Exception : public apptimate::cryptobox::Exception {
            public:
                Exception(const std::string& what) : apptimate::cryptobox::Exception(what) {}
            };

            class GenerationFailedException : public Exception {
            public:
                GenerationFailedException(const std::string& what) : Exception(what) {}
            };

            static std::string generateNonce();
            static std::string generateKey();
            static std::string generateRandom(int length);

            static std::string encrypt(const std::string& key, const std::string& data);
            static std::string encrypt(const std::string& key,
                                       const std::string& data,
                                       const std::string& nonce,
                                       int                macSize = TAG_LENGTH,
                                       const std::string& aad = "");

            static std::string decrypt(const std::string& key, const std::string& nonceAndCipherText);
            static std::string decrypt(const std::string& key,
                                       const std::string& cipherText,
                                       const std::string& nonce,
                                       int                macSize = TAG_LENGTH,
                                       const std::string& aad = "");

            static KeyPair loadKeys(const std::string& cryptoKeyPath, const std::string& cryptoKeyPassword);
            static void storeKeys(const KeyPair& keyPair, const std::string& cryptoKeyPath, const std::string& cryptoKeyPassword);
            static bool hasKeys(const std::string& path);

        private:
            static std::string generateKeyFromPassword(const std::string& path, const std::string& cryptoKeyPassword);

            const static int NONCE_LENGTH;
            const static int KEY_LENGTH;
            const static int TAG_LENGTH;

            const static std::string PRIVATE_KEY_EXTENSION;
            const static std::string PUBLIC_KEY_EXTENSION;
            const static std::string SALT_EXTENSION;
        };
    };
};