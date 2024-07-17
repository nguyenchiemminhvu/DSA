#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <initializer_list>
#include <vector>
#include <algorithm>

template <typename T>
class BinarySearchTree
{
public:
    struct Node
    {
        T data;
        std::size_t count;
        Node* left;
        Node* right;

        Node(const T& value)
            : data(value)
            , count(1U)
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
        std::vector<T> sorted(L.begin(), L.end());
        std::sort(sorted.begin(), sorted.end());
        m_root = recursive_build_tree(sorted, 0U, sorted.size() - 1U);
        m_size = sorted.size();
    }

    BinarySearchTree(const BinarySearchTree& another)
        : BinarySearchTree()
    {
        if (!another.empty())
        {
            m_root = recursive_clone_tree(m_root, another.m_root);
            m_size = another.m_size;   
        }
    }

    ~BinarySearchTree()
    {
        clear();
    }

    bool operator==(const BinarySearchTree& another)
    {
        return recursive_equal_compare(m_root, another.m_root);
    }

    void swap(BinarySearchTree& another)
    {
        std::swap(m_root, another.m_root);
        std::swap(m_size, another.m_size);
    }

    const Node* get_node(const T& key)
    {
        return get_node_util(m_root, key);
    }

    void insert(const T& key)
    {
        m_root = recursive_insert(m_root, key);
        m_size++;
    }

    bool contain(const T& key)
    {
        return recursive_find(m_root, key);
    }

    void erase(const T& key)
    {
        if (empty())
        {
            throw std::out_of_range("Access empty BST");
        }

        m_size--;
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
        return check_BST_validation(m_root);
    }

private:
    Node* recursive_build_tree(const std::vector<T>& sorted, std::size_t left, std::size_t right)
    {
        if (left > right || right >= sorted.size())
        {
            return nullptr;
        }

        std::size_t mid = left + (right - left) / 2U;

        Node* newNode = new Node(sorted[mid]);
        newNode->left = recursive_build_tree(sorted, left, mid - 1U);
        newNode->right = recursive_build_tree(sorted, mid + 1U, right);
        return newNode;
    }

    Node* recursive_clone_tree(Node* this_node, Node* that_node)
    {
        if (that_node == nullptr)
        {
            if (this_node != nullptr)
            {
                recursive_deallocate(this_node);
                this_node = nullptr;
            }

            return this_node;
        }

        if (this_node == nullptr)
        {
            this_node = new Node(that_node->data);
            this_node->count = that_node->count;
        }
        else
        {
            this_node->data = that_node->data;
            this_node->count = that_node->count;
        }

        this_node->left = recursive_clone_tree(this_node->left, that_node->left);
        this_node->right = recursive_clone_tree(this_node->right, that_node->right);

        return this_node;
    }

    bool recursive_equal_compare(Node* this_node, Node* that_node)
    {
        if (this_node == nullptr && that_node == nullptr)
        {
            return true;
        }

        if ((this_node == nullptr && that_node != nullptr)
        ||  (this_node != nullptr && that_node == nullptr))
        {
            return false;
        }

        if ((this_node->data != that_node->data)
        ||  (this_node->count != that_node->count))
        {
            return false;
        }

        return recursive_equal_compare(this_node->left, that_node->left)
            && recursive_equal_compare(this_node->right, that_node->right);
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

    Node* recursive_insert(Node* cur, const T& key)
    {
        if (cur == nullptr)
        {
            cur = new Node(key);
            return cur;
        }

        if (key < cur->data)
        {
            cur->left = recursive_insert(cur->left, key);
        }
        else if (key > cur->data)
        {
            cur->right = recursive_insert(cur->right, key);
        }
        else
        {
            cur->count++;
        }

        return cur;
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

    const Node* get_node_util(Node* cur, const T& key)
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

    bool check_BST_validation(Node* cur, Node* minNode = nullptr, Node* maxNode = nullptr)
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

        return check_BST_validation(cur->left, minNode, cur)
            && check_BST_validation(cur->right, cur, maxNode);
    }

private:
    Node* m_root;
    std::size_t m_size;
};

#endif // BINARY_SEARCH_TREE_H