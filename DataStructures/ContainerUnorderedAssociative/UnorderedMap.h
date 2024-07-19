#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <initializer_list>
#include <vector>

#include "./../HashTable/HashTable.h"

template <typename TK, typename TV>
class UnorderedMap
{
public:
    UnorderedMap()
    {
        m_core.clear();      
    }

    ~UnorderedMap()
    {
        m_core.clear();
    }

    void swap(UnorderedMap<TK, TV>& another)
    {
        m_core.swap(another.m_core);
    }

    void insert(const TK& key, const TV& value)
    {
        m_core.insert(key, value);
    }

    bool contain(const TK& key)
    {
        return m_core.contain(key);
    }

    TV& at(const TK& key)
    {
        return m_core.retrieve(key);
    }

    TV& operator[](const TK& key)
    {
        if (!m_core.contain(key))
        {
            m_core.insert(key, TV());
        }

        return m_core.retrieve(key);
    }

    void erase(const TK& key)
    {
        m_core.remove(key);
    }

    void clear()
    {
        m_core.clear();
    }

    std::size_t size() const
    {
        return m_core.size();
    }

    bool empty()
    {
        return m_core.empty();
    }

private:
    HashTable<TK, TV> m_core;
};

#endif // UNORDERED_MAP_H