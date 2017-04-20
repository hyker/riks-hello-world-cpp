#pragma once

// Cryptobox++
#include "hyker/cryptobox/exception.hpp"
#include "hyker/security/key_pair.hpp"
#include "hyker/security/key_store.hpp"
namespace hyker { namespace cryptobox {
    class Certificate;
    class Cryptobox;
}}

// Toolbox++
namespace hyker {
    class PropertyStore;
}

// std
#include <string>
#include <vector>

// Boost.Serialization
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
namespace boost { namespace serialization { class access; } }

namespace hyker {
    namespace cryptobox {
        class Credentials {
            friend class boost::serialization::access;

        public:
            Credentials() {}
            Credentials(const std::string              &uid,
                        const KeyPair                  &cryptoKeyPair,
                        const std::string              &privateSigningKey,
                        const std::vector<Certificate> &certificateChain,
                        const KeyStore                 &trustStore);

            static Credentials load(const std::string   &uid,
                                    const std::string   &password,
                                    const PropertyStore &propertyStore);

            void save(const std::string   &password,
                      const PropertyStore &propertyStore);

            static bool testCredentials(const std::string   &uid,
                                        const std::string   &password,
                                        const PropertyStore &propertyStore);

            const std::string& getUID() const;
            const std::string& getPrivateSigningKey() const;
            const KeyPair& getCryptoKeyPair() const;
            const std::string& getCryptoPublicKeySignature() const;
            const std::vector<Certificate>& getCertificateChain() const;
            const KeyStore& getTrustStore() const;

        private:
            std::string              m_uid;
            KeyPair                  m_cryptoKeyPair;
            std::string              m_privateSigningKey;
            std::string              m_cryptoPublicKeySignature;
            std::vector<Certificate> m_certificateChain;
            KeyStore                 m_trustStore;

            static KeyPair loadKeys(const std::string &uid, const std::string &password, const PropertyStore &propertyStore);
            static std::string getKeyPath(const std::string &uid, const PropertyStore &propertyStore);
            static std::string getKeyStorePath(const std::string &uid, const PropertyStore &propertyStore);

            template<typename Archive>
            void serialize(Archive& ar, const unsigned version) {
                ar & m_uid;
                ar & m_cryptoKeyPair;
                ar & m_privateSigningKey;
                ar & m_cryptoPublicKeySignature;
                ar & m_certificateChain;
                ar & m_trustStore;
            }
        };
    };
};