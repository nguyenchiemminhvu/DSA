#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <initializer_list>
#include <vector>
#include <algorithm>

#include "./../Tree/AVLTree.h"

template <typename TK, typename TV>
class Map
{
public:
    Map()
    {
        m_core.clear();
    }

    Map(const Map<TK, TV>& another)
        : Map()
    {
        m_core = another.m_core;
    }

    Map<TK, TV>& operator=(const Map<TK, TV>& another)
    {
        m_core.clear();
        m_core = another.m_core;
        return *this;
    }

    ~Map()
    {
        m_core.clear();
    }

    void swap(Map<TK, TV>& another)
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

    void erase(const TK& key)
    {
        m_core.erase(key);
    }

    void clear()
    {
        m_core.clear();
    }

    TV& at(const TK& key)
    {
        return m_core.at(key);
    }

    TV& operator[](const TK& key)
    {
        return m_core[key];
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
    AVLMap<TK, TV> m_core;
};

#endif