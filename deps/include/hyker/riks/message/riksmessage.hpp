#pragma once

// RIKS
#include "hyker/riks/message/message.hpp"

// std
#include <string>

namespace hyker {
    namespace riks {
        class RiksMessage : public Message {
        public:
            RiksMessage(const std::string& uid,
                        const Message& message);

            RiksMessage(const std::string& uid,
                        const std::string& secretData,
                        const std::string& immutableData,
                        const std::string& mutableData);

            const std::string& getUID() const;

        protected:
            std::string m_uid;
        };
    }
}