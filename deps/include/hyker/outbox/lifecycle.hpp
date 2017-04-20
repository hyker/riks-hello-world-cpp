#pragma once

// Outbox++
#include "outbox.hpp"

namespace hyker {
    namespace outbox {
        class Outbox;
        class Lifecycle {
        public:
            /**
             * Creates a new lifecycle.
             *
             * @param outbox The outbox.
             */
            Lifecycle(const Outbox& outbox);

            /**
             * Starts the lifecycle.
             */
            void start();

            /**
             * Stops the lifecycle.
             */
            void stop();
        };
    }
}