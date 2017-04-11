#pragma once

namespace boost { namespace serialization { class access; } }

namespace apptimate {
    template<typename T>
    class Wrapper {
        friend class boost::serialization::access;

    public:
        Wrapper(const T& t) : m_t(t) {}
        Wrapper& operator=(const T& t) { m_t = t; }
        Wrapper(T&& t) : m_t(std::move(t)) {}
        Wrapper& operator=(T&& t) { m_t = std::move(t); }
        operator T&() { return m_t; }
        T& get() { return m_t; }
        const T& get() const { return m_t; }

    private:
        Wrapper() {}
        T m_t;
        template<typename Archive>
        void serialize(Archive& ar, const unsigned version) {
            ar & m_t;
        }
    };
}