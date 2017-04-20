#pragma once

// Toolbox++
#include "hyker/exception.hpp"

// std
#include <string>

namespace hyker {
    namespace cryptobox {
        class Exception : public hyker::Exception {
        protected:
            Exception(const std::string& what) : hyker::Exception(what) {}
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