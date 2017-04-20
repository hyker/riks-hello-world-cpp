#pragma once

// std
#include <string>

namespace hyker {
    namespace riks {
        class Response {
        public:
            Response(const std::string& keyID,
                     const std::string& sender,
                     const std::string& b64Key);

            const std::string& getKeyID() const;
            const std::string& getSender() const;
            const std::string& getBase64Key() const;
            std::string getDataString() const;

        protected:
            std::string m_keyID;
            std::string m_sender;
            std::string m_b64Key;
        };
    }
}