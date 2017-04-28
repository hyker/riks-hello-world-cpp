#pragma once

// Outbox++
#include "callback.hpp"
#include "filter.hpp"
#include "hook.hpp"

// Core (Toolbox++)
#include "hyker/values.hpp"

// std
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace hyker {
    namespace outbox {
        class Hooks {
        public:
            void afterPut(const Filter& filter, const Hook& hook);
            void beforeSend(const Filter& filter, const Hook& hook);
            void afterReceive(const Filter& filter, const Hook& hook);
            void beforeNotify(const Filter& filter, const Hook& hook);

            void performHook(const std::string& key, const Values& payload, const Values& options, const Callback& callback);
            void registerHook(const Filter& filter, const Hook& hook, const std::string& key);
            void unregisterHook(const Filter& filter, const Hook& hook, const std::string& key);

        protected:
            std::map<std::string, std::vector<std::pair<Filter, Hook>>> m_hooks;
        };
    }
}