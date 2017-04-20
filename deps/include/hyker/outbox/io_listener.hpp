#pragma once

// std
#include <vector>

namespace hyker {
    namespace outbox {
        class IOListener {
        public:
            /**
             * Called when the connection has been opened.
             */
            virtual void onConnect() = 0;

            /**
             * Called when the connection gets input.
             */
            virtual void onInput(const char* begin, const char* end) = 0;

            /**
             * Called when the connection is dropped.
             */
            virtual void onDrop() = 0;
        };
    }
}