#pragma once

// std
#include <functional>
#include <string>

namespace hyker {
    namespace riks {
        class Whitelist {
        public:
            using AllowedForKey = std::function<bool(const std::string&, const std::string&, const std::string&)>;
            using NewKey = std::function<void(const std::string&)>;

            Whitelist(AllowedForKey&& allowed_for_key, NewKey&& new_key = [](const std::string& key_id){});

            bool allowedForKey(const std::string& uid, const std::string& message_namespace, const std::string& key_id);
            void newKey(const std::string& key_id);

        private:
            AllowedForKey m_allowed_for_key;
            NewKey m_new_key;
        };
    }
}