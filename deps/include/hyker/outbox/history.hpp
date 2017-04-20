#pragma once

#include "hooks.hpp"

namespace hyker {
    namespace outbox {
        class History {
        public:
            /**
             * Creates a manager for message history tracking.
             *
             * hooks The hooks to use for tracking.
             */
            History(Hooks& hooks);

            /**
             * Sets up the tracker.
             */
            void setup();

            /**
             * Starts tracking a ticket.
             *
             * @param t    The ticket to be tracked.
             * @param save The callback function to be called.
             */
            void start(const std::string& t, const Callback& save);

            /**
             * Stops all tracking.
             */
            void stop();

        protected:
            bool isSetup = false;

            Hook store = Hook::NO_HOOK;
            Hook harvest = Hook::NO_HOOK;
            Hook append = Hook::NO_HOOK;

            Hooks& hooks;

            bool hasTicket = false;
            std::string ticket;

        };
    }
}