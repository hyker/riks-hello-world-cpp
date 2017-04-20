#pragma once

// Cryptobox++
namespace hyker { namespace cryptobox {
    class CryptoCache;
}}

// Outbox++
#include "hyker/outbox/inbox.hpp"
#include "hyker/outbox/filter.hpp"
namespace hyker { namespace outbox {
    class Notifier;
}}

// Toolbox++
namespace hyker {
    class Values;
}

// std
#include <string>

namespace hyker {
    namespace cryptobox {
        class Decryptbox {
        public:
            static const std::string &CIPHER_TEXT;
            static const std::string &PROTOCOL_VERSION;
            static const std::string &PROTOCOL_VERSION_NUMBER;

            Decryptbox(const std::string &privateKey, outbox::Notifier &notifier, CryptoCache &cache);
            ~Decryptbox() = default;

            const outbox::Inbox& inbox();
            const outbox::Filter& filter();

        private:
            bool filter(const Values &payload, const Values &options);
            void call(const Values &payload, const Values &options);
            void decryptUsingHS(const Values &payload, const Values &options);
            void decryptUsingLongTermKeys(const Values &payload, const Values &options);

            outbox::Inbox     m_inbox;
            outbox::Filter    m_filter;
            std::string       m_privateKey;
            outbox::Notifier& m_notifier;
            CryptoCache&      m_cache;
        };
    };
};