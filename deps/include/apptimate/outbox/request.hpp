#pragma once

// Outbox++
#include "endpoint.hpp"
#include "hooks.hpp"
#include "notifier.hpp"

// std
#include <string>

namespace apptimate {
    namespace outbox {
        class Request : public Endpoint {
        public:
            /**
             * Creates a new request endpoint.
             *
             * @param notifier The notifier that will be called on events.
             * @param hooks    The event hooks.
             * @param host     The host to connect to.
             * @param port     The port to connect to.
             * @param pblc     The public key.
             * @param prvt     The private key.
             * @param user     The user ID.
             */
            Request(      Notifier    & notifier,
                          Hooks       & hooks,
                          const std::string & host,
                          const int         & port,
                          const std::string & pblc,
                          const std::string & prvt,
                          const std::string & user);

            void onInput(const char * begin, const char * end) override;
            void onConnect() override;
            /**
             * Adds a message to be sent.
             *
             * @param map The message.
             */
            void add(const Values & map) override;

            /**
             * Returns the packet length of the given data.
             *
             * @param bytes The data.
             *
             * @return The length.
             */
            int getLength(const std::string & bytes) override;

            /**
             * Strips the meta information from the given data.
             *
             * @param bytes The data to strip the meta information from.
             *
             * @return The stripped data.
             */
            std::string decapitate(const std::string & bytes) override;

            /**
             * Returns the packet from the given data.
             *
             * @param bytes The data to retrieve the packet from.
             *
             * @return The packet.
             */
            std::string getPacket(const std::string & bytes) override;

            /**
             * Returns the buffer from the given data.
             *
             * @param bytes The data to retrieve the buffer from.
             *
             * @return The buffer.
             */
            std::string getBuffer(const std::string & bytes) override;

        protected:
            bool chunked = false;
        };
    }
}