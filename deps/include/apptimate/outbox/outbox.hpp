#pragma once

// Outbox++
#include "connection.hpp"
#include "endpoint.hpp"
#include "filter.hpp"
#include "history.hpp"
#include "hooks.hpp"
#include "inbox.hpp"
#include "lifecycle.hpp"
namespace apptimate { namespace outbox { class Lifecycle; } }
#include "notifier.hpp"
#include "request.hpp"

// Toolbox++
namespace apptimate { class Values; }

// std
#include <exception>
#include <string>
#include <vector>

/**
 * Outbox is a lean but smart messaging client for Apptimate Message Broker,
 * providing point-to-point messaging with point-to-multipoint capability.
 *
 * <h2>Overview</h2>
 *
 * Outbox is a lean but smart messaging client for Apptimate Message Broker,
 * providing point-to-point messaging with point-to-multipoint capability.
 * <p>
 * <strong>Introduction</strong>
 * <p>
 * Message data objects are put into the outbox for transmission to targets.
 * Inboxes are attached to receive messages. They can have filters to manage
 * what messages ends up where in the application logic.
 * <p>
 * <strong>Point-to-point</strong>
 * <p>
 * Apptimate messaging system is first and foremost designed for point-to-point
 * messaging. Each client is known to all others from an unique identification
 * string. Every client can target another using this identity. The target
 * identity must be provided when putting a message into the outbox.
 * <p>
 * <strong>Request-response</strong>
 * <p>
 * When putting messages into the outbox, one can choose to also provide a
 * dedicated inbox. If this is done, the target will be given a special outbox
 * when receiving the message. This special outbox will contain all information
 * needed to deliver all messages put into it straight back to the provided
 * inbox at the origin.
 * <p>
 * <strong>Publish-subscribe</strong>
 * <p>
 * Outbox listens for messages sent to a given identity. This identity can
 * subscribe to subjects, which in turn can be subscribed to other subjects.
 * Messages can target both identities and subjects . This enables a
 * publish-subscribe pattern, i.e. point-to-multipoint messaging. Both
 * identities and subjects are in fact technically the same thing (they are
 * called tags).
 * <p>
 * <strong>Tags</strong>
 * <p>
 * Outbox introduces a concept of tags, which are similar to uids but more
 * intuitive. They can be viewed as both addresses for messaging and subjects
 * for publishing and subscription. A tag is a human readable string of
 * arbitrary length prefixed with the hashtag character. A unique id is derived
 * by hashing the concatenation of the tag and the app id, then prefixed with
 * the tilde character.
 * <p>
 * <strong>History</strong>
 * <p>
 * Apptimate messaging system provides message history storage. This enables
 * devices to receive messages in an asynchronous manner, allowing them to drop
 * in and out as they please.
 * <p>
 * Setting a time-to-live option when putting a message will enable history for
 * it. A ticket is generated for each message and must be kept for bookkeeping.
 * It must be stored persistently between application lifecycles. Outbox exposes
 * a callback registration for this purpose. The most recent ticket must be
 * provided when launching the application to keep the message flow consistent.
 * <p>
 * <strong>Design</strong>
 * <p>
 * Outbox architecture is designed to allow implementations in a range of
 * systems such as mobile platforms, scripting and high or low level languages.
 * Outbox can easily be implemented using either threads or event loops.
 * <p>
 * The base of the Outbox implementation is the endpoint representation which
 * have access to some network abstraction. It is responsible for reading and
 * writing data from/to a server instance and queue data when communication is
 * not possible. The queue gets flushed when communication is established. Its
 * objective is to always provide higher levels with a reliable channel no
 * matter current network state.
 * <p>
 * The endpoint is extended into two different practices, connection and
 * request. The connection is used to interface broker instances and implements
 * the portable message format. The request is used to query the backend about
 * publish-subscribe hierarchies and message history retrieval.
 * <p>
 * <strong>Hooks</strong>
 * <p>
 * A hook system is used for external functionality to intercept the message
 * flow. This system is used e.g. by the crypto layer to seamlessly encrypt and
 * decrypt messages.
 * <p>
 * <strong>Metadata</strong>
 * <p>
 * A message consists of a payload and some options. The options contains
 * instruction to the message broker, e.g. the TTL property. Most of these
 * options are piggybacked all the way to the target where they should be
 * considered metadata. Some additional data are set when a message flows
 * through the broker. These are in particular the origin and target properties
 * i.e. the identity of the source client and the identity used to target the
 * destination.
 * <p>
 * <strong>Listen, register, subscribe and publish</strong>
 * <p>
 * As mentioned, tags are used to target clients, both as individuals and as
 * groups with interest in a certain subject. One tag can subscribe to another
 * using the subscribe method call. This tells the broker that all messages
 * targeted for the subject should be delivered to the subscriber. Tags can
 * subscribe to each other in multiple levels, forming tree structures.
 * <p>
 * A publish method exists but is nothing more than an alias for the put method.
 * <p>
 * Before communication can occur, a client needs to listen for messages
 * targeted for some tag. This is done once using the listen method, analogously
 * to a regular socket listen procedure.
 * <p>
 * A common use case involves listen with an ephemeral random tag followed by
 * subscribing it to a more persistent well-known tag. This allows several,
 * perhaps temporary, devices to be represented by one single entity known to
 * others. This case is infact so common one can specify both the ephemeral and
 * the persistent tag in the same listen call to achieve exactly that. The
 * well-known tag will be included in the metadata as the from property when a
 * message is delivered at a target. The random tag may not be known at all to
 * other clients, i.e the origin property won't be of much use.
 * <p>
 * <strong>More about tags</strong>
 * <p>
 * Tag hierarchies can be resolved into a list of tags from a higher level tag.
 * This is done with the resolve method. Tags can also be checked for existence,
 * using tagsExist method. A client might want to make its use of some tag known
 * to others (e.g. for them to be able to use tagsExist to know it is setup),
 * this is done with the register method.
 * <p>
 * <strong>Dependencies</strong>
 * <p>
 * Outbox-cpp depends on Crypto++ and ASIO.
 */
 namespace apptimate {
     namespace outbox {
        class Outbox {
        public:
            /*** Option keys ***/
            static const std::string OPT_HOST;
            static const std::string OPT_PORT;
            static const std::string OPT_PUBLIC;
            static const std::string OPT_SECRET;
            static const std::string OPT_USER;
            static const std::string OPT_FROM;

            /*** Option/metadata keys ***/
            static const std::string KEY_TO;
            static const std::string KEY_FROM;
            static const std::string KEY_SEQ;
            static const std::string KEY_SEQ_SHORT;
            static const std::string KEY_SEQ_MY;
            static const std::string KEY_SEQ_YOUR;

            /*** Reserved address ***/
            static const std::string ADDR_API;
            static const std::string ADDR_MSG;

            /**
             * Message history constant.
             * <p>
             * Fetch all recent messages.
             */
            static const std::string HISTORY_ALL;

            /**
             * Message history constant.
             * <p>
             * Fetch no history at all.
             */
            static const std::string HISTORY_NONE;

            /**
             * Message time-to-live constant.
             * <p>
             * Default TTL i.e. 3600 seconds.
             */
            static const std::string TTL_DEFAULT;

            /**
             * Message time-to-live constant.
             * <p>
             * No TTL i.e. no buffering for message.
             */
            static const std::string TTL_NONE;

            /**
             * Message time-to-live constant.
             * <p>
             * Indefinite TTL i.e. buffer message until further notice.
             */
            static const std::string TTL_INDEF;

            /**
             * History special ticket.
             * <p>
             * Fetch no history at all.
             */
            static const std::string HIST_TICKET_NO;

            /**
             * History special ticket.
             * <p>
             * Fetch all available history.
             */
            static const std::string HIST_TICKET_ALL;

            /*** API KEY ACTION ***/
            static const std::string API_ACTION;

            /*** API KEY UID ***/
            static const std::string API_UID;

            /*** API KEY PARENT ***/
            static const std::string API_PARENT;

            /*** API ACTION SUBSCRIBE ***/
            static const std::string API_SUBSCRIBE;

            /*** API ACTION UNSUBSCRIBE ***/
            static const std::string API_UNSUBSCRIBE;

            /*** API RESULT ***/
            static const std::string API_RESULT;

            /*** API RESPONSE ***/
            static const std::string API_RESPONSE;

            /*** API SUCCESS ***/
            static const std::string API_SUCCESS;

            /*** API FAILURE ***/
            static const std::string API_FAILURE;

            /*** API VALUE UNKNOWN ***/
            static const std::string API_UNKNOWN;

            /**
             * Creates a new outbox.
             */
            Outbox() {
                opts["host"] = "pingapi.link";
                opts["port"] = 443;
            }

            /**
             * Attach inbox to receive messages.
             * <p>
             * Provide a filter to manage what messages ends up where in the application
             * logic.
             *
             * @param inbox inbox to receive messages in.
             * @param filter filter to manage what messages ends up where.
             */
            void attachInbox(const Inbox& inbox, const std::string& filter);

            /**
             * Attach inbox to receive messages.
             * <p>
             * Provide a filter to manage what messages ends up where in the application
             * logic.
             *
             * @param inbox inbox to receive messages in.
             * @param filter filter to manage what messages ends up where.
             */
            void attachInbox(const Inbox& inbox, const Filter& filter = Filter::NO_FILTER);

            /**
             * Detach inbox to stop receive messages.
             * <p>
             * Provide the filter used to attach the inbox to refine impact.
             *
             * @param inbox the inbox to detach.
             * @param filter filter used to attach the inbox to refine impact.
             */
            void detachInbox(const Inbox& inbox, const std::string& filter);

            /**
             * Detach inbox to stop receive messages.
             * <p>
             * Provide the filter used to attach the inbox to refine impact.
             *
             * @param inbox the inbox to detach.
             * @param filter filter used to attach the inbox to refine impact.
             */
            void detachInbox(const Inbox& inbox, const Filter& filter = Filter::NO_FILTER);

            /**
             * Set the logging level and contexts.
             *
             * @param level     The logging level to be used.
             * @param whiteList The contexts which to show.
             */
            void setLogLevelAndContextMask(const int& level, const int& whiteList);

            /**
             * Set options for this outbox instance.
             * <p>
             * All options are by nature optional.
             * <p>
             * Options map may contain:
             * <dl>
             * <dt><span class="strong">host</span></dt><dd>Apptimate message broker host name.</dd>
             * <dt><span class="strong">port</span></dt><dd>Apptimate message broker port number.</dd>
             * </dl>
             *
             * @param options string-object map of options.
             */
            void setOptions(const Values& options);

            /**
             * Set apptimate developer API keys.
             *
             * @param publicKey public identity of apptimate messaging application.
             * @param privateKey secret key of corresponding public identity.
             */
            void setAPIKeys(const std::string& publicKey, const std::string& privateKey);

            /**
             * Set apptimate developer API keys.
             *
             * @param publicKey public identity of apptimate messaging application.
             * @param privateKey secret key of corresponding public identity.
             * @param options the options
             */
            void setAPIKeys(const std::string& publicKey, const std::string& privateKey, Values options);

            /**
             * Puts a message payload into the outbox for transmission to targets.
             * <p>
             * An options map can be provided to control the behavior of the
             * transmission.
             * <p>
             * All options are by nature optional.
             * <p>
             * Options map may contain:
             * <dl>
             * <dt><span class="strong">ttl</span></dt><dd>Message time-to-live in seconds or TTL_* constant.</dd>
             * <dt><span class="strong">from</span></dt><dd>Use this option to shadow the well-know identity.</dd>
             * </dl>
             *
             * @param to target tag
             * @param payload payload string-object map
             * @param options string-object map of options. (optional)
             * @param inbox dedicated inbox for receiving responses. (optional)
             */
            void put(const std::string& to,
                     const Values&      payload,
                     Values             options = Values(),
                     const Inbox&       inbox = Inbox::NO_INBOX);

            /**
             * Resolve tag hierarchies into a list of tags from a higher level tag.
             *
             * @param tag high level tag to resolve.
             * @param callback invoked with result when operation finishes.
             */
            void resolveTag(const std::string& tag, const Callback& callback);

            /**
             * Make use of some tag known to others.
             * <p>
             * E.g. for them to be able to use tagsExist to know it is setup.
             *
             * @param tag the tag to register
             * @param callback invoked with result when operation finishes.
             */
            void registerTag(const std::string& tag, const Callback& callback);

            /**
             * Reverse the register process.
             *
             * @param tag the tag to unregister
             * @param callback invoked with result when operation finishes.
             */
            void unregisterTag(const std::string& tag, const Callback& callback);

            /**
             * Subscribe a tag to another.
             * <p>
             * Will tell the broker that all messages targeted for the subject should be
             * delivered to the subscriber. Tags can subscribe to each other in multiple
             * levels, forming tree structures.
             *
             * @param tag the identity of the subscriber, or some sub-subject
             * @param subject the subject to subscribe upon.
             * @param callback invoked with result when operation finishes.
             */
            void subscribeTag(const std::string& tag,
                              const std::string& subject,
                              const Callback&    callback);

            /**
             * Reverse the subscription process.
             *
             * @param tag the identity of the subscriber, or some sub-subject
             * @param subject the subject that was subscribed upon.
             * @param callback invoked with result when operation finishes.
             */
            void unsubscribeTag(const std::string& tag,
                                const std::string& subject,
                                const Callback&    callback);

            void registerForPushNotifications(const std::string& tag,
                                              const std::string& pushid,
                                              const bool&        debug,
                                              const Callback&    callback);

            /**
             * Outbox resume work.
             * <p>
             * Starting endpoint.
             */
            void resume();

            /**
             * Outbox resign work.
             * <p>
             * Stopping endpoints.
             */
            void resign();

            /**
             * Start message history tracking.
             * <p>
             * Provide most recent ticket or one of the HISTORY_* constants to enable
             * message history.
             *
             * @param ticket most recent ticket or HISTORY_* constant.
             * @param save callback invoked when an incoming ticket should be kept.
             */
            void startHistory(const std::string& ticket = "",
                              const Callback&    save   = Callback::NO_CALLBACK);

            /**
             * Trigger message history fetch.
             * <p>
             * May be invoked after being suspended.
             */
            void fetchHistory();

            /**
             * Stop message history tracking.
             */
            void stopHistory();

            /**
             * Check if tag exists.
             *
             * @param tag tag to check for existence.
             * @param callback invoked with result when operation finishes.
             */
            void tagExists(const std::string& tag, const Callback& callback);

            /**
             * Check if tags exist.
             *
             * @param tags list of tags to check for existence.
             * @param callback invoked with result when operation finishes.
             */
            void tagsExist(const std::vector<std::string>& tags, const Callback& callback);

            /**
             * Hashes the string if it starts with a hashtag.
             *
             * @param tag The string to be hashed.
             */
            std::string hashIfTag(const std::string& tag);

            /**
             * Starts the lifecycle.
             */
            void startLifecycle();

            /**
             * Stops the lifecycle.
             */
            void stopLifecycle();

            /**
             * Starts the outbox with the given tag.
             *
             * @param tag The tag to be used.
             */
            void startWithTag(const std::string& tag);

            /**
             * Starts the outbox with the given tag.
             *
             * @param tag      The tag to be used.
             * @param callback The callback function to be called with the result.
             */
            void startWithTag(const std::string& tag, const Callback& callback);

            void startWithAlias(const std::string& child, const std::string& parent);
            void startWithAlias(const std::string& child, const std::string& parent, const Callback& callback);

            /**
             * Get the internal hook system interface.
             *
             * @return the internal hook system interface.
             */
            Hooks& hooks();

            /**
             * Creates a unique tag.
             */
            static std::string createUniqueTag();

            std::string ensureSequenced(Values& values);

            /**
             * Closes the outbox.
             */
            void close();

        private:
            Hooks    hooks_;
            Notifier notifier;
            Values   opts;

            std::shared_ptr<Request>    request;
            std::shared_ptr<Connection> connection;
            std::shared_ptr<History>    history;
            std::shared_ptr<Lifecycle>  lifecycle;

        protected:
            /*** Default message service host. ***/
            static const std::string HOST;

            /*** Default message service port. ***/
            static const int PORT;

            bool running = false;

            Request& getRequest(const bool& create);
            Connection& getConnection(const bool& create);

            void run(const std::string& user, const std::string& from);
        };
    }
}