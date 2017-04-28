#pragma once

// std
#include <string>

namespace hyker {
    namespace riks {
        class Message {
        public:
            Message(const std::string& secret_data, const std::string& immutable_data, const std::string& mutable_data);

            const std::string& secretData() const;
            const std::string& immutableData() const;
            const std::string& mutableData() const;

        protected:
            std::string m_secret_data;
            std::string m_immutable_data;
            std::string m_mutable_data;
        };
    }
}