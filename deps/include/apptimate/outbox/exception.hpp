#pragma once

#include "apptimate/exception.hpp"
#include <string>

namespace apptimate {
    namespace outbox {
        class Exception : public apptimate::Exception {
        protected:
            Exception(const std::string& what) : apptimate::Exception(what) {}
        };
    }
}