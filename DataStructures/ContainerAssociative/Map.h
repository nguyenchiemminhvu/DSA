#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <initializer_list>
#include <vector>
#include <algorithm>

template <typename TK, typename TV>
class Map
{
public:
    Map()
    {

    }

    Map(const Map<TK, TV>& another)
    {

    }

    Map<TK, TV>& operator=(const Map<TK, TV>& another)
    {
        return *this;
    }

    ~Map()
    {

    }

    void swap(Map<TK, TV>& another)
    {

    }

    void insert(const TK& key, const TV& value)
    {

    }

    bool contain(const TK& key)
    {
        return false;
    }

    void erase(const TK& key)
    {

    }

    void clear()
    {

    }

    TV& at(const TK& key)
    {
        return TV();
    }

    TV& operator[](const TK& key)
    {
        return TV();
    }

    std::size_t size()
    {
        return 0U;
    }

    bool empty()
    {
        return true;
    }

    std::vector<std::pair<TK, TV>> traversal()
    {
        return {};
    }

private:

};

#endif