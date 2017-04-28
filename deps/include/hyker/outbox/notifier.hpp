#pragma once

// Outbox++
#include "filter.hpp"
#include "inbox.hpp"

// Core (Toolbox++)
#include "hyker/values.hpp"

// std
#include <utility>
#include <vector>

namespace hyker {
    namespace outbox {
        class Notifier {
        public:
            Notifier();

            void addInbox(const Inbox& inbox, const Filter& filter);
            void removeInbox(const Inbox& inbox, const Filter& filter);
            void notify(const Values& payload, const Values& options);

        private:
            std::vector<std::pair<Inbox, Filter>> m_inboxes;
        };
    }
}