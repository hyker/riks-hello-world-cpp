#pragma once

// Cryptobox++
namespace hyker { namespace cryptobox {
    class Credentials;
    class CryptoCache;
    class Certificate;
}}
#include "handshakebox.hpp"

// Outbox++
namespace hyker { namespace outbox {
    class Outbox;
}}

// Toolbox++
namespace hyker {
    class Values;
}

// std
#include <string>
#include <vector>

namespace hyker {
    namespace cryptobox {
        class CertificateExchangeHandshakebox : public Handshakebox {
        public:
            CertificateExchangeHandshakebox(Credentials&    credentials,
                                            CryptoCache&    cache,
                                            outbox::Outbox& outbox);

            Values generateHS1(const std::string& to, int validity) override;

        protected:
            Values generateHS2(const Values& payload, const Values& options) override;
            Certificate getCertificate(const Values& payload, const Values& options) override;
        };
    };
};