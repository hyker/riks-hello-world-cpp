#pragma once

// Toolbox++
#include "exception.hpp"
#include "hyker/property_store.hpp"

// std
#include <functional>
#include <string>

namespace hyker {
    class BadConfigurationException : public Exception {
    public:
        BadConfigurationException(const std::string& what) : Exception(what) {}
    };

    template<typename S>
    using Validator = std::function<void(S s)>;

    class Configuration {
    public:
        Configuration(const PropertyStore& propertyStore) : m_propertyStore (propertyStore) {}

        template<typename S>
        void check(const std::string& name, Validator<S> validator = [](S s){}) {
            validator([&]() {
                try {
                    return (S)m_propertyStore[name];
                } catch (hyker::Exception& e) {
                    throw PropertyStore::BadFormatException(name + " is not a valid value. (" + e.what() + ')');
                }
            }());
        }

    private:
        const PropertyStore& m_propertyStore;
    };
};