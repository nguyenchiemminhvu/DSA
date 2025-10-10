#ifndef STRING_H
#define STRING_H

#include "Vector.h"
#include <iostream>
#include <cstring>
#include <algorithm>
#include <algorithm>

using String = Vector<char>;

template <>
class Vector<char>
{
public:
    using iterator = char*;
    using const_iterator = const char*;

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

    Vector(std::initializer_list<char> L)
        : m_data(nullptr)
        , m_size(0U)
        , m_capacity(0U)
    {
        this->expand(L.size() == 0 ? 1 : L.size() * 2U);
        std::copy(L.begin(), L.end(), m_data);

        m_size = L.size();
    }

    Vector(const Vector<char>& another)
        : m_data(nullptr)
        , m_size(0U)
        , m_capacity(0U)
    {
        this->expand(another.capacity() == 0 ? 1 : another.capacity());
        std::copy(another.m_data, another.m_data + another.m_size, m_data);

        m_size = another.size();
    }

    Vector(const char* str)
        : m_data(nullptr)
        , m_size(0U)
        , m_capacity(0U)
    {
        std::size_t str_len = strlen(str);
        this->expand(str_len == 0 ? 1 : str_len * 2);
        std::copy(str, str + str_len, m_data);

        m_size = str_len;
    }

    Vector(const char* str, std::size_t n)
        : m_data(nullptr)
        , m_size(0U)
        , m_capacity(0U)
    {
        this->expand(n == 0 ? 1 : n * 2);
        std::copy(str, str + n, m_data);

        m_size = n;
    }

    Vector<char>& operator=(const Vector<char>& another)
    {
        if (this == &another)
        {
            return *this;
        }

        this->clear();
        this->expand(another.capacity());
        std::copy(another.m_data, another.m_data + another.m_size, m_data);

        m_size = another.size();
        return *this;
    }

    Vector<char>& operator=(const char* str)
    {
        this->clear();

        std::size_t str_len = strlen(str);
        this->expand(str_len == 0 ? 1 : str_len * 2);
        std::copy(str, str + str_len, m_data);

        m_size = str_len;
        return *this;
    }

    bool operator==(const Vector<char>& another)
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

    void swap(Vector<char>& another)
    {
        std::size_t tempSize = this->m_size;
        this->m_size = another.m_size;
        another.m_size = tempSize;

        std::size_t tempCap = this->m_capacity;
        this->m_capacity = another.m_capacity;
        another.m_capacity = tempCap;

        char* tempData = this->m_data;
        this->m_data = another.m_data;
        another.m_data = tempData;
    }

    void push_back(const char& element)
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

    void insert(std::size_t index, const char& element)
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

    void insert(std::size_t index, const_iterator left, const_iterator right)
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

        for (const_iterator it = left; it != right; ++it)
        {
            m_data[index + (it - left)] = *it;
        }

        m_size = new_size;
    }

    void insert(std::size_t index, const char* str)
    {
        std::size_t str_len = strlen(str);
        this->insert(index, str, str + str_len);
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
        delete[] m_data;
        m_data = nullptr;
        m_size = 0U;
        m_capacity = 0U;
    }

    char& front()
    {
        if (m_size == 0)
        {
            throw std::out_of_range("Index out of range");
        }

        return *(m_data);
    }

    char& back()
    {
        if (m_size == 0)
        {
            throw std::out_of_range("Index out of range");
        }

        return *(m_data + m_size - 1);
    }

    char& operator[](std::size_t index)
    {
        if (index >= m_size)
        {
            throw std::out_of_range("Index out of range");
        }

        return m_data[index];
    }

    const char& operator[](std::size_t index) const
    {
        if (index >= m_size)
        {
            throw std::out_of_range("Index out of range");
        }

        return m_data[index];
    }

    Vector<char>& operator+=(const Vector<char>& nextStr)
    {
        this->insert(this->m_size, nextStr.begin(), nextStr.end());
        return *this;
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

    const_iterator begin() const noexcept
    {
        return m_data;
    }

    iterator end() noexcept
    {
        return m_data + m_size;
    }

    const_iterator end() const noexcept
    {
        return m_data + m_size;
    }

    const char* data() const
    {
        return m_data;
    }

    const char* c_str() const
    {
        return m_data;
    }

private:
    void expand(std::size_t new_cap)
    {
        char* new_data = new char[new_cap];
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
    char* m_data;
    std::size_t m_size;
    std::size_t m_capacity;
};

#endif // STRING_H