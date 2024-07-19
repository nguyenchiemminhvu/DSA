#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <initializer_list>
#include <algorithm>

template <typename T>
class Deque
{
public:
    using iterator = T*;
    using const_iterator = const T*;

    Deque()
        : m_data(nullptr)
        , m_size(0U)
        , m_capacity(0U)
        , m_front_idx(0U)
        , m_back_idx(0U)
    {
    }

    Deque(const std::initializer_list<T>& L)
        : m_data(nullptr)
        , m_size(0U)
        , m_capacity(0U)
        , m_front_idx(0U)
        , m_back_idx(0U)
    {
        if (L.size() > 0U)
        {
            m_size = L.size();
            m_capacity = L.size();
            m_back_idx = L.size() - 1;
            m_data = new T[m_back_idx];
            std::copy(L.begin(), L.end(), m_data);
        }
    }

    Deque(const Deque<T>& another)
        : m_data(nullptr)
        , m_size(0U)
        , m_capacity(0U)
        , m_front_idx(0U)
        , m_back_idx(0U)
    {
        if (another.m_data != nullptr)
        {
            m_size = another.m_size;
            m_capacity = another.m_capacity;
            m_front_idx = another.m_front_idx;
            m_back_idx = another.m_back_idx;
            m_data = new T[m_capacity];
            std::copy(another.m_data, another.m_data + m_capacity, m_data);
        }
    }

    ~Deque()
    {
        if (m_data != nullptr)
        {
            delete[] m_data;
        }
    }

    void swap(Deque<T>& another)
    {
        std::swap(m_data, another.m_data);
        std::swap(m_size, another.m_size);
        std::swap(m_capacity, another.m_capacity);
        std::swap(m_front_idx, another.m_front_idx);
        std::swap(m_back_idx, another.m_back_idx);
    }

    T& operator[](const std::size_t index)
    {
        if (index >= m_size)
        {
            throw std::out_of_range("Index out of range");
        }

        return m_data[(m_front_idx + index) % m_capacity];
    }

    void push_back(const T& value)
    {
        ensure_capacity();

        m_back_idx = (m_back_idx + 1U) % m_capacity;
        m_data[m_back_idx] = value;
        m_size++;
    }

    void push_front(const T& value)
    {
        ensure_capacity();

        m_front_idx = (m_front_idx + m_capacity - 1) % m_capacity;
        m_data[m_front_idx] = value;
        m_size++;
    }

    void pop_back()
    {
        if (empty())
        {
            throw std::out_of_range("Access empty deque");
        }

        m_back_idx = (m_back_idx + m_capacity - 1U) % m_capacity;
        m_size--;
    }

    void pop_front()
    {
        if (empty())
        {
            throw std::out_of_range("Access empty deque");
        }

        m_front_idx = (m_front_idx + 1U) % m_capacity;
        m_size--;
    }

    void clear()
    {
        if (m_data != nullptr)
        {
            delete[] m_data;
        }
        m_data = nullptr;
        m_size = 0U;
        m_capacity = 0U;
        m_front_idx = 0U;
        m_back_idx = 0U;
    }

    T& back()
    {
        if (empty())
        {
            throw std::out_of_range("Access empty deque");
        }

        return m_data[m_back_idx];
    }

    const T& back() const
    {
        if (empty())
        {
            throw std::out_of_range("Access empty deque");
        }

        return m_data[m_back_idx];
    }

    T& front()
    {
        if (empty())
        {
            throw std::out_of_range("Access empty deque");
        }

        return m_data[m_front_idx];
    }

    const T& front() const
    {
        if (empty())
        {
            throw std::out_of_range("Access empty deque");
        }

        return m_data[m_front_idx];
    }

    bool empty() const
    {
        return m_size == 0U;
    }

    std::size_t size() const
    {
        return m_size;
    }

    std::size_t capacity() const
    {
        return m_capacity;
    }

private:
    void ensure_capacity()
    {
        if (m_size == m_capacity)
        {
            std::size_t new_cap = m_capacity == 0U ? 1U : m_capacity * 2U;
            T* new_data = new T[new_cap];
            
            for (std::size_t i = 0U; i < m_size; i++)
            {
                new_data[i] = m_data[(m_front_idx + i) % m_capacity];
            }

            delete[] m_data;
            m_data = new_data;
            m_capacity = new_cap;
            m_front_idx = 0U;
            m_back_idx = m_size > 0U ? m_size - 1U : 0U;
        }
    }

private:
    T* m_data;
    std::size_t m_size;
    std::size_t m_capacity;
    std::size_t m_front_idx;
    std::size_t m_back_idx;
};

#endif // DEQUE_H