#pragma once

// RIKS++
#include "hyker/riks/exception.hpp"

// std
#include <memory>
#include <mutex>
#include <string>

// Boost.Serialization
namespace boost { namespace serialization { class access; } }

namespace hyker {
    namespace riks {
        class Nonce {
        public:
            class NonceExpiredException : public Exception {
            public:
                NonceExpiredException(const std::string& what) : Exception(what) {}
            };

            Nonce();
            Nonce(const std::string& b64Nonce);

            Nonce(const Nonce& nonce);
            Nonce& operator =(const Nonce& nonce);
            ~Nonce() = default;

            Nonce operator ++(int);
            unsigned long toLong() const;
            std::string toString() const;

        private:
            Nonce(unsigned long nonce);

            static const long NONCE_MAX;

            unsigned long m_nonce;
            bool m_unused;
            std::mutex m_mutex;

            friend class boost::serialization::access;

            template<typename Archive>
            void serialize(Archive& ar, const unsigned version) {
                ar & m_nonce;
                ar & m_unused;
            }
        };
    }
}