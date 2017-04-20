#pragma once

#include "hyker/configuration.hpp"

#include <string>

namespace hyker {
    namespace riks {
        const std::string DEFAULT_CONFIGURATION       = "default.config";

        const std::string AUTOMATIC_QUERY_ENABLED     = "automatic_query_enabled";
        const std::string AUTOMATIC_QUERY_TIMEOUT     = "automatic_query_timeout";
        const std::string PERSISTENCE_PATH            = "persistence_path";
        const std::string PERSISTENCE_PASSWORD        = "persistence_password";
        const std::string NONCE_VALIDATOR_WINDOW_SIZE = "nonce_validator_window_size";
        const std::string KEY_RELAY_ENABLED           = "key_relay_enabled";

        const PropertyStore& checkConfiguration(const PropertyStore& propertyStore);
    };
};