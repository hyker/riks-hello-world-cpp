#pragma once

// Toolbox++
#include "hyker/exception.hpp"

namespace hyker {
    namespace riks {
        class Exception : public hyker::Exception {
        protected:
            Exception(const std::string& what) : hyker::Exception(what) {}
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