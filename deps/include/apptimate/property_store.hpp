#pragma once

// Toolbox++
#include "exception.hpp"

// std
#include <map>
#include <string>

// Boost.Serialization
#include <boost/serialization/map.hpp>
#include <boost/serialization/string.hpp>
namespace boost { namespace serialization { class access; } }

namespace apptimate {
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
        operator std::string();

    private:
        std::string m_value;

        friend class boost::serialization::access;
        template<typename Archive>
        void serialize(Archive& ar, const unsigned version) {
            ar & m_value;
        }
    };

    class PropertyStore {
    public:
        class BadFormatException : public Exception {
        public:
            BadFormatException(const std::string& what) : Exception(what) {}
        };

        PropertyStore();
        static PropertyStore load(const std::string& path);

        Property operator [](const std::string& key) const;

    protected:
        void parse(const std::string& line);

    private:
        PropertyStore(std::map<std::string, Property> properties);

        std::map<std::string, Property> m_properties;

        friend class boost::serialization::access;
        template<typename Archive>
        void serialize(Archive& ar, const unsigned version) {
            ar & m_properties;
        }
    };
}