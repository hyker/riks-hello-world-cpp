#pragma once

// Outbox++
#include "filter.hpp"
#include "hooks.hpp"
#include "inbox.hpp"

// Toolbox++
#include "hyker/log.hpp"
#include "hyker/json_array.hpp"

// std
#include <memory>
#include <vector>

namespace hyker {
    namespace outbox {
        class Notifier {
        public:
            /**
             * Creates a new Notifier.
             *
             * @param hooks The hooks on which to perform the notifications.
             */
            Notifier();

            /**
             * Adds an inbox to the Notifier.
             *
             * @param inbox The inbox to be added.
             * @param filter The filter to be coupled with the inbox.
             */
            void addInbox(const Inbox& inbox, const Filter& filter);

            /**
             * Removes an inbox from the Notifier.
             *
             * @param inbox The inbox to be removed.
             * @param filter The filter that was coupled with the inbox, to reduce the impact of the removal.
             */
            void removeInbox(const Inbox& inbox, const Filter& filter);

            /**
             * Removes an inbox from the Notifier.
             *
             * @param id The identifier of the inbox to be removed.
             */
            void removeInbox(const int& id);

            /**
             * Notifies the inboxes.
             *
             * @param payload The message payload.
             * @param payload The message options.
             */
            void notify(const Values& payload, const Values& options);

        private:
            /**
             * Pairs an inbox with a filter.
             */
            class Holder {
            public:
                Holder(const Inbox&  inbox,
                       const Filter& filter)
                        : inbox(inbox),
                          filter(filter) {
                }

                Inbox inbox;
                Filter filter;
            };

            std::vector<Holder> inboxes;
        };
    }
}