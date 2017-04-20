#pragma once

// RIKS++
#include "hyker/riks/response.hpp"
#include "hyker/riks/signed_response.hpp"

// std
#include <functional>
#include <string>

namespace hyker {
    namespace riks {
        class ResponseVerifier {
        public:
            using VerifyFunction = std::function<bool(const std::string& b64Data,
                                                      const std::string& b64Signature,
                                                      const std::string& uid)>;

            ResponseVerifier(const VerifyFunction& verifyFunction);

            bool verify(const SignedResponse& response);

        private:
            VerifyFunction m_verifyFunction;
        };
    }
}