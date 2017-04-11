#pragma once

// Toolbox++
#include "apptimate/json_array.hpp"

// std
#include <functional>
#include <string>

namespace apptimate {
    namespace outbox {
        class Inbox {
        public:
            static const Inbox NO_INBOX;

            /**
             * Creates a new inbox.
             *
             * @param callback The inbox function.
             */
            Inbox(const std::function<void(const Values&, const Values&)>& callback);

            /**
             * Calls the inbox function.
             *
             * @param payload The payload of the message.
             * @param options The options of the message.
             */
            void operator()(const Values& payload, const Values& options);

            /**
             * Checks if this inbox is identical to the other inbox.
             */
            bool operator==(const Inbox& other) const;

            /**
             * Checks if this inbox is not identical to the other inbox.
             */
            bool operator!=(const Inbox& other) const;

            /**
             * Returns the ID of the inbox.
             *
             * @return the ID
             */
            int getID() const;

        private:
            static int NEXT_ID;
            int id;
            std::function<void(const Values&, const Values&)> callback;
        };
    }
}