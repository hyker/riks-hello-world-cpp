#pragma once

// Outbox++
#include "io_listener.hpp"

// std
#include <functional>
#include <memory>
#include <system_error>

namespace hyker {
    namespace outbox {
        class IOWrapper {
        public:
            /**
             * Creates a new IOWrapper.
             *
             * @param listener The IOListener that will listen to this wrapper.
             */
            IOWrapper(IOListener& listener);
            ~IOWrapper();

            IOWrapper(IOWrapper&&) noexcept;
            IOWrapper& operator=(IOWrapper&&) noexcept;

            /**
             * Connects to a host.
             *
             * @param host The host.
             * @param port The port.
             */
            void connect(std::string host, int port);

            /**
             * Writes data to the host.
             *
             * @param bytes The data to write.
             * @param callback The callback function for error handling.
             */
            void write(std::string bytes, const std::function<void(std::error_code)>& callback);

            /**
             * Closes the connection and IO wrapper.
             */
            void close();

            /**
             * Posts a task to be performed as soon as a thread is available.
             *
             * @param function The function to be called when a thread is available.
             */
            void post(std::function<void()> function);

            /**
             * Posts a task to be performed as soon as a thread is available, after the given timeout.
             *
             * @param function The function to be called when a thread is available.
             * @param timeout  The timeout before performing the task.
             */
            void post(std::function<void()> function, long timeout);

        private:
            class Impl;
            std::unique_ptr<Impl> m_impl;
        };
    }
}