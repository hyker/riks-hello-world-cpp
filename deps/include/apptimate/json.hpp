#pragma once

// Toolbox++
#include "values.hpp"

// std
#include <string>

namespace apptimate {
    class JSON {
    public:
        /**
         * Converts a given Values to a JSON string representation.
         *
         * @param jsonMap The Values to be converted.
         *
         * @return The resulting JSON string representation.
         */
        static std::string encode(const Values& values);

        /**
         * Converts a given JSON string representation to a Values.
         *
         * @param jsonMap The JSON string representation to be converted.
         *
         * @return The resulting Values.
         */
        static Values decode(const std::string& jsonString);
    };
}