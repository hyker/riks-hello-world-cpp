#pragma once

#include <string>

namespace apptimate {
    namespace riks {
        class Constants {
        public:
            static const int MESSAGE_NONCE_LENGTH; // bits
            static const int SYM_KEY_LENGTH; // bytes
            static const int KEY_ID_LENGTH; // bytes
            static const int TAG_LENGTH; // bytes

            // encrypted file storeage
            static const int PBE_SALT_LENGTH;
            static const int PBE_KEY_DERIVATION_ITERATIONS;
            static const int PBE_KEY_LENGTH;
            static const std::string PBE_KEY_DERIVATION_FUNCTION;
            static const std::string PBE_ENCRYPTION_ALG;

            // packet header io.apptimate.riks.keys
            static const std::string ACTION;
            static const std::string VERSION;
            static const std::string KEY_ID;
            static const std::string SENDER;
            static const std::string DATA_CIPHER_TEXT;
            static const std::string DATA_IP;
            static const std::string DATA_MUTABLE;
            static const std::string NONCE;
            static const std::string KEY;
            static const std::string SIGNATURE;

            // packet header values
            static const std::string VERSION_VAL;
            static const std::string SYM_MSG;
            static const std::string ACCESS_REQ;
            static const std::string ACCESS_RESP;
        };
    }
}