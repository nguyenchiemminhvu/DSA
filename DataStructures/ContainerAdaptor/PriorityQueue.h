#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <initializer_list>
#include <functional>
#include <algorithm>

/**
 * Default is min heap
 * Use std::greater comparator for max heap
*/
template <typename T, typename Comparator = std::less<T>>
class PriorityQueue
{
public:
    PriorityQueue()
        : m_data(nullptr)
        , m_size(0U)
        , m_capacity(0U)
    {
    }

    PriorityQueue(const std::initializer_list<T>& L)
        : m_data(nullptr)
        , m_size(0U)
        , m_capacity(0U)
    {
        m_size = L.size();
        m_capacity = L.size() * 2U;
        m_data = new T[m_capacity];
        std::copy(L.begin(), L.end(), m_data);

        make_heap();
    }

    PriorityQueue(const PriorityQueue<T, Comparator>& another)
        : m_data(nullptr)
        , m_size(0U)
        , m_capacity(0U)
    {
        m_size = another.m_size;
        m_capacity = another.m_capacity;
        m_data = new T[m_capacity];
        std::copy(another.m_data, another.m_data + m_size, m_data);
        m_comparator = another.m_comparator;
    }

    ~PriorityQueue()
    {
        if (m_data != nullptr)
        {
            delete[] m_data;
            m_data = nullptr;
        }
    }

    void swap(PriorityQueue<T, Comparator>& another)
    {
        std::swap(m_data, another.m_data);
        std::swap(m_size, another.m_size);
        std::swap(m_capacity, another.m_capacity);
        std::swap(m_comparator, another.m_comparator);
    }

    void push(const T& value)
    {
        ensure_capacity();
        m_data[m_size++] = value;

        // heapify up
        std::size_t current = m_size - 1U;
        while (current > 0U)
        {
            std::size_t parent = (current - 1U) / 2U;
            if (m_comparator(m_data[current], m_data[parent]))
            {
                std::swap(m_data[current], m_data[parent]);
                current = parent;
            }
            else
            {
                break;
            }
        }
    }

    void pop()
    {
        if (empty())
        {
            throw std::out_of_range("Access empty priority queue");
        }

        m_data[0U] = m_data[--m_size];

        // heapify down
        std::size_t current = 0U;
        while (true)
        {
            std::size_t leftIdx = current * 2U + 1U;
            std::size_t rightIdx = current * 2U + 2U;
            std::size_t pivotIdx = current;

            if (leftIdx < m_size && m_comparator(m_data[leftIdx], m_data[pivotIdx]))
            {
                pivotIdx = leftIdx;
            }

            if (rightIdx < m_size && m_comparator(m_data[rightIdx], m_data[pivotIdx]))
            {
                pivotIdx = rightIdx;
            }

            if (pivotIdx == current)
            {
                break;
            }
            else
            {
                std::swap(m_data[current], m_data[pivotIdx]);
                current = pivotIdx;
            }
        }
    }

    const T& top() const
    {
        if (empty())
        {
            throw std::out_of_range("Access empty priority queue");
        }

        return m_data[0U];
    }

    std::size_t size() const
    {
        return m_size;
    }

    bool empty() const
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

    void make_heap()
    {
        for (std::size_t i = m_size / 2U; i-- > 0U;)
        {
            heapify(i);
        }
    }

    void heapify(std::size_t idx)
    {
        std::size_t leftIdx = idx * 2U + 1U;
        std::size_t rightIdx = idx * 2U + 2U;
        std::size_t pivotIdx = idx;

        if (leftIdx < m_size && m_comparator(m_data[leftIdx], m_data[pivotIdx]))
        {
            pivotIdx = leftIdx;
        }

        if (rightIdx < m_size && m_comparator(m_data[rightIdx], m_data[pivotIdx]))
        {
            pivotIdx = rightIdx;
        }

        if (pivotIdx != idx)
        {
            std::swap(m_data[idx], m_data[pivotIdx]);
            heapify(pivotIdx);
        }
    }

private:
    T* m_data;
    std::size_t m_size;
    std::size_t m_capacity;
    Comparator m_comparator;
};

#endif // PRIORITY_QUEUE_H