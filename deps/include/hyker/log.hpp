#pragma once

// std
#include <mutex>
#include <string>

namespace hyker {
    class Log {
    public:
        static const int LOG_LEVEL_VERBOSE = 1;
        static const int LOG_LEVEL_DEBUG   = 2;
        static const int LOG_LEVEL_INFO    = 3;
        static const int LOG_LEVEL_WARN    = 4;
        static const int LOG_LEVEL_ERROR   = 5;

        static const unsigned int LOG_CONTEXT_ALL           = -1;
        static const unsigned int LOG_CONTEXT_UNSPECIFIED   = 1 << 0;
        static const unsigned int LOG_CONTEXT_SERVER        = 1 << 1;
        static const unsigned int LOG_CONTEXT_CONNECTION    = 1 << 2;
        static const unsigned int LOG_CONTEXT_LOCAL         = 1 << 3;
        static const unsigned int LOG_CONTEXT_COMMUNICATION = 1 << 4;

        /**
         * Set the logging level and contexts.
         *
         * @param level     The logging level to be used.
         * @param whiteList The contexts which to show.
         */
        static void setLogConditions(int level, int whiteList);

        /**
         * Logs a message.
         *
         * @param level   The severity level of the message.
         * @param context The context in which the message should be logged.
         * @param line    The text of the message.
         */
        static void log(int level, int context, std::string line);

    private:
        static int logLevel;
        static int whiteListMask;
    };
}