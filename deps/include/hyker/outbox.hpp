#pragma once

// Outbox++
#include "hyker/outbox/hooks.hpp"
#include "hyker/outbox/notifier.hpp"
#include "hyker/outbox/callback.hpp"
#include "hyker/outbox/inbox.hpp"
#include "hyker/outbox/filter.hpp"

// Core (Toolbox++)
#include "hyker/values.hpp"

// std
#include <memory>
#include <string>
#include <vector>

namespace hyker {
    namespace outbox {
        class Outbox {
        public:
            Outbox();
            ~Outbox();

            Outbox(Outbox&&) noexcept;
            Outbox& operator=(Outbox&&) noexcept;

            void attachInbox(const Inbox& inbox, const Filter& filter = Filter::NO_FILTER);
            void detachInbox(const Inbox& inbox, const Filter& filter = Filter::NO_FILTER);

            void setLogLevelAndContextMask(int level, int whitelist);
            void setOptions(const Values& options);
            void setAPIKeys(const std::string& public_key, const std::string& private_key);
            void setAPIKeys(const std::string& public_key, const std::string& private_key, Values options);

            void put(const std::string& to, const Values& payload, Values options = Values(), const Inbox& inbox = Inbox::NO_INBOX);

            void resolveTag(const std::string& tag, const Callback& callback);
            void registerTag(const std::string& tag, const Callback& callback);
            void unregisterTag(const std::string& tag, const Callback& callback);
            void subscribeTag(const std::string& tag, const std::string& subject, const Callback& callback);
            void unsubscribeTag(const std::string& tag, const std::string& subject, const Callback& callback);
            void registerForPushNotifications(const std::string& tag, const std::string& push_id, bool debug, const Callback& callback);

            void resume();
            void resign();
            void startHistory(const std::string& ticket = "", const Callback& save = Callback::NO_CALLBACK);
            void fetchHistory();
            void stopHistory();

            void tagExists(const std::string& tag, const Callback& callback);
            void tagsExist(const std::vector<std::string>& tags, const Callback& callback);

            std::string hashIfTag(const std::string& tag);

            void startWithTag(const std::string& tag);
            void startWithTag(const std::string& tag, const Callback& callback);
            void startWithAlias(const std::string& child, const std::string& parent);
            void startWithAlias(const std::string& child, const std::string& parent, const Callback& callback);

            static std::string createUniqueTag();

            std::string ensureSequenced(Values& values) const;
            void close();

            Hooks& hooks();
            Notifier& notifier();

            static const std::string OPT_HOST;
            static const std::string OPT_PORT;
            static const std::string OPT_PUBLIC;
            static const std::string OPT_SECRET;
            static const std::string OPT_USER;
            static const std::string OPT_FROM;
            static const std::string KEY_TO;
            static const std::string KEY_FROM;
            static const std::string KEY_SEQ;
            static const std::string KEY_SEQ_SHORT;
            static const std::string KEY_SEQ_MY;
            static const std::string KEY_SEQ_YOUR;
            static const std::string ADDR_API;
            static const std::string ADDR_MSG;
            static const std::string HISTORY_ALL;
            static const std::string HISTORY_NONE;
            static const std::string TTL_DEFAULT;
            static const std::string TTL_NONE;
            static const std::string TTL_INDEF;
            static const std::string HIST_TICKET_NO;
            static const std::string HIST_TICKET_ALL;
            static const std::string API_ACTION;
            static const std::string API_UID;
            static const std::string API_PARENT;
            static const std::string API_SUBSCRIBE;
            static const std::string API_UNSUBSCRIBE;
            static const std::string API_RESULT;
            static const std::string API_RESPONSE;
            static const std::string API_SUCCESS;
            static const std::string API_FAILURE;
            static const std::string API_UNKNOWN;

        private:
            class Impl;
            std::unique_ptr<Impl> m_impl;
        };
    }
}