#pragma once

// Toolbox++
namespace apptimate {
    class PropertyStore;
}

// std
#include <string>

namespace apptimate {
    namespace cryptobox {
        const std::string DEFAULT_CONFIGURATION         = "default.config";

        const std::string AUTOMATIC_REKEYING            = "automatic_rekeying";
        const std::string BACKEND_IP                    = "backend_IP";
        const std::string BACKEND_PORT                  = "backend_port";
        const std::string CACHE_EXPIRATION              = "cache_expiration";
        const std::string CERTIFICATE_EXCHANGE_KEYSTORE = "certificate_exchange_keystore";
        const std::string CERTIFICATE_EXCHANGE_ENABLED  = "certificate_exchange_enabled";
        const std::string DEFAULT_KEY_VALIDITY          = "default_key_validity";
        const std::string KDI_KEY_STORES_PATH           = "kdi_key_stores_path";
        const std::string KEY_DIST_CREDENTIALS          = "key_dist_credentials";
        const std::string KEY_PATH                      = "key_path";
        const std::string PRIVATE_API_KEY               = "private_api_key";
        const std::string PUBLIC_API_KEY                = "public_api_key";
        const std::string PUBLIC_KEY_LOOKUP_ENABLED     = "public_key_lookup_enabled";
        const std::string PUBLIC_KEY_LOOKUP_URL         = "public_key_lookup_url";
        const std::string REQUIRE_SIGNED_KEYS           = "require_signed_keys";
        const std::string SIGNING_KEY_ALIAS             = "signing_key_alias";
        const std::string TRUST_STORE                   = "trust_store";
        const std::string TRUST_STORE_PASSWORD          = "trust_store_password";

        const PropertyStore& checkConfiguration(const PropertyStore& propertyStore);
    };
};