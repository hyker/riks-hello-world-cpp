#pragma once

namespace apptimate { class Values; }

#include <string>
#include <functional>

namespace apptimate {
    namespace outbox {
        class Callback {
        public:
            static const Callback NO_CALLBACK;

            /**
             * Creates a new callback.
             *
             * @param callback The callback function.
             */
            Callback(const std::function<void(const Values&)>& callback);

            /**
             * Calls the callback function.
             *
             * @param args The arguments to send to the callback function.
             */
            void operator()(const Values& args) const;

            /**
             * Checks if this callback is identical to the other callback.
             */
            bool operator==(const Callback& other) const;

            /**
             * Checks if this callback is not identical to the other callback.
             */
            bool operator!=(const Callback& other) const;

            /**
             * Returns the ID of the callback.
             *
             * @return the ID
             */
            int getID() const;

        private:
            static int NEXT_ID;
            int id;
            std::function<void(const Values&)> callback;
        };
    }
}