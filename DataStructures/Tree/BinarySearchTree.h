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
        clear();
    }

    void swap(BinarySearchTree& another)
    {
        std::swap(m_root, another.m_root);
    }

    Node* get_node(const T& key)
    {
        return get_node_util(m_root, key);
    }

    void insert(const T& key)
    {

    }

    bool contain(const T& key)
    {
        return recursive_find(m_root, key);
    }

    void erase(const T& key)
    {

    }

    void clear()
    {
        recursive_deallocate(m_root);
        m_root = nullptr;
    }

    std::vector<T> traversal()
    {
        std::vector<T> elements;
        recursive_traversal(m_root, elements);
        return elements;
    }

    std::size_t size() const
    {
        return m_size;
    }

private:
    void recursive_traversal(Node* cur, std::vector<T>& elements)
    {
        if (cur != nullptr)
        {
            recursive_traversal(cur->left, elements);
            elements.push_back(cur->data);
            recursive_traversal(cur->right, elements);
        }
    }

    void recursive_deallocate(Node* cur)
    {
        if (cur == nullptr)
        {
            return;
        }

        recursive_deallocate(cur->left);
        recursive_deallocate(cur->right);

        delete cur;
    }

    bool recursive_find(Node* cur, const T& key)
    {
        if (cur == nullptr)
        {
            return false;
        }

        if (key == cur->data)
        {
            return true;
        }
        
        if (key < cur->data)
        {
            return recursive_find(cur->left, key);
        }
        else
        {
            return recursive_find(cur->right, key);
        }
    }

    Node* get_node_util(Node* cur, const T& key)
    {
        if (cur == nullptr)
        {
            return nullptr;
        }

        if (key == cur->data)
        {
            return cur;
        }

        if (key < cur->data)
        {
            return get_node_util(cur->left, key);
        }
        else
        {
            return get_node_util(cur->right, key);
        }
    }

private:
    Node* m_root;
    std::size_t m_size;
};

#endif // BINARY_SEARCH_TREE_H