#pragma once

// std
#include <stdexcept>
#include <string>

namespace apptimate {
    class Exception : public std::runtime_error {
    public:
        Exception(const std::string& what) : std::runtime_error(what) {}
    };

    class IOException : public Exception {
    public:
        IOException(const std::string& what) : Exception(what) {}
    };

    class FileNotFoundException : public IOException {
    public:
        FileNotFoundException(const std::string& what) : IOException(what) {}
    };

    class NoSuchElementException : public Exception {
    public:
        NoSuchElementException() : NoSuchElementException("No such element.") {}
        NoSuchElementException(const std::string& what) : Exception(what) {}
    };

    class IllegalArgumentException : public Exception {
    public:
        IllegalArgumentException() : IllegalArgumentException("Illegal argument.") {}
        IllegalArgumentException(const std::string& what) : Exception(what) {}
    };

    class IllegalStateException : public Exception {
    public:
        IllegalStateException() : IllegalStateException("Illegal state.") {}
        IllegalStateException(const std::string& what) : Exception(what) {}
    };
}