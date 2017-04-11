#pragma once

// Toolbox++
#include "exception.hpp"

// std
#include <chrono>
#include <condition_variable>
#include <ctime>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <utility>
#include <vector>

// Boost.Serialization
#include <boost/serialization/map.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>
namespace boost { namespace serialization { class access; } }

namespace apptimate {
    template<typename S, typename T>
    class CacheMap {
        friend class boost::serialization::access;

    public:
        using CacheMapCallback = std::function<void(T&)>;

        class InterruptedException : public Exception {
        public:
            InterruptedException(const std::string& what) : Exception(what) {}
        };

        class TimeoutException : public Exception {
        public:
            TimeoutException(const std::string& what) : Exception(what) {}
        };

        class Monitor {
            friend class boost::serialization::access;

        public:
            Monitor() : m_ttl(-1) {}
            Monitor(long ttl) : m_ttl(ttl) {}

            Monitor(const Monitor& other) :
                    m_timestamp(other.m_timestamp),
                    m_ttl(other.m_ttl),
                    m_value(new T(*other.m_value)),
                    m_callbacks(other.m_callbacks) {
            }
            Monitor& operator=(const Monitor& other) {
                m_timestamp = other.m_timestamp;
                m_ttl = other.m_ttl;
                m_value = new T(*other.m_value);
                m_callbacks = other.m_callbacks;
                return *this;
            }

            Monitor(Monitor&& other) :
                    m_timestamp(std::move(other.m_timestamp)),
                    m_ttl(std::move(other.m_ttl)),
                    m_value(std::move(other.m_value)),
                    m_callbacks(std::move(other.m_callbacks)) {
            }
            Monitor& operator=(Monitor&& other) {
                m_timestamp = std::move(other.m_timestamp);
                m_ttl = other.m_ttl;
                m_value = std::move(other.m_value);
                m_callbacks = std::move(other.m_callbacks);
                return *this;
            }

            Monitor& operator=(const T& value) {
                set(new T(value));
                return *this;
            }
            Monitor& operator=(T&& value) {
                set(new T(std::move(value)));
                return *this;
            }

            operator bool() { return (bool) m_value; }
            operator T&() { return get(); }

            T& get() {
                std::unique_lock<std::mutex> lock(m_mutex);
                if (!m_value) throw NoSuchElementException("No such element.");
                if ((m_ttl != -1) && (std::time(0) - m_timestamp > m_ttl)) throw TimeoutException("CacheMap timed out.");
                return *m_value;
            }

            T& wait() {
                std::unique_lock <std::mutex> lock(m_mutex);
                if (!m_value) m_cv.wait(lock);
                if (!m_value) throw InterruptedException("Monitor interrupted.");
                return *m_value;
            }

            T& wait(unsigned long timeout) {
                std::unique_lock<std::mutex> lock(m_mutex);

                if (m_value) return *m_value;
                else {
                    if (m_cv.wait_until(lock, std::chrono::system_clock::now() + std::chrono::milliseconds(timeout)) ==
                        std::cv_status::no_timeout) {
                        if (!m_value) throw InterruptedException("Monitor interrupted.");
                        else return *m_value;
                    } else throw TimeoutException("CacheMap timed out.");
                }
            }

            void wait(const CacheMapCallback& callback) {
                std::unique_lock <std::mutex> lock(m_mutex);
                if (m_value) callback(*m_value);
                else m_callbacks.push_back(callback);
            }

            void interrupt() {
                std::unique_lock<std::mutex> lock(m_mutex);
                m_cv.notify_all();
            }

            friend std::ostream& operator<<(std::ostream& os, Monitor& monitor) {
                os << monitor.get();
                return os;
            }

        private:
            void set(T* value) {
                std::unique_lock<std::mutex> lock(m_mutex);
                m_value = std::unique_ptr<T>(value);
                m_timestamp = time(0);

                for (auto& callback : m_callbacks)
                    callback(*m_value);
                m_callbacks.clear();
                m_cv.notify_all();
            }

            long m_timestamp = -1;
            long m_ttl;
            std::unique_ptr<T> m_value;
            std::vector<CacheMapCallback> m_callbacks;
            std::condition_variable m_cv;
            std::mutex m_mutex;

            template<typename Archive>
            void save(Archive& ar, const unsigned version) const {
                bool hasValue = m_value != nullptr;
                ar & hasValue;
                if (hasValue) ar & *m_value;
                ar & m_timestamp;
                ar & m_ttl;
            }
            template<typename Archive>
            void load(Archive& ar, const unsigned version) {
                std::unique_lock<std::mutex> lock(m_mutex);
                bool hasValue;
                ar & hasValue;
                if (hasValue) ar & *m_value;
                ar & m_timestamp;
                ar & m_ttl;
            }
            BOOST_SERIALIZATION_SPLIT_MEMBER()
        };

        CacheMap() : CacheMap(-1) {}
        CacheMap(long ttl) : m_ttl(ttl) {
            if (ttl < -1) throw IllegalArgumentException("ttl cannot be less than -1");
        }

        CacheMap(const CacheMap& other) : m_map(other.m_map), m_ttl(other.m_ttl) {}
        CacheMap& operator=(const CacheMap& other) {
            m_map = other.m_map;
            m_ttl = other.m_ttl;
            return *this;
        }

        CacheMap(CacheMap&& other) : m_map(std::move(other.m_map)), m_ttl(std::move(other.m_ttl)) {}
        CacheMap& operator=(CacheMap&& other) {
            m_map = std::move(other.m_map);
            m_ttl = other.m_ttl;
            return *this;
        }

        Monitor& operator[](const S& key) {
            std::unique_lock<std::mutex> lock(m_mutex);
            if (m_map.find(key) == m_map.end()) m_map.insert(std::make_pair(key, Monitor(m_ttl)));
            return m_map.at(key);
        }

        void remove(const S& key) {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_map.erase(key);
        }

        size_t size() {
            std::unique_lock<std::mutex> lock(m_mutex);
            return m_map.size();
        }

        std::vector<S> keys() {
            std::unique_lock<std::mutex> lock(m_mutex);
            std::vector<S> keys;
            for (auto it = m_map.begin(); it != m_map.end(); ++it) {
                keys.push_back(it->first);
            }
            return keys;
        }

    private:
        std::mutex m_mutex;
        std::map<S, Monitor> m_map;
        long m_ttl;

        template<typename Archive>
        void serialize(Archive& ar, const unsigned version) {
            std::unique_lock<std::mutex> lock(m_mutex);
            ar & m_map;
            ar & m_ttl;
        }
    };
}