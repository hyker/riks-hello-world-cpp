#pragma once

// RIKS++
#include "response.hpp"

// Toolbox++
#include "hyker/values.hpp"

// std
#include <string>

namespace hyker {
    namespace riks {
        class SignedResponse : public Response {
        public:
            SignedResponse(const Response&    response,
                           const std::string& b64Signature);
            SignedResponse(const std::string& keyID,
                           const std::string& sender,
                           const std::string& b64Key,
                           const std::string& b64Signature);

            const std::string& getBase64Signature() const;
            Values getMessageStructure() const;
            static SignedResponse fromMessageStructure(const Values& messageStructure);

        protected:
            static bool verifyMessageStructure(const Values& messageStructure);

            std::string m_b64Signature;
        };
    }
}