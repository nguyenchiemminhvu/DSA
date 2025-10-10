#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <initializer_list>
#include <algorithm>

template <typename T, std::size_t N>
class Array
{
public:
    using iterator = T*;
    using const_iterator = const T*;

    Array() = default;

    Array(std::initializer_list<T> L)
    {
        if (L.size() != N)
        {
            throw std::invalid_argument("Invalid initializer list size");
        }

        std::copy(L.begin(), L.end(), m_data);
    }

    T& operator[](std::size_t index)
    {
        if (index >= N)
        {
            throw std::out_of_range("Index out of range");
        }

        return m_data[index];
    }

    const T& operator[](std::size_t index) const
    {
        if (index >= N)
        {
            throw std::out_of_range("Index out of range");
        }

        return m_data[index];
    }

    constexpr std::size_t size() const noexcept
    {
        return N;
    }

    iterator begin() noexcept
    {
        return m_data;
    }

    iterator end() noexcept
    {
        return m_data + N;
    }

    const_iterator begin() const noexcept
    {
        return m_data;
    }

    const_iterator end() const noexcept
    {
        return m_data + N;
    }

private:
    T m_data[N];
};

#endif // ARRAY_H