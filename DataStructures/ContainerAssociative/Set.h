#ifndef SET_H
#define SET_H

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <initializer_list>
#include <algorithm>

template <typename T, Comparator = std::less<T>>
class Set
{
public:
    using iterator = T*;
    using const_iterator = const T*;

    Set()
        : m_data(nullptr)
        , m_size(0U)
        , m_capacity(0U)
        , m_comparator(Comparator())
    {
    }

    Set(const std::initializer_list<T>& L)
        : Set()
    {
        for (const T& key : L)
        {
            insert(key);
        }
    }
    
    Set(const Set<T>& another)
        : Set()
    {
        m_size = another.m_size;
        m_capacity = another.m_capacity;
        m_comparator = another.m_comparator;
        if (m_capacity > 0U)
        {
            m_data = new T[m_capacity];
            std::copy(another.m_data, another.m_data + m_size, m_data);
        }
    }

    ~Set()
    {
        if (m_data != nullptr)
        {
            delete[] m_data;
        }
    }

    void swap(Set<T>& another)
    {
        std::swap(m_data, another.m_data);
        std::swap(m_size, another.m_size);
        std::swap(m_capacity, another.m_capacity);
        std::swap(m_comparator, another.m_comparator);
    }

    void insert(const T& key)
    {
        ensure_capacity();


    }

    void erase(const T& key)
    {
        
    }

    void clear()
    {
        if (m_data != nullptr)
        {
            delete[] m_data;
            m_data = nullptr;
        }

        m_size = 0U;
        m_capacity = 0U;
    }

    std::size_t count(const T& key)
    {
        return 0U;
    }

    iterator find(const T& key)
    {
        return nullptr;
    }

    iterator begin()
    {
        return m_data;
    }

    const_iterator begin() const
    {
        return m_data;
    }

    iterator end()
    {
        return m_data + m_size;
    }

    const_iterator end() const
    {
        return m_data + m_size;
    }

    std::size_t size() const
    {
        return m_size;
    }

    std::size_t capacity() const
    {
        return m_capacity;
    }

    bool empty()
    {
        return m_size == 0U;
    }

private:
    void ensure_capacity()
    {
        if (m_size == m_capacity)
        {
            std::size_t new_cap = m_capacity == 0U ? 1U : m_capacity * 2U;
            T* new_data = new T[new_cap];
            if (m_data != nullptr)
            {
                std::copy(m_data, m_data + m_size, new_data);
                delete[] m_data;
            }
            m_data = new_data;
            m_capacity = new_cap;
        }
    }

private:
    T* m_data;
    std::size_t m_size;
    std::size_t m_capacity;
    Comparator m_comparator;
};

#endif // SET_H