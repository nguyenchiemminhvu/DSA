#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <initializer_list>

template <typename T>
class Stack
{
public:
    Stack()
        : m_data(nullptr)
        , m_size(0U)
        , m_capacity(0U)
        , m_front_idx(0U)
        , m_back_idx(0U)
    {

    }

    ~Stack()
    {
        if (m_data != nullptr)
        {
            delete[] m_data;
        }
    }

    void swap(Stack<T>& another)
    {
        std::swap(m_data, another.m_data);
        std::swap(m_size, another.m_size);
        std::swap(m_capacity, another.m_capacity);
        std::swap(m_front_idx, another.m_front_idx);
        std::swap(m_back_idx, another.m_back_idx);
    }

    void push(const T& value)
    {
        ensure_capacity();

        m_back_idx = (m_back_idx + 1U) % m_capacity;
        m_data[m_back_idx] = value;
        m_size++;
    }

    void pop()
    {
        if (empty())
        {
            throw std::out_of_range("Access empty stack");
        }

        m_back_idx = (m_back_idx + m_capacity - 1U) % m_capacity;
        m_size--;
    }

    T& top()
    {
        if (empty())
        {
            throw std::out_of_range("Access empty stack");
        }

        return m_data[m_back_idx];
    }

    std::size_t size() const
    {
        return m_size;
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
            for (std::size_t i = 0U; i < m_size; i++)
            {
                new_data[i] = m_data[(m_front_idx + i) % m_capacity];
            }

            if (m_data != nullptr)
            {
                delete[] m_data;
            }

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

#endif // STACK_H