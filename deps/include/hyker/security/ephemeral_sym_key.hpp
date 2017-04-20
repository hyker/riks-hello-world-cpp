#pragma once

// Cryptobox++
#include "hyker/cryptobox/exception.hpp"

// std
#include <string>

// Boost.Serialization
#include <boost/serialization/string.hpp>
namespace boost { namespace serialization { class access; } }

namespace hyker {
    namespace cryptobox {
        class EphemeralSymKey {
            friend class boost::serialization::access;

        public:
            class NoUsesLeftException : public Exception {
            public:
                NoUsesLeftException() : NoUsesLeftException("Ephemeral symkey has no uses left.") {}
                NoUsesLeftException(const std::string& what) : Exception(what) {}
            };

            EphemeralSymKey(const std::string& key, int validFor, const std::string& keyID, const std::string& myUID);

            std::string useKeyForEncryption();
            std::string useKeyForDecryption(const std::string& sender);
            int usesLeftForEncryption() const;
            int usesLeftForDecryption(const std::string& sender) const;
            std::string getKeyID() const;

        protected:
            int m_usesLeft;
            std::string m_key;
            std::string m_keyID;
            std::string m_myUID;

        private:
            EphemeralSymKey() {}

            template<typename Archive>
            void serialize(Archive& ar, const unsigned version) {
                ar & m_usesLeft;
                ar & m_key;
                ar & m_keyID;
                ar & m_myUID;
            }
        };
    };
};