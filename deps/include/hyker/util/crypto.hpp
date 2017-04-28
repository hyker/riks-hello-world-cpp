#pragma once

// Cryptobox++
#include "../key_pair.hpp"

// Core (Toolbox++)
#include "hyker/exception.hpp"

// std
#include <string>

namespace hyker {
    namespace util {

        constexpr int NONCE_LENGTH = 32;
        constexpr int KEY_LENGTH = 32;
        constexpr int TAG_LENGTH = 16;

        class GenerationFailedException : public hyker::Exception {
        public:
            GenerationFailedException(const std::string& what) : hyker::Exception(what) {}
        };

        std::string generateNonce();
        std::string generateKey();
        std::string generateRandom(int length);

        std::string encrypt(const std::string& key, const std::string& data);
        std::string encrypt(const std::string& key, const std::string& data, const std::string& nonce, int mac_size = TAG_LENGTH, const std::string& aad = "");

        std::string decrypt(const std::string& key, const std::string& nonce_and_ciphertext);
        std::string decrypt(const std::string& key, const std::string& ciphertext, const std::string& nonce, int mac_size = TAG_LENGTH, const std::string& aad = "");

        KeyPair loadKeys(const std::string& path, const std::string& password);
        void storeKeys(const KeyPair& key_pair, const std::string& path, const std::string& password);
        bool hasKeys(const std::string& path);

    };
};