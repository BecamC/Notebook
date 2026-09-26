#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>

template <typename T>
class my_vector {
private:
    T*          m_data;
    std::size_t m_size;
    std::size_t m_cap;

    void reallocate(std::size_t new_cap) {
        if (new_cap <= m_cap) return;
        T* new_data = new T[new_cap];
        for (std::size_t i = 0; i < m_size; ++i)
            new_data[i] = std::move(m_data[i]);
        delete[] m_data;
        m_data = new_data;
        m_cap  = new_cap;
    }

public:
    my_vector() : m_data(nullptr), m_size(0), m_cap(0) {}

    my_vector(std::initializer_list<T> init)
        : m_data(nullptr), m_size(0), m_cap(0) {
        reallocate(init.size());
        for (const T& x : init) m_data[m_size++] = x;
    }

    explicit my_vector(std::size_t n, const T& value = T())
        : m_data(nullptr), m_size(0), m_cap(0) {
        reallocate(n);
        for (std::size_t i = 0; i < n; ++i) m_data[i] = value;
        m_size = n;
    }

    my_vector(const my_vector& other)
        : m_data(nullptr), m_size(other.m_size), m_cap(other.m_cap) {
        m_data = (m_cap ? new T[m_cap] : nullptr);
        for (std::size_t i = 0; i < m_size; ++i) m_data[i] = other.m_data[i];
    }

    my_vector& operator=(const my_vector& other) {
        if (this == &other) return *this;
        delete[] m_data;
        m_size = other.m_size;
        m_cap  = other.m_cap;
        m_data = (m_cap ? new T[m_cap] : nullptr);
        for (std::size_t i = 0; i < m_size; ++i) m_data[i] = other.m_data[i];
        return *this;
    }

    my_vector(my_vector&& other) noexcept
        : m_data(other.m_data), m_size(other.m_size), m_cap(other.m_cap) {
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_cap  = 0;
    }

    my_vector& operator=(my_vector&& other) noexcept {
        if (this == &other) return *this;
        delete[] m_data;
        m_data = other.m_data;
        m_size = other.m_size;
        m_cap  = other.m_cap;
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_cap  = 0;
        return *this;
    }

    ~my_vector() { delete[] m_data; }

    void push_back(const T& value) {
        if (m_size == m_cap)
            reallocate(m_cap == 0 ? 1 : m_cap * 2);
        m_data[m_size++] = value;
    }

    void pop_back() { if (m_size > 0) --m_size; }

    T&       operator[](std::size_t i)       { return m_data[i]; }
    const T& operator[](std::size_t i) const { return m_data[i]; }

    T& at(std::size_t i) {
        if (i >= m_size) throw std::out_of_range("my_vector::at");
        return m_data[i];
    }
    const T& at(std::size_t i) const {
        if (i >= m_size) throw std::out_of_range("my_vector::at");
        return m_data[i];
    }

    T&       front()       { return m_data[0]; }
    const T& front() const { return m_data[0]; }
    T&       back()        { return m_data[m_size - 1]; }
    const T& back()  const { return m_data[m_size - 1]; }

    std::size_t size()     const { return m_size; }
    std::size_t capacity() const { return m_cap; }
    bool        empty()    const { return m_size == 0; }

    void reserve(std::size_t new_cap) { reallocate(new_cap); }
    void clear() { m_size = 0; }

    T*       begin()       { return m_data; }
    T*       end()         { return m_data + m_size; }
    const T* begin() const { return m_data; }
    const T* end()   const { return m_data + m_size; }
};

#endif