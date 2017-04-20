#pragma once

// Cryptobox++
#include "hyker/cryptobox/exception.hpp"
namespace hyker { namespace cryptobox {
    class KeyPair;
}}

// std
#include <string>

namespace hyker {
    namespace cryptobox {
        class KeyAgreement {
        public:
            class KeyAgreementFailedException : public Exception {
            public:
                KeyAgreementFailedException(const std::string& what) : Exception(what) {}
            };

            /**
             * Generates a secret key using a public key and a private key.
             * Uses a NIST/X9.62/SECG curve over a 192 bit prime field.
             *
             * @param publicKey  The public key.
             * @param privateKey The private key.
             * @param sessionKey The session key.
             *
             * @return <b>true</b> if successful.
             */
            static std::string doKeyAgreement(const std::string& publicKey, const std::string& privateKey);

            /**
            * Generates a public and private key.
            * Uses a NIST/X9.62/SECG curve over a 192 bit prime field.
            *
            * @param publicKey  The public key.
            * @param privateKey The private key.
            *
            * @return <b>true</b> if successful.
            */
            static KeyPair getKeyPair();
        };
    };
};