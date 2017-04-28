#pragma once

// RIKS++
#include "hyker/riks/whitelist.hpp"
#include "hyker/riks/message.hpp"

// Core (Toolbox++)
#include "hyker/exception.hpp"

// std
#include <functional>
#include <iostream>
#include <memory>
#include <string>

namespace hyker {
    namespace riks {
        class RiksKit {
        public:
            static const std::string DEFAULT_CONFIGURATION;

            using EncryptionCallback = std::function<void(const std::string&)>;
            using DecryptionCallback = std::function<void(const Message&)>;
            using ExceptionCallback = std::function<void(const hyker::Exception&)>;

            using SignFunction = std::function<std::string(const std::string&)>;
            using VerifyFunction = std::function<bool(const std::string&, const std::string&, const std::string&)>;

            RiksKit(const std::string& uid, const std::string& password, const Whitelist& whitelist, const std::string& property_store = DEFAULT_CONFIGURATION);
            ~RiksKit();

            RiksKit(RiksKit&&) noexcept;
            RiksKit& operator=(RiksKit&&) noexcept;

            void load(std::istream& is, const std::string& password);
            void save(std::ostream& os, const std::string& password) const;

            std::string encryptMessage(const Message& message, const std::string& message_namespace);
            void encryptMessage(const Message& message, const std::string& message_namespace, const EncryptionCallback& callback, const ExceptionCallback& exception_callback = [](const hyker::Exception& e){});

            Message decryptMessage(const std::string& message);
            void decryptMessage(const std::string& message, const DecryptionCallback& callback, const ExceptionCallback& exception_callback = [](const hyker::Exception& e){});

            void preShareKey(const std::string& recipient_uid, const std::string& key_id);

            void queryForKey(const std::string& uid, const std::string& key_id, int timeout);

            void rekey(const std::string& message_namespace);

            void resetReplayProtector();
            void resetReplayProtector(const std::string& message_namespace);

            void close();

            const std::string& getUID() const;

        private:
            class Impl;
            std::unique_ptr<Impl> m_impl;
        };
    }
}