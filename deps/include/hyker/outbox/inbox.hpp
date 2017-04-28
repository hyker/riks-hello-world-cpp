#pragma once

// Core (Toolbox++)
#include "hyker/values.hpp"

// std
#include <functional>
#include <string>

namespace hyker {
    namespace outbox {
        class Inbox {
        public:
            static const Inbox NO_INBOX;

            Inbox(std::function<void(const Values&, const Values&)>&& callback);

            void operator()(const Values& payload, const Values& options);
            bool operator==(const Inbox& other) const;
            bool operator!=(const Inbox& other) const;

            int getID() const;

        private:
            std::function<void(const Values&, const Values&)> m_callback;
            int m_id;
        };
    }
}