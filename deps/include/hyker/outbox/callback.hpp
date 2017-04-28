#pragma once

// Core (Toolbox++)
#include "hyker/values.hpp"

// std
#include <string>
#include <functional>

namespace hyker {
    namespace outbox {
        class Callback {
        public:
            static const Callback NO_CALLBACK;

            Callback(std::function<void(const Values&)>&& callback);

            void operator()(const Values& args) const;
            bool operator==(const Callback& other) const;
            bool operator!=(const Callback& other) const;

            int getID() const;

        private:
            std::function<void(const Values&)> m_callback;
            int m_id;
        };
    }
}