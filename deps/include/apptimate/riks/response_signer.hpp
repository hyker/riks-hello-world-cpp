#pragma once

// RIKS++
#include "apptimate/riks/response.hpp"
#include "apptimate/riks/signed_response.hpp"

// std
#include <functional>
#include <string>

namespace apptimate {
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