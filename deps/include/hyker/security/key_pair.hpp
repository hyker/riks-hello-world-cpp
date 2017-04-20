#pragma once

// std
#include <string>

// Boost.Serialization
#include <boost/serialization/string.hpp>
namespace boost { namespace serialization { class access; } }

namespace hyker {
    namespace cryptobox {
        class KeyPair {
            friend class boost::serialization::access;

        public:
            KeyPair() {}
            KeyPair(const std::string& publicKey, const std::string& privateKey);
            const std::string& getPublicKey() const;
            const std::string& getPrivateKey() const;

        private:
            std::string m_publicKey;
            std::string m_privateKey;

            template<typename Archive>
            void serialize(Archive& ar, const unsigned version) {
                ar & m_publicKey;
                ar & m_privateKey;
            }
        };
    };
};