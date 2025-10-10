#ifndef SET_H
#define SET_H

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <initializer_list>
#include <vector>
#include <algorithm>

#include "./../Tree/AVLTree.h"

template <typename T>
class Set
{
public:
    Set()
    {
        m_core.clear();
    }

    Set(const std::initializer_list<T>& L)
        : Set()
    {
        for (const T& key : L)
        {
            m_core.insert(key);
        }
    }

    Set(const std::vector<T>& V)
        : Set()
    {
        for (const T& key : V)
        {
            m_core.insert(key);
        }
    }
    
    Set(const Set<T>& another)
        : Set()
    {
        m_core = another.m_core;
    }

    ~Set()
    {
        m_core.clear();
    }

    void swap(Set<T>& another)
    {
        m_core.swap(another.m_core);
    }

    void insert(const T& key)
    {
        m_core.insert(key);
    }

    void erase(const T& key)
    {
        m_core.erase(key);
    }

    void clear()
    {
        m_core.clear();
    }

    bool contain(const T& key)
    {
        return m_core.contain(key);
    }

    std::size_t count(const T& key)
    {
        return m_core.count(key);
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
    AVLTree<T> m_core;
};

#endif // SET_H