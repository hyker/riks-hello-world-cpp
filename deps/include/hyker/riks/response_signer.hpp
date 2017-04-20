#pragma once

// RIKS++
#include "hyker/riks/response.hpp"
#include "hyker/riks/signed_response.hpp"

// std
#include <functional>
#include <string>

namespace hyker {
    namespace riks {
        class ResponseSigner {
        public:
            using SignFunction = std::function<std::string(const std::string& b64Data)>;

            ResponseSigner(const SignFunction& signFunction);

            SignedResponse sign(const Response& response);

        private:
            SignFunction m_signFunction;
        };
    }
}