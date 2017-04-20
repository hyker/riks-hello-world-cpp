#pragma once

#include "hyker/values.hpp"

#include <functional>
#include <string>

namespace hyker {
    namespace outbox {
        class Filter {
        public:
            static const Filter NO_FILTER;

            /**
             * Creates a new filter.
             *
             * @param callback The filter function.
             */
            Filter(const std::function<bool(const Values&, const Values&)>& callback);

            /**
             * Calls the filter function.
             *
             * @param payload The payload of the message.
             * @param options The options of the message.
             *
             * @return <b>true</b> if message should be let through.
             */
            bool operator()(const Values& payload, const Values& options) const;

            /**
             * Checks if this filter is identical to the other filter.
             */
            bool operator==(const Filter& other) const;

            /**
             * Checks if this filter is not identical to the other filter.
             */
            bool operator!=(const Filter& other) const;

            /**
             * Returns the ID of the filter.
             *
             * @return the ID
             */
            int getID() const;

        private:
            static int NEXT_ID;
            int id;
            std::function<bool(const Values&, const Values&)> callback;
        };
    }
}