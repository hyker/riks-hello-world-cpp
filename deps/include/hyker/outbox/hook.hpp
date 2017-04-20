#pragma once

// Outbox++
#include "callback.hpp"

// Toolbox++
#include "hyker/json_array.hpp"

// std
#include <functional>
#include <string>

namespace hyker {
    namespace outbox {
        class Hook {
        public:
            static const Hook NO_HOOK;

            /**
             * Creates a new hook.
             *
             * @param callback The hook function.
             */
            Hook(const std::function<void(const Values&, const Values&, const Callback&)>& callback);

            /**
             * Calls the hook function.
             *
             * @param payload      The payload of the message.
             * @param options      The options of the message.
             * @param hookCallback The callback that should be called.
             */
            void operator()(const Values& payload, const Values& options, const Callback& hookCallback);

            /**
             * Checks if this hook is identical to the other hook.
             */
            bool operator==(const Hook& other) const;

            /**
             * Checks if this hook is not identical to the other hook.
             */
            bool operator!=(const Hook& other) const;

            /**
             * Returns the ID of the hook.
             *
             * @return the ID
             */
            int getID() const;

        private:
            static int NEXT_ID;
            int id;
            std::function<void(const Values&, const Values&, const Callback&)> callback;
        };
    }
}