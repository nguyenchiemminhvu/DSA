#ifndef UNORDERED_SET_H
#define UNORDERED_SET_H

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <initializer_list>
#include <vector>

#include "./../HashTable/HashTable.h"

template <typename T>
class UnorderedSet
{
public:
    UnorderedSet()
    {
        m_core.clear();
    }

    UnorderedSet(const std::initializer_list<T>& L)
        : UnorderedSet()
    {
        for (const T& key : L)
        {
            m_core.insert(key, false);
        }
    }

    UnorderedSet(const std::vector<T>& V)
    {
        for (const T& key : V)
        {
            m_core.insert(key, false);
        }
    }

    ~UnorderedSet()
    {
        m_core.clear();
    }

private:
    HashTable<T, bool> m_core;
};

#endif // UNORDERED_SET_H