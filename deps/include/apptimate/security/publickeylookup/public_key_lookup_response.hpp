#pragma once

// Cryptobox++
#include "apptimate/security/certificate.hpp"
#include "apptimate/security/key_store.hpp"

// std
#include <string>
#include <vector>

namespace apptimate {
    namespace cryptobox {
        class PublicKeyLookupResponse {
        public:
            /**
             * Creates a public key lookup response.
             *
             * @param ecKey            The public key.
             * @param certificate      The certificate.
             * @param certificateChain The certificate chain.
             */
            PublicKeyLookupResponse(const std::string&              ecKey,
                                    const std::string&              ecKeySign,
                                    const Certificate&              certificate,
                                    const std::vector<Certificate>& certificateChain);

            /**
             * Gets the public key used for encryption of data.
             *
             * @return The key.
             */
            const std::string& getKey() const;

            /**
             * Gets the certificate.
             *
             * @return The certificate.
             */
            const Certificate& getCertificate() const;

            /**
             * Gets the certificate chain.
             *
             * @return The certificate chains.
             */
            const std::vector<Certificate>& getCertificateChain() const;

            /**
             * Validates the correctness of the parameters in the response. i.e. ecKey, certificate, and issuer.
             *
             * @param uid the uid for which the response should validateRegistrationParameters
             * @param trustStore holding all trusted root certificates
             * @param tm custom trust manager (can be null if none has been chosen)
             * @returns <b>true</b> if successfully validated
             */
            bool validate(std::string uid, const KeyStore& trustStore);

        private:
            std::string              m_ecKey;
            std::string              m_ecKeySign;
            Certificate              m_certificate;
            std::vector<Certificate> m_certificateChain;
        };
    };
};