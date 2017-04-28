#pragma once

// std
#include <map>
#include <memory>
#include <mutex>
#include <utility>

template<typename S, typename T>
class ConcurrentMap {
public:
    class Monitor {
    public:
        Monitor& operator=(const Monitor& other) { std::unique_lock<std::mutex> lock(m_mutex); *this = other.m_value; return *this; }
        Monitor& operator=(Monitor&& other) { std::unique_lock<std::mutex> lock(m_mutex); *this = std::move(other.m_value); return *this; }
        Monitor& operator=(const T& value) { std::unique_lock<std::mutex> lock(m_mutex); m_value = value; return *this; }
        Monitor& operator=(T&& value) { std::unique_lock<std::mutex> lock(m_mutex); m_value = std::move(value); return *this; }

        operator bool() { std::unique_lock<std::mutex> lock(m_mutex); return (bool)m_value; }
        operator T&() { std::unique_lock<std::mutex> lock(m_mutex); return m_value; }

    private:
        T m_value;
        std::mutex m_mutex;
    };

    ConcurrentMap() {}
    ConcurrentMap(const ConcurrentMap& other) : m_map(other.m_map) {}
    ConcurrentMap(ConcurrentMap&& other) : m_map(std::move(other.m_map)) {}
    ConcurrentMap& operator=(const ConcurrentMap& other) { m_map = other.m_map; return *this; }
    ConcurrentMap& operator=(ConcurrentMap&& other) { m_map = std::move(other.m_map); return *this; }

    T& operator[](const S& key) {
        std::unique_lock<std::mutex> lock(m_mutex);
        return m_map[key];
    }

    bool has(const S& key) {
        std::unique_lock<std::mutex> lock(m_mutex);
        return m_map.find(key) != m_map.end();
    }

protected:
    std::map<S, Monitor> m_map;
    std::mutex m_mutex;
};