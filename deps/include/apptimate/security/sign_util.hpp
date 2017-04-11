#pragma once

// Cryptobox++
#include "apptimate/cryptobox/exception.hpp"

// std
#include <string>

namespace apptimate {
    namespace cryptobox {
        class SignUtil {
        public:
            class SigningFailedException : public apptimate::cryptobox::Exception {
            public:
                SigningFailedException() : SigningFailedException("Signing failed.") {}
                SigningFailedException(const std::string& what) : apptimate::cryptobox::Exception(what) {}
            };

            class VerificationFailedException : public apptimate::cryptobox::Exception {
            public:
                VerificationFailedException() : VerificationFailedException("Verification failed.") {}
                VerificationFailedException(const std::string& what) : apptimate::cryptobox::Exception(what) {}
            };

            /**
             * Signs a public key using a private key.
             *
             * @param publicKey  The public key.
             * @param privateKey The private key.
             * @throws SigningFailedException
             * @return The signature.
             */
            static std::string signData(const std::string& publicKey,
                                        const std::string& privateKey);

            /**
            * Verifies that a public key has been correctly signed by a public signing key.
            *
            * @param publicKey        The public key.
            * @param signature        The signature.
            * @param publicSigningKey The public signing key.
            * @throws VerificationFailedException
            * @return <b>true</b> if successful.
            */
            static bool verifySignature(const std::string& publicKey,
                                        const std::string& signature,
                                        const std::string& publicSigningKey);
        };
    };
};