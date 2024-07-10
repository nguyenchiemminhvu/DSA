#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <initializer_list>

template <typename T>
class Vector
{
public:
    using iterator = T*;
    using const_iterator = const T*;

    Vector() = default;

private:
    T* m_data;
};

#endif // VECTOR_H