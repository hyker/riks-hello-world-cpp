#pragma once

// std
#include <string>

namespace apptimate {
    namespace cryptobox {
        class SSLClient {
        public:
            /**
             * Make a GET request to the given host, over SSL.
             *
             * @param host The host URL.
             * @param port The host port.
             * @param path The path to make the request to.
             * @param contentType The content type of the data to be sent.
             * @param content The content to be sent.
             *
             * @return The response.
             */
            static std::string get(const std::string& host,
                                   int                port,
                                   const std::string& path,
                                   const std::string& contentType,
                                   const std::string& content);
        };
    };
};