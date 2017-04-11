#pragma once

// Outbox++
namespace apptimate { namespace outbox { class Notifier; } }
namespace apptimate { namespace outbox { class Hooks; } }
#include "endpoint.hpp"

// std
#include <string>
#include <vector>

namespace apptimate {
    namespace outbox {
        class Connection : public Endpoint {
        public:
            /**
             * Creates a new connection.
             *
             * @param notifier The notifier that will be called on events.
             * @param hooks    The event hooks.
             * @param host     The host to connect to.
             * @param port     The port to connect to.
             * @param pblc     The public key.
             * @param prvt     The private key.
             * @param user     The user ID.
             */
            Connection(Notifier&          notifier,
                       Hooks&             hooks,
                       const std::string& host,
                       const int&         port,
                       const std::string& pblc,
                       const std::string& prvt,
                       const std::string& user);

            /**
             * Called when the connection gets input.
             */
            void onInput(const char* begin, const char* end) override;

            /**
             * Called when the connection has been opened.
             */
            void onConnect() override;

            /**
             * Called when the connection is dropped.
             */
            void onDrop() override;

            /**
             * Sends a fetch action to the connection.
             */
            void fetch();

            /**
             * Adds a message to be sent.
             *
             * @param map The message.
             */
            void add(const Values& map) override;

            /**
             * Adds a message to be sent.
             *
             * @param payload The payload.
             * @param options The options.
             */
            void add(const Values& payload, const Values& options);

            /**
             * Returns the packet length of the given data.
             *
             * @param bytes The data.
             *
             * @return The length.
             */
            int getLength(const std::string& bytes) override;

            /**
             * Strips the meta information from the given data.
             *
             * @param bytes The data to strip the meta information from.
             *
             * @return The stripped data.
             */
            std::string decapitate(const std::string& bytes) override;

            /**
             * Returns the packet from the given data.
             *
             * @param bytes The data to retrieve the packet from.
             *
             * @return The packet.
             */
            std::string getPacket(const std::string& bytes) override;

            /**
             * Returns the buffer from the given data.
             *
             * @param bytes The data to retrieve the buffer from.
             *
             * @return The buffer.
             */
            std::string getBuffer(const std::string& bytes) override;

        private:
            const std::string KEY_ACTION = "action";
            const std::string ACT_BIND   = "bind";
            const std::string ACT_FETCH  = "fetch";

        protected:
            void insertBindCommandInWriteQueue();
            void share();

            Values BIND = Values::init(KEY_ACTION, ACT_BIND);
            Values FETCH = Values::init(KEY_ACTION, ACT_FETCH);

            std::string BIND_MSG;

            /** Is this connection online? **/
            bool online = false;
        };
    }
}