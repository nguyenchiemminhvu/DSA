#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <initializer_list>

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

    }

    Deque(const Deque& another)
        : m_data(nullptr)
        , m_size(0U)
        , m_capacity(0U)
        , m_front_idx(0U)
        , m_back_idx(0U)
    {

    }

    Deque(iterator left, iterator right)
        : m_data(nullptr)
        , m_size(0U)
        , m_capacity(0U)
        , m_front_idx(0U)
        , m_back_idx(0U)
    {

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

    }

    T& operator[](const std::size_t index)
    {
        if (index >= m_size)
        {
            throw std::out_of_range("Index out of range");
        }

        return m_data[index];
    }

    void push_back(const T& value)
    {

    }

    void push_front(const T& value)
    {

    }

    void pop_back()
    {

    }

    void pop_front()
    {

    }

    void clear()
    {
        
    }

    T& back()
    {

    }

    const T& back() const
    {

    }

    T& front()
    {

    }

    const T& front() const
    {

    }

    iterator begin()
    {

    }

    const_iterator begin() const
    {

    }

    iterator end()
    {

    }

    const_iterator end() const
    {

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
    void shrink()
    {

    }

private:
    T* m_data;
    std::size_t m_size;
    std::size_t m_capacity;
    std::size_t m_front_idx;
    std::size_t m_back_idx;
};

#endif // DEQUE_H