#pragma once

// Toolbox++
#include "exception.hpp"

// std
#include <map>
#include <string>

namespace hyker {
    class Property {
    public:
        class BadPropertyException : public Exception {
        public:
            BadPropertyException(const std::string& what) : Exception(what) {}
        };

        Property();
        Property(int value);
        Property(double value);
        Property(bool value);
        Property(long value);
        Property(const char* value);
        Property(const std::string& value);

        operator int();
        operator double();
        operator long();
        operator bool();
        operator const std::string&();

    private:
        std::string m_value;
    };

    class PropertyStore {
    public:
        class BadFormatException : public Exception {
        public:
            BadFormatException(const std::string& what) : Exception(what) {}
        };

        PropertyStore();

        static PropertyStore load(const std::string& path);

        Property operator[](const std::string& key) const;

    protected:
        void parse(const std::string& line);

    private:
        PropertyStore(std::map<std::string, Property> properties);

        std::map<std::string, Property> m_properties;
    };
}