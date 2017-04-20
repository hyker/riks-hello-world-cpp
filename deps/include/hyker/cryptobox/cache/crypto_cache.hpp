#pragma once

#include "ephemeral_key_pair.hpp"
#include "hyker/cryptobox/exception.hpp"
#include "hyker/security/certificate.hpp"
#include "hyker/security/ephemeral_sym_key.hpp"

// Toolbox++
#include "hyker/concurrent_map.hpp"
#include "hyker/cache_map.hpp"
#include "hyker/wrapper.hpp"

// std
#include <memory>
#include <string>
#include <utility>

// Boost.Serialization
#include <boost/serialization/map.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/shared_ptr.hpp>
namespace boost { namespace serialization { class access; } }

namespace hyker {
    namespace cryptobox {
        class CryptoCache {
            friend class boost::serialization::access;

        public:
            class EphemeralSymKeyExpiredException : public Exception {
            public:
                EphemeralSymKeyExpiredException() : EphemeralSymKeyExpiredException("Ephemeral symkey has expired.") {}
                EphemeralSymKeyExpiredException(const std::string& what) : Exception(what) {}
            };

            CryptoCache();
            CryptoCache(long ttl);

            void addEphemeralKeyPair(const std::string& keyId, EphemeralKeyPair keyPair);
            bool hasEphemeralKeyPair(const std::string& keyId);
            EphemeralKeyPair& getEphemeralKeyPair(const std::string& keyId);

            void putEphemeralSymKey(const std::string& uid, EphemeralSymKey ephemeralSymKey);
            bool hasEphemeralSymKey(const std::string& uid);
            bool hasEphemeralSymKey(const std::string& uid, const std::string& keyID);
            EphemeralSymKey& getEphemeralSymKeyForEncryption(const std::string& uid);
            EphemeralSymKey& getEphemeralSymKeyForDecryption(const std::string& uid, const std::string& keyId);
            EphemeralSymKey& waitForEphemeralSymKeyForDecryption(const std::string& uid, const std::string& keyId);
            EphemeralSymKey& waitForEphemeralSymKeyForEncryption(const std::string& uid, const std::string& keyId);
            EphemeralSymKey& waitForEphemeralSymKeyForEncryption(const std::string& uid);

            void putCertificate(const std::string& uid, const Certificate& certificate);
            virtual bool hasCertificate(const std::string& uid);
            virtual Certificate getCertificate(const std::string& uid);
            Certificate waitForCertificate(const std::string& uid);

            void putPublicLongtermEncryptionKey(const std::string& uid, const std::string& publicKey);
            virtual bool hasPublicLongtermEncryptionKey(const std::string& uid);
            virtual std::string getPublicLongtermEncryptionKey(const std::string& uid);
            std::string waitForPublicLongtermEncryptionKey(const std::string& uid);

        private:
            EphemeralSymKey& waitForEphemeralSymKeyForEncryption_noblock(const std::string &uid);

            using PublicKeyCache = CacheMap<std::string, Wrapper<std::string>>;
            using CertificateCache = CacheMap<std::string, Certificate>;
            using EphemeralKeyPairCache = CacheMap<std::string, EphemeralKeyPair>;
            using SymKeySetCache = CacheMap<std::string, EphemeralSymKey>;
            using SymKeySetCacheMap = std::map<std::string, std::shared_ptr<SymKeySetCache>>;

            PublicKeyCache m_publicKeys;
            CertificateCache m_certificates;
            EphemeralKeyPairCache m_ephemeralKeyPairs;
            SymKeySetCacheMap m_symKeySets;

            long m_ttl;
            std::mutex m_symKeySets_mutex;

            template<typename Archive>
            void serialize(Archive& ar, const unsigned version) {
                ar & m_publicKeys;
                ar & m_certificates;
                ar & m_ephemeralKeyPairs;
                ar & m_symKeySets;
            }
        };
    };
};