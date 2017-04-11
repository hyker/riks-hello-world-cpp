#pragma once

// Toolbox++
#include "apptimate/exception.hpp"

// std
#include <string>

namespace apptimate {
    namespace cryptobox {
        class Exception : public apptimate::Exception {
        protected:
            Exception(const std::string& what) : apptimate::Exception(what) {}
        };

        class CipherException : public Exception {
        public:
            CipherException() : CipherException("Cipher exception.") {}
            CipherException(const std::string &what) : Exception(what) {}
        };

        class IOException : public Exception {
        public:
            IOException() : IOException("I/O exception.") {}
            IOException(const std::string &what) : Exception(what) {}
        };
    }
}