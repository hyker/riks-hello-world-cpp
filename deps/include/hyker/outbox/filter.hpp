#pragma once

// Core (Toolbox++)
#include "hyker/values.hpp"

// std
#include <functional>
#include <string>

namespace hyker {
    namespace outbox {
        class Filter {
        public:
            static const Filter NO_FILTER;

            Filter(std::function<bool(const Values&, const Values&)>&& callback);

            bool operator()(const Values& payload, const Values& options) const;
            bool operator==(const Filter& other) const;
            bool operator!=(const Filter& other) const;

            int getID() const;

        private:
            std::function<bool(const Values&, const Values&)> m_callback;
            int m_id;
        };
    }
}