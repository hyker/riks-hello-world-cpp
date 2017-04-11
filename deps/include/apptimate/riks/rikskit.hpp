#pragma once

// RIKS++
#include "configuration.hpp"
#include "key_sharer.hpp"
#include "riks_whitelist.hpp"
#include "replay_protector.hpp"
#include "message/message.hpp"
#include "keys/symkey_cache.hpp"

// Cryptobox++
#include "apptimate/cryptobox/cryptobox.hpp"

// Toolbox++
#include "apptimate/json.hpp"
#include "apptimate/values.hpp"
#include "apptimate/property_store.hpp"

// std
#include <functional>
#include <string>

// Boost.Serialization
#include <boost/serialization/shared_ptr.hpp>

namespace apptimate {
    namespace riks {
        class RiksKit {
        public:
            using EncryptionCallback = std::function<void(const std::string&)>;
            using DecryptionCallback = std::function<void(const Message&)>;
            using ExceptionCallback = std::function<void(apptimate::Exception&)>;

            using SignFunction = std::function<std::string(const std::string&)>;
            using VerifyFunction = std::function<bool(const std::string&, const std::string&, const std::string&)>;

            RiksKit(const std::string&     uid,
                    const std::string&     password,
                    const RiksWhitelist&   whitelist,
                    const std::string&     propertyStorePath);
            RiksKit(const std::string&     uid,
                    const std::string&     password,
                    const RiksWhitelist&   whitelist,
                    const PropertyStore&   propertyStore = loadDefaultConfiguration());
            RiksKit(cryptobox::Cryptobox&& cryptobox,
                    const RiksWhitelist&   whitelist,
                    const std::string&     propertyStorePath);
            RiksKit(cryptobox::Cryptobox&& cryptobox,
                    const RiksWhitelist&   whitelist,
                    const PropertyStore&   propertyStore = loadDefaultConfiguration());

            ~RiksKit() = default;
            RiksKit(const RiksKit& other) = delete;
            RiksKit(RiksKit&& other);
            RiksKit& operator=(const RiksKit& other) = delete;
            RiksKit& operator=(RiksKit&& other) = delete;

            static PropertyStore loadDefaultConfiguration();

            static RiksKit load(const std::string& path, const std::string& password, const RiksWhitelist& whitelist);
            void save(const std::string& path, const std::string& password);

            std::string encryptMessage(const Message& message, const std::string& messageNamespace);
            void encryptMessage(const Message&            message,
                                const std::string&        messageNamespace,
                                const EncryptionCallback& callback,
                                const ExceptionCallback&  exceptionCallback = [](apptimate::Exception& e){});

            Message decryptMessage(const std::string& message);
            void decryptMessage(const std::string&        message,
                                const DecryptionCallback& callback,
                                const ExceptionCallback&  exceptionCallback = [](apptimate::Exception& e){});

            void preShareKey(const std::string& recipientUID, const std::string& keyID);

            void queryForKey(const std::string& uid,
                             const std::string& keyID,
                             int                timeout);

            void rekey(const std::string& messageNamespace);

            void resetReplayProtector();
            void resetReplayProtector(const std::string& messageNamespace);

            std::string getUID();

            void close();

        private:
            SignFunction                     initSignFunction();
            VerifyFunction                   initVerifyFunction();

            cryptobox::Cryptobox             m_cryptobox;
            PropertyStore                    m_propertyStore;
            RiksWhitelist                    m_whitelist;
            std::unique_ptr<SymKeyCache>     m_cache;
            std::unique_ptr<ReplayProtector> m_replayProtector;
            KeySharer                        m_keySharer;
        };
    }
}