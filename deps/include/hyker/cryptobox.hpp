#pragma once

// Cryptobox++
#include "ephemeral_sym_key.hpp"

// Outbox++
#include "hyker/outbox/callback.hpp"
#include "hyker/outbox/filter.hpp"
#include "hyker/outbox/inbox.hpp"
#include "hyker/outbox.hpp"

// Core (Toolbox++)
#include "hyker/values.hpp"

// std
#include <functional>
#include <iostream>
#include <memory>
#include <string>

namespace hyker {
    namespace cryptobox {
        class Cryptobox {
        public:
            using CryptoFailureCallback = std::function<void(const hyker::Exception&)>;
            using HandshakeCallback = std::function<void(const EphemeralSymKey&)>;

            Cryptobox(const std::string& uid, const std::string& password, const std::string& property_store_path);
            ~Cryptobox();

            Cryptobox(Cryptobox&&);
            Cryptobox& operator=(Cryptobox&&);

            void load(std::istream& is, const std::string& password);
            void save(std::ostream& os, const std::string& password) const;

            void start();
            void start(const std::string& ticket, const outbox::Callback& save = outbox::Callback::NO_CALLBACK);
            void close();

            void startHistory();
            void startHistory(const std::string& ticket);
            void startHistory(const std::string& ticket, const outbox::Callback& save = outbox::Callback::NO_CALLBACK);
            void stopHistory();
            void fetchHistory();

            void resume();
            void resign();

            void setAPIKeys(const std::string& publicKey, const std::string& privateKey);
            void setOptions(const Values& options);

            std::string shakeHands(const std::string& uid, int validity);
            std::string shakeHands(const std::string& uid, int validity, const HandshakeCallback& callback);

            void attachInbox(const outbox::Inbox& inbox, const outbox::Filter& filter = outbox::Filter::NO_FILTER);
            void removeInbox(const outbox::Inbox& inbox, const outbox::Filter& filter = outbox::Filter::NO_FILTER);

            void put(const std::string& to, const Values& payload, const Values& options = Values(), const outbox::Inbox& inbox = outbox::Inbox::NO_INBOX, const CryptoFailureCallback& failure_callback = [](const std::exception& e){});
            void putUsingLongTermKeys(const std::string& to, const Values& payload, const Values& options = Values(), const outbox::Inbox& inbox = outbox::Inbox::NO_INBOX, const CryptoFailureCallback& failure_callback = [](const hyker::Exception& e){});

            std::string sign(const std::string& base64_data) const;
            bool verify(const std::string& base64_data, const std::string& base64_signature, const std::string& uid) const;

            const std::string& getUID() const;

        private:
            class Impl;
            std::unique_ptr<Impl> m_impl;
        };
    };
};