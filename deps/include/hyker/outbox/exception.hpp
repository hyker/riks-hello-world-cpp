#pragma once

#include "hyker/exception.hpp"
#include <string>

namespace hyker {
    namespace outbox {
        class Exception : public hyker::Exception {
        protected:
            Exception(const std::string& what) : hyker::Exception(what) {}
        };
    }
}