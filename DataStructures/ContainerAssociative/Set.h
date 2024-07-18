#ifndef SET_H
#define SET_H

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <initializer_list>
#include <vector>
#include <algorithm>

template <typename T>
class Set
{
public:
    Set()
    {
    }

    Set(const std::initializer_list<T>& L)
        : Set()
    {
    }

    Set(const std::vector<T>& V)
        : Set()
    {
    }
    
    Set(const Set<T>& another)
        : Set()
    {
    }

    ~Set()
    {
    }

    void swap(Set<T>& another)
    {
    }

    void insert(const T& key)
    {
    }

    void erase(const T& key)
    {
        
    }

    void clear()
    {
    }

    bool contain(const T& key)
    {

    }

    std::size_t count(const T& key)
    {
        return 0U;
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
    // core AVL tree implementation


private:
    
};

#endif // SET_H