#pragma once

// Cryptobox++
#include "hyker/security/key_pair.hpp"

// Boost.Serialization
namespace boost { namespace serialization { class access; } }

namespace hyker {
    namespace cryptobox {
        class EphemeralKeyPair {
            friend class boost::serialization::access;

        public:
            EphemeralKeyPair(const KeyPair& keyPair, int validFor);

            const KeyPair& getKeyPair();
            int validFor();

        private:
            KeyPair m_keyPair;
            int m_validFor;

            EphemeralKeyPair() {}

            template<typename Archive>
            void serialize(Archive& ar, const unsigned version) {
                ar & m_keyPair;
                ar & m_validFor;
            }
        };
    };
};