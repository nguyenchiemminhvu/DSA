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

    void swap(UnorderedSet<T>& another)
    {
        m_core.swap(another.m_core);
    }

    void insert(const T& key)
    {
        m_core.insert(key, false);
    }

    bool contain(const T& key)
    {
        return m_core.contain(key);
    }

    void erase(const T& key)
    {
        m_core.remove(key);
    }

    void clear()
    {
        m_core.clear();
    }

    std::size_t size()
    {
        return m_core.size();
    }

    bool empty()
    {
        return m_core.empty();
    }

private:
    HashTable<T, bool> m_core;
};

#endif // UNORDERED_SET_H