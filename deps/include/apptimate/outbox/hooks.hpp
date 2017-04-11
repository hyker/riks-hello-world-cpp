#pragma once

// Outbox++
#include "callback.hpp"
#include "filter.hpp"
#include "hook.hpp"

// Toolbox++
#include "apptimate/json_array.hpp"

// std
#include <exception>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace apptimate {
    namespace outbox {
        class Hooks {
        public:
            /**
             * Registers a hook to be performed after a message has been put to the outbox.
             *
             * @param filter The filter to be used.
             * @param hook   The hook to be triggered.
             */
            void afterPut(const Filter& filter, const Hook& hook);

            /**
             * Registers a hook to be performed before sending messages.
             *
             * @param filter The filter to be used.
             * @param hook   The hook to be triggered.
             */
            void beforeSend(const Filter& filter, const Hook& hook);

            /**
             * Registers a hook to be performed after receiving messages.
             *
             * @param filter The filter to be used.
             * @param hook   The hook to be triggered.
             */
            void afterReceive(const Filter& filter, const Hook& hook);

            /**
             * Registers a hook to be performed before notifying inboxes.
             *
             * @param filter The filter to be used.
             * @param hook   The hook to be triggered.
             */
            void beforeNotify(const Filter& filter, const Hook& hook);

            /**
             * Performs a hook.
             *
             * @param key      The key of the hook.
             * @param payload  The message payload.
             * @param options  The message options.
             * @param callback The callback function.
             */
            void performHook(const std::string& key,
                             const Values&     payload,
                             const Values&     options,
                             const Callback&    callback);

            /**
             * Registers a hook.
             *
             * @param filter The filter to be used.
             * @param hook   The hook to be triggered.
             * @param key    The key of the hook.
             */
            void registerHook(const Filter&      filter,
                              const Hook&        hook,
                              const std::string& key);

            /**
             * Unregisters a hook.
             *
             * @param filter The filter to be used.
             * @param hook   The hook to be triggered.
             * @param key    The key of the hook.
             */
            void unregisterHook(const Filter&      filter,
                                const Hook&        hook,
                                const std::string& key);

        protected:
            /**
             * Holder class for pairing Hook and Filter
             */
            class HookAndFilter {
            public:
                /**
                 *
                 *
                 * @param filter
                 * @param hook
                 */
                HookAndFilter(const Filter& filter,
                              const Hook&   hook)
                        : filter(filter),
                          hook(hook) {
                }

                Filter filter;
                Hook hook;

            };

            /**
             * Hookback
             */
            class Hookback : public Callback {
            public:
                /**
                 *
                 *
                 * @param hook
                 * @param callback
                 */
                Hookback(const Hook&     hook,
                         const Callback& callback)
                        : Callback ([](const Values& args) {}),
                          hook     (hook),
                          callback (callback) {
                }

                Hook hook;
                Callback callback;
            };

            /** The hooks **/
            std::map<std::string, std::vector<HookAndFilter>> hooks;

        };
    }
}