#pragma once

// Cryptobox++
#include "hyker/cryptobox/exception.hpp"
#include "hyker/security/certificate.hpp"

// std
#include <string>
#include <vector>

// Boost.Serialization
#include <boost/serialization/string.hpp>
namespace boost { namespace serialization { class access; } }

namespace hyker {
    namespace cryptobox {
        class KeyStore {
            friend class boost::serialization::access;

        public:
            class Exception : public hyker::cryptobox::Exception {
            public:
                Exception(const std::string& what) : hyker::cryptobox::Exception(what) {}
            };

            /**
             * Creates an empty key store.
             */
            KeyStore();

            /**
             * Loads a key store from the given path and password.
             *
             * @param store         The path to the key store.
             * @param storePassword The password used to encrypt the key store
             */
            KeyStore(const std::string& store, const std::string& storePassword);

            /**
             * Gets a key corresponding to a given alias from the key store, decrypted using a given password.
             *
             * @param alias    The alias of the key.
             * @param password The password to use when decrypting the key.
             *
             * @return The key.
             */
            std::string getKey(const std::string& alias, const std::string& password) const;

            /**
             * Gets a certificate chain corresponding to a given alias.
             *
             * @param alias The alias of the certificate chain.
             *
             * @return The certificate chain.
             */
            std::vector<Certificate> getCertificateChain(const std::string& alias) const;

            /**
             * Sets a key and its certificate chain in the key store, with alias and password.
             *
             * @param alias            The alias of the key.
             * @param key              The key.
             * @param password         The password.
             * @param certificateChain The certificate chain corresponding to the key.
             */
            void setKeyEntry(const std::string&              alias,
                             const std::string&              key,
                             const std::string&              password,
                             const std::vector<Certificate>& certificateChain);

            /**
             * Sets a certificate with a given alias.
             *
             * @param alias The alias of the certificate
             * @param cert  The certificate.
             */
            void setCertificateEntry(const std::string& alias, const std::string& cert);

        private:
            std::string m_store;
            std::string m_storePassword;

            template<typename Archive>
            void serialize(Archive& ar, const unsigned version) {
                ar & m_store;
                ar & m_storePassword;
            }
        };
    };
};