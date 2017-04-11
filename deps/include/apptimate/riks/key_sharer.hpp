#pragma once

// RIKS++
#include "keys/symkey_cache.hpp"
#include "riks_whitelist.hpp"
#include "signed_response.hpp"

// Cryptobox++
#include "apptimate/cryptobox/cryptobox.hpp"

// Toolbox++
#include "apptimate/property_store.hpp"
#include "apptimate/values.hpp"

// std
#include <string>

namespace apptimate {
    namespace riks {
        class KeySharer {
        public:
            class KeySharingException : public Exception {
            public:
                KeySharingException(const std::string& what) : Exception(what) {}
            };

            KeySharer(cryptobox::Cryptobox& cryptoBox,
                      SymKeyCache&          cache,
                      RiksWhitelist         whitelist,
                      const PropertyStore&  propertyStore);

            ~KeySharer() = default;
            KeySharer(const KeySharer& other) = delete;
            KeySharer(KeySharer&& other);
            KeySharer& operator=(const KeySharer& other) = delete;
            KeySharer& operator=(KeySharer&& other);

            void requestKey(const std::string& keyID, const std::string& ownerUID);
            bool filterMessage(const Values& payload, const Values& options);
            void onMessage(const Values& payload);
            void onRequest(const Values& payload);
            void verifyRequest(const std::string& keyID, const std::string& requesterUid);
            void handleRequest(const std::string& keyID, const std::string& requesterUID);
            void onResponse(const Values& payload);
            bool verifyResponse(const SignedResponse& response);
            void handleResponse(const SignedResponse& response);

        private:
            cryptobox::Cryptobox& m_cryptobox;
            SymKeyCache&          m_cache;
            RiksWhitelist         m_whitelist;
            bool                  m_keyRelayEnabled;
        };
    }
}