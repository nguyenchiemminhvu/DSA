#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <initializer_list>
#include <algorithm>

template <typename T>
class Vector
{
public:
    using iterator = T*;
    using const_iterator = const T*;

    Vector()
        : m_data(nullptr)
        , m_size(0U)
        , m_capacity(0U)
    {

    }

    ~Vector()
    {
        if (m_data != nullptr)
        {
            delete[] m_data;
        }
    }

    Vector(std::initializer_list<T> L)
        : m_data(nullptr)
        , m_size(0U)
        , m_capacity(0U)
    {
        this->expand(L.size() * 2U);
        std::copy(L.begin(), L.end(), m_data);

        m_size = L.size();
    }

    Vector(iterator left, iterator right)
        : m_data(nullptr)
        , m_size(0U)
        , m_capacity(0U)
    {
        std::size_t dist = (right - left);
        this->expand(dist == 0 ? 1 : dist * 2);

        for (iterator it = left; it <= right; it++)
        {
            m_data[it - left] = *it;
        }

        m_size = dist;
    }

    Vector(const_iterator left, const_iterator right)
        : m_data(nullptr)
        , m_size(0U)
        , m_capacity(0U)
    {
        std::size_t dist = (right - left);
        this->expand(dist == 0 ? 1 : dist * 2);

        for (iterator it = left; it <= right; it++)
        {
            m_data[it - left] = *it;
        }

        m_size = dist;
    }

    Vector(const Vector<T>& another)
        : m_data(nullptr)
        , m_size(0U)
        , m_capacity(0U)
    {
        if (another.m_data != nullptr)
        {
            this->expand(another.capacity());
            std::copy(another.m_data, another.m_data + another.m_size, m_data);
        }

        m_size = another.m_size;
    }

    Vector<T>& operator=(const Vector<T>& another)
    {
        if (this == &another)
        {
            return *this;
        }

        this->clear();
        if (another.m_data != nullptr)
        {
            this->expand(another.capacity());
            std::copy(another.m_data, another.m_data + another.m_size, m_data);
            m_size = another.m_size;
        }
        return *this;
    }

    bool operator==(const Vector<T>& another)
    {
        bool equal = true;
        if (m_size != another.m_size)
        {
            equal = false;
        }
        else
        {
            for (std::size_t i = 0U; i < m_size; i++)
            {
                if (m_data[i] != another[i])
                {
                    equal = false;
                    break;
                }
            }
        }
        return equal;
    }

    void swap(Vector<T>& another)
    {
        std::size_t tempSize = this->m_size;
        this->m_size = another.m_size;
        another.m_size = tempSize;

        std::size_t tempCap = this->m_capacity;
        this->m_capacity = another.m_capacity;
        another.m_capacity = tempCap;

        T* tempData = this->m_data;
        this->m_data = another.m_data;
        another.m_data = tempData;
    }

    void push_back(const T& element)
    {
        if (m_size == m_capacity)
        {
            this->expand(m_capacity == 0U ? 1U : m_capacity * 2U);
        }

        m_data[m_size] = element;
        m_size++;
    }

    void pop_back()
    {
        if (m_size > 0U)
        {
            m_size--;
            if (m_size == 0U)
            {
                this->clear();
            }
        }
    }

    void insert(std::size_t index, const T& element)
    {
        if (index > m_size)
        {
            throw std::out_of_range("Index out of range");
        }

        if (m_size == m_capacity)
        {
            this->expand(m_capacity == 0U ? 1U : m_capacity * 2U);
        }

        for (std::size_t i = m_size; i > index; i--)
        {
            m_data[i] = m_data[i - 1U];
        }

        m_data[index] = element;
        m_size++;
    }

    void insert(std::size_t index, iterator left, iterator right)
    {
        if (index > m_size)
        {
            throw std::out_of_range("Index out of range");
        }

        std::size_t num_elements = right - left;
        std::size_t new_size = m_size + num_elements;
        if (new_size > m_capacity)
        {
            this->expand(new_size * 2);
        }

        for (std::size_t i = m_size + num_elements - 1; i >= index + num_elements; --i)
        {
            m_data[i] = m_data[i - num_elements];
        }

        for (iterator it = left; it != right; ++it)
        {
            m_data[index + (it - left)] = *it;
        }

        m_size = new_size;
    }

    void erase(std::size_t index)
    {
        if (index >= m_size)
        {
            throw std::out_of_range("Index out of range");
        }

        for (std::size_t i = index; i < m_size - 1U; i++)
        {
            m_data[i] = m_data[i + 1];
        }

        m_size--;
        if (m_size == 0U)
        {
            this->clear();
        }
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
    }

    T& front()
    {
        if (m_size == 0)
        {
            throw std::out_of_range("Index out of range");
        }

        return *(m_data);
    }

    T& back()
    {
        if (m_size == 0)
        {
            throw std::out_of_range("Index out of range");
        }

        return *(m_data + m_size - 1);
    }

    T& operator[](std::size_t index)
    {
        if (index >= m_size)
        {
            throw std::out_of_range("Index out of range");
        }

        return m_data[index];
    }

    const T& operator[](std::size_t index) const
    {
        if (index >= m_size)
        {
            throw std::out_of_range("Index out of range");
        }

        return m_data[index];
    }

    constexpr std::size_t size() const noexcept
    {
        return m_size;
    }

    bool empty() const
    {
        return m_size == 0U;
    }

    constexpr std::size_t capacity() const noexcept
    {
        return m_capacity;
    }

    iterator begin() noexcept
    {
        return m_data;
    }

    iterator end() noexcept
    {
        return m_data + m_size;
    }

    T* data() const
    {
        return m_data;
    }

private:
    void expand(std::size_t new_cap)
    {
        T* new_data = new T[new_cap];
        std::fill(new_data, new_data + new_cap, 0);
        for (std::size_t i = 0U; i < m_size; i++)
        {
            new_data[i] = m_data[i];
        }

        if (m_data != nullptr)
        {
            delete[] m_data;
        }

        m_data = new_data;
        m_capacity = new_cap;
    }

private:
    T* m_data;
    std::size_t m_size;
    std::size_t m_capacity;
};

#endif // VECTOR_H