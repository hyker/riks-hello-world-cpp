#pragma once

// std
#include <mutex>
#include <string>

namespace hyker {

    constexpr int LOG_LEVEL_VERBOSE = 1;
    constexpr int LOG_LEVEL_DEBUG   = 2;
    constexpr int LOG_LEVEL_INFO    = 3;
    constexpr int LOG_LEVEL_WARN    = 4;
    constexpr int LOG_LEVEL_ERROR   = 5;

    constexpr unsigned int LOG_CONTEXT_ALL           = -1;
    constexpr unsigned int LOG_CONTEXT_UNSPECIFIED   = 1 << 0;
    constexpr unsigned int LOG_CONTEXT_SERVER        = 1 << 1;
    constexpr unsigned int LOG_CONTEXT_CONNECTION    = 1 << 2;
    constexpr unsigned int LOG_CONTEXT_LOCAL         = 1 << 3;
    constexpr unsigned int LOG_CONTEXT_COMMUNICATION = 1 << 4;

    class Log {
    public:
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
        static std::mutex mutex;

        static int log_level;
        static int whitelist_mask;

        static bool color_codes;
        static bool cleared;

	constexpr static const char* def     = "\033[0m";
	constexpr static const char* red     = "\033[1;31m";
	constexpr static const char* orange  = "\033[33m";
	constexpr static const char* green   = "\033[32m";
	constexpr static const char* magenta = "\033[35m";
	constexpr static const char* cls     = "\033[2J\033[1;1H";
    };

}
