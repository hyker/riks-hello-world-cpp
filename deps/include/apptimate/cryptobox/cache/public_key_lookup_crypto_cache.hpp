#pragma once

// Cryptobox++
#include "crypto_cache.hpp"
#include "apptimate/security/publickeylookup/public_key_lookup.hpp"
namespace apptimate { namespace cryptobox {
    class Certificate;
}}

// std
#include <string>

// Boost.Serialization
#include <boost/serialization/base_object.hpp>
namespace boost { namespace serialization { class access; } }

namespace apptimate {
    namespace cryptobox {
        class PublicKeyLookupCryptoCache : public CryptoCache {
            friend class boost::serialization::access;

        public:
            PublicKeyLookupCryptoCache(long ttl, PublicKeyLookup publicKeyLookup);

            bool hasCertificate(const std::string& uid) override;
            bool hasPublicLongtermEncryptionKey(const std::string& uid) override;

            Certificate getCertificate(const std::string& uid) override;
            std::string getPublicLongtermEncryptionKey(const std::string& uid) override;

        private:
            PublicKeyLookupCryptoCache() {}

            void getKeyAndCertFromPublicKeyLookup(const std::string& owner);

            PublicKeyLookup m_publicKeyLookup;

            template<typename Archive>
            void serialize(Archive& ar, const unsigned version) {
                ar & boost::serialization::base_object<CryptoCache>(*this);
                ar & m_publicKeyLookup;
            }
        };
    };
};