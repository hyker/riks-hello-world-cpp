#pragma once

// std
#include <functional>
#include <string>

namespace hyker {
    namespace riks {
        class RiksWhitelist {
        public:
            using AllowedForKey = std::function<bool(const std::string&, const std::string&, const std::string&)>;
            using NewKey = std::function<void(const std::string&)>;

            RiksWhitelist(const AllowedForKey&& allowedForKey,
                          const NewKey&&        newKey = [](const std::string& keyID){});

            bool allowedForKey(const std::string& uid,
                               const std::string& messageNamespace,
                               const std::string& keyID);
            void newKey(const std::string& keyID);

        private:
            AllowedForKey m_allowedForKey;
            NewKey m_newKey;
        };
    }
}