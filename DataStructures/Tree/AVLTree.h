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
            , count(1U)
            , height(0U)
            , left(nullptr)
            , right(nullptr)
        {
        }
    };

    AVLTree()
        : m_root(nullptr)
        , m_size(0U)
    {

    }

    AVLTree(const std::initializer_list<T>& L)
        : AVLTree()
    {
        for (const T& key : L)
        {
            insert(key);
        }
    }

    AVLTree(const AVLTree<T>& another)
        : AVLTree()
    {
        if (!another.empty())
        {
            m_root = recursive_clone_tree(m_root, another.m_root);
            m_size = another.m_size;
        }
    }

    AVLTree<T>& operator=(const std::initializer_list<T>& L)
    {
        if (m_root != nullptr)
        {
            clear();
        }

        for (const T& key : L)
        {
            insert(key);
        }

        return *this;
    }

    AVLTree<T>& operator=(const AVLTree<T>& another)
    {
        if (m_root != nullptr)
        {
            clear();
        }

        if (!another.empty())
        {
            m_root = recursive_clone_tree(m_root, another.m_root);
            m_size = another.m_size;
        }

        return *this;
    }

    ~AVLTree()
    {
        clear();
    }

    bool operator==(const AVLTree<T>& another)
    {
        return recursive_equal_compare(m_root, another.m_root);
    }

    bool is_same_set(const AVLTree<T>& another)
    {
        std::vector<std::pair<T, std::size_t>> this_elements = traversal(m_root);
        std::vector<std::pair<T, std::size_t>> that_elements = another.traversal();

        bool res = true;
        if (this_elements.size() != that_elements.size())
        {
            res = false;
        }
        else
        {
            for (std::size_t i = 0U; i < this_elements.size(); i++)
            {
                if ((this_elements[i].first != that_elements[i].first)
                ||  (this_elements[i].second != that_elements[i].second))
                {
                    res = false;
                    break;
                }
            }
        }

        return res;
    }

    void swap(AVLTree<T>& another)
    {
        std::swap(m_root, another.m_root);
        std::swap(m_size, another.m_size);
    }

    void insert(const T& key)
    {

    }

    bool contain(const T& key)
    {
        return recursive_contain(m_root, key);
    }

    const Node* get_node(const T& key)
    {
        return recursive_find_node(m_root, key);
    }

    void erase(const T& key)
    {

    }

    void clear()
    {
        recursive_deallocate(m_root);
        m_root = nullptr;
        m_size = 0U;
    }

    std::vector<std::pair<T, std::size_t>> traversal()
    {
        std::vector<std::pair<T, std::size_t>> elements;
        recursive_traversal(m_root, elements);
        return elements;
    }

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

    Node* get_lowest_common_ancestor(const T& key1, const T& key2)
    {
        Node* common = nullptr;

        if (contain(key1) && contain(key2))
        {
            common = get_lowest_common_ancestor(m_root, key1, key2);
        }

        return common;
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
    Node* recursive_build_tree(const std::vector<T>& sorted, std::size_t left, std::size_t right)
    {
        return nullptr;
    }

    Node* recursive_clone_tree(Node* this_node, Node* that_node)
    {
        return nullptr;
    }

    bool recursive_equal_compare(Node* this_node, Node* that_node)
    {
        return false;
    }

    bool recursive_contain(Node* cur, const T& key)
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
            return recursive_contain(cur->left, key);
        }
        else
        {
            return recursive_contain(cur->right, key);
        }
    }

    const Node* recursive_find_node(Node* cur, const T& key)
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
            return recursive_find_node(cur->left, key);
        }
        else
        {
            return recursive_find_node(cur->right, key);
        }
    }

    void recursive_traversal(Node* cur, std::vector<std::pair<T, std::size_t>>& elements)
    {
        if (cur != nullptr)
        {
            recursive_traversal(cur->left, elements);
            elements.push_back({cur->data, cur->count});
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

    Node* get_lowest_common_ancestor(Node* cur, const T& key1, const T& key2)
    {
        if (cur == nullptr)
        {
            return nullptr;
        }

        if (key1 < cur->data && key2 < cur->data)
        {
            return get_lowest_common_ancestor(cur->left, key1, key2);
        }

        if (key1 > cur->data && key2 > cur->data)
        {
            return get_lowest_common_ancestor(cur->right, key1, key2);
        }

        return cur;
    }

private:
    Node* m_root;
    std::size_t m_size;
};

#endif // AVL_TREE_H