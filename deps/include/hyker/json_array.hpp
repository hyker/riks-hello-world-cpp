#pragma once

// Toolbox++
#include "values.hpp"

// Jsonpp
#include "json/json.hpp"

// std
#include <functional>
#include <string>

namespace hyker {
    class Values;
    class JSONArray : public Json::Value {
    public:
        /**
         * Creates an empty JSONArray.
         */
        JSONArray();

        /**
         * Creates a JSONArray from the given value.
         *
         * @param value The JSON value.
         */
        JSONArray(Json::Value value);

        /**
         * Gets the string at the given index.
         * If there is no value at the given index, value will be equal to defaultValue.
         *
         * @param index        The index from which to get the string.
         * @param value        The value of the string.
         * @param defaultValue The default value. (optional)
         *
         * @return <b>true</b> if there is a value at the given index.
         */
        bool getString(const int& index, std::string& value, std::string defaultValue = "") const;

        /**
         * Gets the integer at the given index.
         * If there is no value at the given index, value will be equal to defaultValue.
         *
         * @param index        The index from which to get the integer.
         * @param value        The value of the integer.
         * @param defaultValue The default value. (optional)
         *
         * @return <b>true</b> if there is a value at the given index.
         */
        bool getInt(const int& index, int& value, int defaultValue = 0) const;

        /**
         * Gets the double at the given index.
         * If there is no value at the given index, value will be equal to defaultValue.
         *
         * @param index        The index from which to get the double.
         * @param value        The value of the double.
         * @param defaultValue The default value. (optional)
         *
         * @return <b>true</b> if there is a value at the given index.
         */
        bool getDouble(const int& index, double& value, double defaultValue = 0) const;

        /**
         * Gets the boolean at the given index.
         * If there is no value at the given index, value will be equal to defaultValue.
         *
         * @param index        The index from which to get the boolean.
         * @param value        The value of the boolean.
         * @param defaultValue The default value. (optional)
         *
         * @return <b>true</b> if there is a value at the given index.
         */
        bool getBool(const int& index,
                     bool& value,
                     bool defaultValue = 0) const;

        /**
         * Gets the JSONArray at the given index.
         *
         * @param index The index from which to get the JSONArray.
         * @param value The value of the JSONArray.
         *
         * @return <b>true</b> if there is a value at the given index.
         */
        bool getJSONArray(const int& index, JSONArray& value) const;

        /**
         * Gets the Values at the given index.
         *
         * @param index The index from which to get the Values.
         * @param value The value of the Values.
         *
         * @return <b>true</b> if there is a value at the given index.
         */
        bool getValues(const int& index, Values& value) const;

    };
}