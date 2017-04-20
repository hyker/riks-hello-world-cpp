#pragma once

// Cryptobox++
namespace hyker { namespace cryptobox {
    class Certificate;
    class KeyStore;
}}

// std
#include <vector>

namespace hyker {
    namespace cryptobox {
        class CertificateValidation {
        public:
            /**
             * Validate a certificate and certificate chain and return the leaf certificate.
             * If certificate chain is valid, the certificate at index 0 in the certificate chain should have been signed by the trust anchor.
             * The certificate at index 1 has been signed by the certificate at index 0, and so on.
             *
             * @param trustStore       holding all trusted root certificates
             * @param certificateChain certificate chain to validate
             * @return <b>true</b> if successful
             */
            static bool validate(const KeyStore& trustStore, const std::vector<Certificate>& certificateChain);
        };
    };
};