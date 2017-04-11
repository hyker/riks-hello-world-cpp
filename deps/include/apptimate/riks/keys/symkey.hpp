#pragma once

// RIKS++
#include "nonce.hpp"

// std
#include <string>

// Boost.Serialization
#include <boost/serialization/string.hpp>
namespace boost { namespace serialization { class access; } }

namespace apptimate {
    namespace riks {
        class SymKey {
        public:
            SymKey();
            SymKey(const std::string& b64KeyID,
                   const std::string& b64Key);

            const std::string& getKeyID() const;
            const std::string& getKeyBytes() const;
            std::string getKeyBase64() const;
            Nonce& getNonce() const;

        private:
            std::string m_keyID;
            std::string m_key;
            std::shared_ptr<Nonce> m_nonce;
            bool m_decryption;

            friend class boost::serialization::access;
            template<typename Archive>
            void serialize(Archive& ar, const unsigned version) {
                ar & m_keyID;
                ar & m_key;
                ar & *m_nonce;
                ar & m_decryption;
            }
        };
    }
}