#pragma once

// std
#include <string>

namespace hyker {
    class KeyPair {
    public:
        KeyPair() {}

        KeyPair(const std::string& public_key, const std::string& private_key);

        const std::string& getPublicKey() const;
        const std::string& getPrivateKey() const;

    private:
        std::string m_public_key;
        std::string m_private_key;
    };
}