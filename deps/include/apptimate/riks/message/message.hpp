#pragma once

// Toolbox++
#include "apptimate/values.hpp"

// std
#include <string>

namespace apptimate {
    namespace riks {
        class Message {
        public:
            Message(const std::string& secretData,
                    const std::string& immutableData,
                    const std::string& mutableData);

            const std::string& getSecret() const;
            const std::string& getImmutable() const;
            const std::string& getMutable() const;

        protected:
            std::string m_secret;
            std::string m_immutable;
            std::string m_mutable;
        };
    }
}