#pragma once

// RIKS++
#include "encrypted_riksmessage.hpp"
#include "hyker/riks/keys/nonce.hpp"
#include "hyker/values.hpp"

// std
#include <string>

namespace hyker {
    namespace riks {
        class SignedRiksMessage : public EncryptedRiksMessage {
        public:
            SignedRiksMessage(const std::string& b64Signature, const EncryptedRiksMessage& message);

            SignedRiksMessage(const std::string& b64Signature,
                              const Nonce&       nonce,
                              const std::string& keyID,
                              const std::string& uid,
                              const std::string& secretData,
                              const std::string& immutableData,
                              const std::string& mutableData);

            const std::string& getBase64Signature() const;
            Values getMessageStructure() const;
            static SignedRiksMessage fromMessageStructure(const Values& messageStructure);

        protected:
            std::string m_b64Signature;

        private:
            static bool verifyMessageStructure(const Values& messageStructure);
        };
    }
}