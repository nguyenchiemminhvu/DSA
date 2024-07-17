#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <initializer_list>
#include <vector>
#include <algorithm>

template <typename T>
class AVLTree
{
public:
    struct Node
    {
        T data;
        std::size_t count;
        std::size_t height;
        Node* left;
        Node* right;

        Node(const T& value)
            : data(value)
            , height(0U)
            , left(nullptr)
            , right(nullptr)
        {
        }
    };

    Node* get_root()
    {
        return m_root;
    }

    Node* get_min_node()
    {
        return get_min_node(m_root);
    }

    Node* get_max_node()
    {
        return get_max_node(m_root);
    }

    std::size_t size() const
    {
        return m_size;
    }

    bool empty()
    {
        return m_size == 0U;
    }

    bool is_valid()
    {
        return check_bst_validity(m_root);
    }

private:
    Node* get_min_node(Node* cur)
    {
        if (cur == nullptr)
        {
            return nullptr;
        }

        while (cur->left != nullptr)
        {
            cur = cur->left;
        }

        return cur;
    }

    Node* get_max_node(Node* cur)
    {
        if (cur == nullptr)
        {
            return nullptr;
        }

        while (cur->right != nullptr)
        {
            cur = cur->right;
        }

        return cur;
    }

    bool check_bst_validity(Node* cur, Node* minNode = nullptr, Node* maxNode = nullptr)
    {
        if (cur == nullptr)
        {
            return true;
        }

        if ((minNode != nullptr && cur->data <= minNode->data)
        ||  (maxNode != nullptr && cur->data >= maxNode->data))
        {
            return false;
        }

        return check_bst_validity(cur->left, minNode, cur)
            && check_bst_validity(cur->right, cur, maxNode);
    }

private:
    Node* m_root;
    std::size_t m_size;
};

#endif // AVL_TREE_H