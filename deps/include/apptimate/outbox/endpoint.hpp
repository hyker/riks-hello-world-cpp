#pragma once

#include "hooks.hpp"
#include "io_listener.hpp"
#include "io_wrapper.hpp"
#include "notifier.hpp"

#include "apptimate/json_array.hpp"

#include <iterator>
#include <iostream>
#include <mutex>
#include <queue>
#include <deque>

namespace apptimate {
    namespace outbox {
        class Endpoint : public IOListener {
        public:
            /**
             * Creates a new endpoint.
             *
             * @param notifier The notifier that will be called on events.
             * @param hooks    The event hooks.
             * @param host     The host to connect to.
             * @param port     The port to connect to.
             * @param pblc     The public key.
             * @param prvt     The private key.
             * @param user     The user ID.
             */
            Endpoint(Notifier&          notifier,
                     Hooks&             hooks,
                     const std::string& host,
                     const int&         port,
                     const std::string& pblc,
                     const std::string& prvt,
                     const std::string& user);

            /**
             * Called when the connection gets input.
             */
            void onInput(const char* begin, const char* end);

            /**
             * Called when the connection has been opened.
             */
            void onConnect();

            /**
             * Called when the connection is dropped.
             */
            void onDrop();

            void start();
            void stop();

            /**
             * Writes to the endpoint.
             */
            void write();

            /**
             * Cancels the operations.
             */
            void cancel();

            void give();
            bool take();

            int claim();
            bool owner(const int& id);

            void put(const std::string& bytes);

            void onset();
            void reset();

            void open();
            void close();

            /**
             * Adds a message to be sent.
             *
             * @param map The message.
             */
            virtual void add(const Values& map) = 0;

        protected:
            std::deque<Values> getClearCache();

            void loop();
            void loop(int id, int it);

            /**
             * Returns the packet length of the given data.
             *
             * @param bytes The data.
             *
             * @return The length.
             */
            virtual int getLength(const std::string& bytes) = 0;

            /**
             * Strips the meta information from the given data.
             *
             * @param bytes The data to strip the meta information from.
             *
             * @return The stripped data.
             */
            virtual std::string decapitate(const std::string& bytes) = 0;

            /**
             * Returns the packet from the given data.
             *
             * @param bytes The data to retrieve the packet from.
             *
             * @return The packet.
             */
            virtual std::string getPacket(const std::string& bytes) = 0;

            /**
             * Returns the buffer from the given data.
             *
             * @param bytes The data to retrieve the buffer from.
             *
             * @return The buffer.
             */
            virtual std::string getBuffer(const std::string& bytes) = 0;

            Notifier& notifier;
            Hooks& hooks;

            const std::string host;
            const int port;
            const std::string pblc;
            const std::string prvt;
            const std::string user;

            std::deque<Values> cache;
            std::deque<std::string> queue;
            std::string buffer;
            int length = -1;

            std::shared_ptr<IOWrapper> iowrapper;

            int looperCount = -1;
            bool writerFlag = false;
            bool connected = false;
        };
    }
}