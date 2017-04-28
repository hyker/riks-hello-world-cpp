#pragma once

// Outbox++
#include "callback.hpp"

// Core (Toolbox++)
#include "hyker/values.hpp"

// std
#include <functional>
#include <string>

namespace hyker {
    namespace outbox {
        class Hook {
        public:
            static const Hook NO_HOOK;

            Hook(const std::function<void(const Values&, const Values&, const Callback&)>& callback);

            void operator()(const Values& payload, const Values& options, const Callback& hookCallback);
            bool operator==(const Hook& other) const;
            bool operator!=(const Hook& other) const;

            int getID() const;

        private:
            std::function<void(const Values&, const Values&, const Callback&)> m_callback;
            int m_id;
        };
    }
}