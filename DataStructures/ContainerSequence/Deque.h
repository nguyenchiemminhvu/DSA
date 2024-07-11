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

private:
    T* m_data;
    std::size_t m_size;
    std::size_t m_capacity;
    std::size_t m_front_idx;
    std::size_t m_back_idx;
};

#endif // DEQUE_H