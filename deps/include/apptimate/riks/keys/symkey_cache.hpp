#pragma once

// RIKS++
#include "symkey.hpp"

// Toolbox++
#include "apptimate/cache_map.hpp"
#include "apptimate/wrapper.hpp"

// std
#include <memory>
#include <string>

// Boost.Serialization
#include <boost/serialization/string.hpp>
namespace boost { namespace serialization { class access; } }

namespace apptimate {
    namespace riks {
        using SymKeyCacheCallback = std::function<void(const SymKey&)>;

        class SymKeyCache {
        public:
            SymKeyCache();

            void rekey(const std::string& messageNamespace);
            const std::string& getNamespace(const std::string& b64KeyID);
            const std::string& getCurrentKeyID(const std::string& messageNamespace);

            SymKey& getCurrentLocalSymKey(const std::string& messageNamespace);

            CacheMap<std::string, SymKey>& getLocalSymKeys();
            CacheMap<std::string, SymKey>& getExternalSymKeys();

        private:
            void rekey_unlocked(const std::string& messageNamespace);
            const std::string& getCurrentKeyID_unlocked(const std::string& messageNamespace);

            CacheMap<std::string, SymKey>      m_externalKeys;
            CacheMap<std::string, SymKey>      m_localKeys;
            CacheMap<std::string, Wrapper<std::string>> m_currentKeyIDs;
            CacheMap<std::string, Wrapper<std::string>> m_namespaces;

            std::mutex m_mutex;

            friend class boost::serialization::access;
            template<typename Archive>
            void serialize(Archive& ar, const unsigned version) {
                ar & m_externalKeys;
                ar & m_localKeys;
                ar & m_currentKeyIDs;
                ar & m_namespaces;
            }
        };
    }
}