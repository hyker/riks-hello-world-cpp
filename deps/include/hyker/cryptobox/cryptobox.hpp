#pragma once

// Cryptobox++
#include "exception.hpp"
#include "credentials.hpp"
#include "decryptbox.hpp"
#include "cache/crypto_cache.hpp"
#include "handshakebox.hpp"
namespace hyker { namespace cryptobox {
    class EphemeralSymKey;
}}

// Outbox++
#include "hyker/outbox/callback.hpp"
#include "hyker/outbox/filter.hpp"
#include "hyker/outbox/inbox.hpp"
#include "hyker/outbox/outbox.hpp"

// Toolbox++
#include "hyker/property_store.hpp"
namespace hyker {
    class Values;
}

// std
#include <functional>
#include <memory>
#include <string>

// Boost.Serialization
namespace boost { namespace archive { class text_iarchive; class text_oarchive; }}

namespace hyker {
    namespace cryptobox {
        class Cryptobox {
        public:
            using CryptoFailureCallback = std::function<void(const hyker::Exception&)>;
            using HandshakeCallback = std::function<void(const EphemeralSymKey&)>;

            Cryptobox(const std::string& uid,
                      const std::string& password,
                      const std::string& propertyStorePath);
            Cryptobox(const std::string& uid,
                      const std::string& password,
                      const PropertyStore& propertyStore = loadDefaultConfiguration());
            Cryptobox(const Credentials& credentials, const PropertyStore& propertyStore);

            ~Cryptobox() = default;
            Cryptobox(const Cryptobox& other) = delete;
            Cryptobox(Cryptobox&& other);
            Cryptobox& operator=(const Cryptobox& other) = delete;
            Cryptobox& operator=(Cryptobox&& other);

            static PropertyStore loadDefaultConfiguration();

            static Cryptobox load(const std::string& path, const std::string& password);
            static Cryptobox load(boost::archive::text_iarchive& ia);
            void save(const std::string& path, const std::string& password);
            void save(boost::archive::text_oarchive& oa);

            void start();
            void start(const std::string& ticket, const outbox::Callback& save = outbox::Callback::NO_CALLBACK);
            void close();

            void startHistory();
            void startHistory(const std::string& ticket);
            void startHistory(const std::string& ticket,
                              const outbox::Callback& save = outbox::Callback::NO_CALLBACK);
            void stopHistory();
            void fetchHistory();

            void resume();
            void resign();

            void setAPIKeys(const std::string& publicKey, const std::string& privateKey);
            void setOptions(const Values& options);


            void attachInbox(const std::function<void(const Values&, const Values&)>& inbox);
            void attachInbox(const std::function<void(const Values&, const Values&)>& inbox,
                             const std::function<bool(const Values&, const Values&)>& filter);
            void attachInbox(const outbox::Inbox& inbox,
                             const outbox::Filter& filter = outbox::Filter::NO_FILTER);
            void detachInbox(const outbox::Inbox& inbox,
                             const outbox::Filter& filter = outbox::Filter::NO_FILTER);

            std::string shakeHands(const std::string& uid, const int& validity);
            std::string shakeHands(const std::string& uid, const int& validity, const HandshakeCallback& callback);

            void put(const std::string& to,
                     const Values& payload,
                     const Values& options = Values(),
                     const outbox::Inbox& inbox = outbox::Inbox::NO_INBOX,
                     const CryptoFailureCallback& cbFail = [](const std::exception& e){});

            void putUsingLongTermKeys(const std::string& to,
                                      const Values& payload,
                                      const Values& options = Values(),
                                      const outbox::Inbox& inbox = outbox::Inbox::NO_INBOX,
                                      const CryptoFailureCallback& cbFail = [](const hyker::Exception& e){});

            const std::string& getUID() const;
            CryptoCache& getCryptoCache();
            Handshakebox& getHandshakebox();

            std::string sign(const std::string& b64Data) const;
            bool verify(const std::string& b64Data, const std::string& b64Signature, const std::string& uid) const;

        private:
            EphemeralSymKey fetchEphemeralSymKeyForEncryption(const std::string& uid);

            Credentials                   initCredentials(const std::string& uid, const std::string& password, const PropertyStore& propertyStore);
            std::unique_ptr<CryptoCache>  initCache();
            std::unique_ptr<Handshakebox> initHandshakebox();
            std::unique_ptr<Decryptbox>   initDecryptbox();

            PropertyStore                     m_propertyStore;
            Credentials                       m_credentials;
            std::unique_ptr<outbox::Outbox>   m_outbox = std::unique_ptr<outbox::Outbox>(new outbox::Outbox());
            std::unique_ptr<outbox::Hooks>    m_hooks = std::unique_ptr<outbox::Hooks>(new outbox::Hooks());
            std::unique_ptr<outbox::Notifier> m_notifier = std::unique_ptr<outbox::Notifier>(new outbox::Notifier());
            std::unique_ptr<CryptoCache>      m_cache;
            std::unique_ptr<Handshakebox>     m_handshakebox;
            std::unique_ptr<Decryptbox>       m_decryptbox;
            std::string                       m_ticket = outbox::Outbox::HIST_TICKET_ALL;
        };
    };
};