#pragma once

// Cryptobox++
namespace apptimate { namespace cryptobox {
    class Certificate;
    class Credentials;
    class CryptoCache;
}}

// Outbox++
#include "apptimate/outbox/filter.hpp"
#include "apptimate/outbox/inbox.hpp"
namespace apptimate { namespace outbox {
    class Outbox;
}}

// Toolbox++
namespace apptimate {
    class Values;
}

// std
#include <string>

namespace apptimate {
    namespace cryptobox {
        class Handshakebox {
        public:
            static const std::string ACTION;
            static const std::string HS1;
            static const std::string HS2;
            static const std::string VERSION;
            static const std::string KEY_ID;
            static const std::string LONG_TERM_KEY;
            static const std::string SEND_SIGNING_CERT;
            static const std::string EC_KEY;
            static const std::string KEY_VALIDITY;
            static const std::string SIGNATURE;
            static const std::string CERT_CHAIN;
            static const std::string VERSION_NUMBER;

            Handshakebox(Credentials& cryptoBoxCredentials, CryptoCache& cache, outbox::Outbox& outbox);

            const outbox::Inbox& inbox();
            const outbox::Filter& filter();
            virtual Values generateHS1(const std::string& to, int validity);

        protected:
            virtual Values generateHS2(const Values& payload, const Values& options);
            virtual Certificate getCertificate(const Values& payload, const Values& options);
            void handleHS1(const Values& payload, const Values& options);
            void handleHS2(const Values& payload, const Values& options);
            void negotiateAndStore(const std::string& otherPublicKey,
                                   const std::string& ourPrivateKey,
                                   const std::string& keyId,
                                   const std::string& correspondant,
                                   const int& validity);

            Credentials& credentials;
            CryptoCache& cache;
            outbox::Outbox& outbox;

        private:
            bool filter(const Values& payload, const Values& options);
            void call(const Values& payload, const Values& options);

            outbox::Inbox m_inbox;
            outbox::Filter m_filter;
        };
    };
};