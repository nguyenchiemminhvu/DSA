#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <initializer_list>
#include <algorithm>

template <typename T>
class BinarySearchTree
{
public:
    struct Node
    {
        T data;
        Node* left;
        Node* right;

        Node(const T& value)
            : data(value)
            , left(nullptr)
            , right(nullptr)
        {
        }
    };

    BinarySearchTree()
        : m_root(nullptr)
        , m_size(0U)
    {

    }

    BinarySearchTree(const std::initializer_list<T>& L)
        : BinarySearchTree()
    {

    }

    BinarySearchTree(const BinarySearchTree& another)
        : BinarySearchTree()
    {

    }

    ~BinarySearchTree()
    {
        
    }

    void swap(BinarySearchTree& another)
    {

    }

    Node* get_node(const T& key)
    {
        return nullptr;
    }

    void insert(const T& key)
    {

    }

    bool contain(const T& key)
    {

    }

    void erase(const T& key)
    {

    }

    void clear()
    {

    }

    std::size_t size() const
    {
        return m_size;
    }

private:


private:
    Node* m_root;
    std::size_t m_size;
};

#endif // BINARY_SEARCH_TREE_H