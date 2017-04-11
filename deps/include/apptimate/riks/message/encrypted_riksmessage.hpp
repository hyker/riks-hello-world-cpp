#pragma once

// RIKS++
#include "riksmessage.hpp"
#include "apptimate/riks/keys/nonce.hpp"

// std
#include <string>

namespace apptimate {
    namespace riks {
        class EncryptedRiksMessage : public RiksMessage {
        public:
            EncryptedRiksMessage(const Nonce& nonce,
                                 const std::string& keyID,
                                 const std::string& uid,
                                 const std::string& secretData,
                                 const std::string& immutableData,
                                 const std::string& mutableData);

            const Nonce& getNonce() const;
            const std::string& getKeyID() const;
            std::string getDataString() const;

        protected:
            Nonce m_nonce;
            std::string m_keyID;
        };
    }
}