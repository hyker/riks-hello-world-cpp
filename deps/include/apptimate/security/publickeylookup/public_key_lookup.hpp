#pragma once

// Cryptobox++
#include "public_key_lookup_response.hpp"
#include "apptimate/cryptobox/credentials.hpp"
#include "apptimate/cryptobox/configuration.hpp"
#include "apptimate/security/key_pair.hpp"
#include "apptimate/security/key_store.hpp"
namespace apptimate { namespace cryptobox {
    class PublicKeyLookupCryptoCache;
}}

// Toolbox++
#include "apptimate/values.hpp"

// std
#include <string>

// Boost.Serialization
#include <boost/serialization/string.hpp>

namespace boost { namespace serialization { class access; } }

namespace apptimate {
    namespace cryptobox {
        class PublicKeyLookup {
            friend class boost::serialization::access;

        public:
            class Exception : public apptimate::cryptobox::Exception {
            public:
                Exception() : Exception("apptimate::cryptobox::PublicKeyLookup::Exception") {}
                Exception(const std::string& what) : apptimate::cryptobox::Exception(what) {}
            };

            PublicKeyLookup() {}
            PublicKeyLookup(const PropertyStore& propertyStore);
            PublicKeyLookup(const std::string& url, const std::string& apiKey, const KeyStore& trustStore);

            Credentials registerUID(const std::string& uid, const std::string& password);
            Credentials registerUID(const std::string& uid, const std::string& password, const KeyPair& cryptoKeyPair);
            PublicKeyLookupResponse fetch(const std::string& uid);

        protected:
            static const std::string GET_UID_INFO_PATH;
            static const std::string ADD_TOKEN_PATH;
            static const std::string REGISTER_USER_PATH;
            static const std::string REVOKE_CERTIFICATE_PATH;
            static const std::string UID;
            static const std::string KD_CRT;
            static const std::string REGISTER_USER_CSR;
            static const std::string REGISTER_USER_CRT;
            static const std::string EC_KEY;
            static const std::string EC_KEY_SIGN;
            static const std::string API_KEY;
            static const std::string REVOCATION_PASS;
            static const std::string OK_RESPONSE;
            static const std::string ERROR_KEY;

        private:
            std::string m_url;
            std::string m_apiKey;
            KeyStore    m_trustStore;

            PublicKeyLookupResponse post(const std::string& path, const Values& hmapOut);

            template<typename Archive>
            void serialize(Archive& ar, const unsigned version) {
                ar & m_url;
                ar & m_apiKey;
                ar & m_trustStore;
            }
        };
    };
};