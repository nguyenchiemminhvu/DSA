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
        for (const T& key : L)
        {
            insert(key);
        }
    }

    BinarySearchTree(const BinarySearchTree<T>& another)
        : BinarySearchTree()
    {
        if (another.m_root != nullptr)
        {
            m_root = recursive_clone_tree(m_root, another.m_root);
            m_size = another.m_size;
        }
    }

    BinarySearchTree<T>& operator=(const std::initializer_list<T>& L)
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

    BinarySearchTree<T>& operator=(const BinarySearchTree<T>& another)
    {
        if (m_root != nullptr)
        {
            clear();
        }

        if (another.m_root != nullptr)
        {
            m_root = recursive_clone_tree(m_root, another.m_root);
            m_size = another.m_size;
        }

        return *this;
    }

    ~BinarySearchTree()
    {
        clear();
    }

    bool operator==(const BinarySearchTree<T>& another)
    {
        return recursive_equal_compare(m_root, another.m_root);
    }

    bool is_same_set(const BinarySearchTree<T>& another)
    {
        std::vector<std::pair<T, std::size_t>> this_elements;
        recursive_traversal(m_root, this_elements);

        std::vector<std::pair<T, std::size_t>> that_elements;
        recursive_traversal(another.m_root, that_elements);

        bool res = true;
        if (this_elements.size() != that_elements.size())
        {
            res = false;
        }
        else
        {
            for (int i = 0; i < this_elements.size(); i++)
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

    void swap(BinarySearchTree<T>& another)
    {
        std::swap(m_root, another.m_root);
        std::swap(m_size, another.m_size);
    }

    void insert(const T& key)
    {
        m_root = recursive_insert(m_root, key);
        m_size++;
    }

    bool contain(const T& key)
    {
        return recursive_contain(m_root, key);
    }

    Node* get_node(const T& key)
    {
        return recursive_find_node(m_root, key);
    }

    void erase(const T& key)
    {
        m_root = recursive_erase(m_root, key);
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

    std::size_t height()
    {
        return get_height(m_root);
    }

    bool is_valid()
    {
        return check_bst_validity(m_root);
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

    Node* recursive_find_node(Node* cur, const T& key)
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

    Node* recursive_erase(Node* cur, const T& key)
    {
        if (cur == nullptr)
        {
            return nullptr;
        }

        if (key < cur->data)
        {
            cur->left = recursive_erase(cur->left, key);
        }
        else if (key > cur->data)
        {
            cur->right = recursive_erase(cur->right, key);
        }
        else
        {
            if (cur->left == nullptr)
            {
                m_size -= cur->count;
                Node* temp = cur->right;
                delete cur;
                return temp;
            }
            else if (cur->right == nullptr)
            {
                m_size -= cur->count;
                Node* temp = cur->left;
                delete cur;
                return temp;
            }
            else
            {
                Node* min_of_right_node = get_min_node(cur->right);
                cur->data = min_of_right_node->data;
                cur->count = min_of_right_node->count;
                cur->right = recursive_erase(cur->right, min_of_right_node->data);
            }
        }

        return cur;
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

    std::size_t get_height(Node* cur)
    {
        if (cur == nullptr)
        {
            return 0U;
        }

        return 1 + std::max(get_height(cur->left), get_height(cur->right));
    }

private:
    Node* m_root;
    std::size_t m_size;
};

#endif // BINARY_SEARCH_TREE_H