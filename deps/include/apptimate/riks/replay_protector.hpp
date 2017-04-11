#pragma once

// RIKS++
#include "apptimate/riks/keys/nonce.hpp"

// std
#include <map>
#include <memory>
#include <string>
#include <vector>

// Boost.Serialization
#include <boost/serialization/map.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
namespace boost { namespace serialization { class access; } }

namespace apptimate {
    namespace riks {
        class ReplayProtector {
        public:
            class ReplayException : public Exception {
            public:
                ReplayException(const std::string &what) : Exception(what) {}
            };

            class NonceOutsideReplayWindowException : public Exception {
            public:
                NonceOutsideReplayWindowException(const std::string &what) : Exception(what) {}
            };

            ReplayProtector(int windowSize);

            void check(const std::string& keyID, const Nonce& nonce);
            void reset();
            void reset(const std::string& keyID);

        private:
            ReplayProtector() {}

            class ReplayWindow {
            public:
                ReplayWindow(int windowSize);

                void check(const Nonce& nonce);
                void reset();

            private:
                ReplayWindow() {}

                int m_windowSize;
                std::vector<bool> m_window;
                unsigned long m_currentNonce = 0;

                friend class boost::serialization::access;
                template<typename Archive>
                void serialize(Archive& ar, const unsigned version) {
                    ar & m_windowSize;
                    ar & m_window;
                    ar & m_currentNonce;
                }
            };

            static std::string getPath(const std::string& path, const std::string& uid);

            int m_windowSize;
            std::map<std::string, std::shared_ptr<ReplayWindow>> m_replayWindows;
            std::mutex m_mutex;

            friend class boost::serialization::access;
            template<typename Archive>
            void serialize(Archive& ar, const unsigned version) {
                ar & m_windowSize;
                ar & m_replayWindows;
            }
        };
    }
}