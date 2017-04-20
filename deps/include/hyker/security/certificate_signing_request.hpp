#pragma once

// Cryptobox++
#include "hyker/cryptobox/exception.hpp"

// std
#include <string>

namespace hyker {
    namespace cryptobox {
        class CertificateSigningRequest {
        public:
            class Exception : public hyker::cryptobox::Exception {
            public:
                Exception(const std::string& what) : hyker::cryptobox::Exception(what) {}
            };

            /**
             * Certificate Signing Request constructor.
             * Generates keypair, creates a certificate signing request, and stores it as PEM.
             *
             * @param uid - the name of the subject of the certificate signing request
             */
            CertificateSigningRequest(const std::string& uid);

            /**
             * Returns the PEM representation.
             *
             * @return the PEM representation of the certificate signing request.
             */
            const std::string& getEncoded() const;

            /**
             * Returns the user ID of the subject.
             *
             * @return the user ID of the subject.
             */
            const std::string& getUID() const;

            /**
             * Returns the public key.
             *
             * @return the public key of the certificate signing request.
             */
            const std::string& getPublicKey() const;

            /**
             * Returns the private key.
             *
             * @return the private key of the certificate signing request.
             */
            const std::string& getPrivateKey() const;

        private:
            std::string m_encoded;
            std::string m_userID;
            std::string m_publicKey;
            std::string m_privateKey;
        };
    };
};