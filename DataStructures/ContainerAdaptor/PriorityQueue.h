#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <initializer_list>
#include <functional>

template <typename T, typename Comparator = std::less<T>>
class PriorityQueue
{
public:
    PriorityQueue()
    {

    }

    PriorityQueue(const std::initializer_list<T>& L)
    {

    }

    PriorityQueue(const PriorityQueue<T>& another)
    {

    }

    ~PriorityQueue()
    {

    }

    void swap(PriorityQueue<T>& another)
    {

    }

    void push(const T& value)
    {

    }

    void pop()
    {

    }

    T& top() const
    {
        
    }

    std::size_t size() const
    {
        return 0U;
    }

    bool empty()
    {
        return true;
    }

private:
    void ensure_capacity()
    {

    }

    void make_heap()
    {

    }

private:
    T* m_data;
    std::size_t m_size;
    std::size_t m_capacity;
    Comparator m_comparator;
};

#endif // PRIORITY_QUEUE_H