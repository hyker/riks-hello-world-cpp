#pragma once

// Toolbox++
#include "exception.hpp"

// Jsonpp
#include "json/json.hpp"
#include "json_array.hpp"

// std
#include <functional>
#include <string>

namespace apptimate {
    class JSONArray;
    class Values : public Json::Value {
    public:
        /**
         * Creates a Values from the given value.
         *
         * @param value The JSON value.
         */
        Values(const Json::Value& map);

        /**
         * Creates a new Values with the given pair.
         */
        static Values init(const std::string& key, const std::string& value);

        /**
         * Creates an empty Values.
         */
        Values();

        bool containsKey(const std::string& key) const;
        bool containsString(const std::string& key) const;
        bool containsInt(const std::string& key) const;
        bool containsDouble(const std::string& key) const;
        bool containsBool(const std::string& key) const;
        bool containsValues(const std::string& key) const;

        /**
         * Gets the string with the given key.
         * If there is no value with the given key, value will be equal to defaultValue.
         *
         * @param key          The key with which the string is associated.
         * @param value        The value of the string.
         * @param defaultValue The default value. (optional)
         *
         * @return <b>true</b> if there is a value with the given key.
         */
        std::string getString(const std::string& key) const;
        bool getString(const std::string& key, std::string& value, const std::string& defaultValue = "") const;

        /**
         * Gets the integer with the given key.
         * If there is no value with the given key, value will be equal to defaultValue.
         *
         * @param key          The key with which the integer is associated.
         * @param value        The value of the integer.
         * @param defaultValue The default value. (optional)
         *
         * @return <b>true</b> if there is a value with the given key.
         */
        int getInt(const std::string& key) const;
        bool getInt(const std::string& key, int& value, const int& defaultValue = 0) const;

        /**
         * Gets the double with the given key.
         * If there is no value with the given key, value will be equal to defaultValue.
         *
         * @param key          The key with which the double is associated.
         * @param value        The value of the double.
         * @param defaultValue The default value. (optional)
         *
         * @return <b>true</b> if there is a value with the given key.
         */
        double getDouble(const std::string& key) const;
        bool getDouble(const std::string& key, double& value, const double& defaultValue = 0) const;

        /**
         * Gets the boolean with the given key.
         * If there is no value with the given key, value will be equal to defaultValue.
         *
         * @param key          The key with which the boolean is associated.
         * @param value        The value of the boolean.
         * @param defaultValue The default value. (optional)
         *
         * @return <b>true</b> if there is a value with the given key.
         */
        bool getBool(const std::string& key) const;
        bool getBool(const std::string& key, bool& value, const bool& defaultValue = false) const;

        /**
         * Gets the JSONArray with the given key.
         *
         * @param key   The key with which the JSONArray is associated.
         * @param value The value of the JSONArray.
         *
         * @return <b>true</b> if there is a value with the given key.
         */
        JSONArray getJSONArray(const std::string& key) const;
        bool getJSONArray(const std::string& key, JSONArray& value) const;

        /**
         * Gets the Values with the given key.
         *
         * @param key   The key with which the Values is associated.
         * @param value The value of the Values.
         *
         * @return <b>true</b> if there is a value with the given key.
         */
        Values getValues(const std::string& key) const;
        bool getValues(const std::string& key, Values& value) const;
    };
}