#pragma once

// Core (Toolbox++)
#include "hyker/exception.hpp"

// std
#include <string>

namespace hyker {
    namespace cryptobox {
        class EphemeralSymKey {
        public:
            class NoUsesLeftException : public Exception {
            public:
                NoUsesLeftException() : NoUsesLeftException("Ephemeral symkey has no uses left.") {}
                NoUsesLeftException(const std::string& what) : Exception(what) {}
            };

            EphemeralSymKey(const std::string& key, int valid_for, const std::string& key_id, const std::string& my_uid);

            std::string useKeyForEncryption();
            std::string useKeyForDecryption(const std::string& sender);
            int usesLeftForEncryption() const;
            int usesLeftForDecryption(const std::string& sender) const;
            std::string getKeyID() const;

        protected:
            int m_uses_left;
            std::string m_key;
            std::string m_key_id;
            std::string m_my_uid;

        private:
            EphemeralSymKey() {}
        };
    };
};