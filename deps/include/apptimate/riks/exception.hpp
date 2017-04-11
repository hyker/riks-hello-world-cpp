#pragma once

// Toolbox++
#include "apptimate/exception.hpp"

namespace apptimate {
    namespace riks {
        class Exception : public apptimate::Exception {
        protected:
            Exception(const std::string& what) : apptimate::Exception(what) {}
        };

        class IllegalArgumentException : public Exception {
        public:
            IllegalArgumentException() : IllegalArgumentException("Illegal argument.") {}
            IllegalArgumentException(const std::string& what) : Exception(what) {}
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

        class NoSuchElementException : public Exception {
        public:
            NoSuchElementException() : NoSuchElementException("No such element.") {}
            NoSuchElementException(const std::string& what) : Exception(what) {}
        };
    }
}