#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <initializer_list>
#include <vector>
#include <string>
#include <cmath>
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
        , m_size_set(0U)
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
        if (another.m_root != nullptr)
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

        if (another.m_root != nullptr)
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
        std::swap(m_size_set, another.m_size_set);
    }

    void insert(const T& key)
    {
        m_root = recursive_insert(m_root, key);
    }

    bool contain(const T& key)
    {
        return recursive_contain(m_root, key);
    }

    std::size_t count(const T& key)
    {
        Node* find_node = recursive_find_node(m_root, key);
        if (find_node == nullptr)
        {
            return 0U;
        }
        else
        {
            return find_node->count;
        }
    }

    Node* get_node(const T& key)
    {
        return recursive_find_node(m_root, key);
    }

    void erase(const T& key)
    {
        m_root = recursive_erase(m_root, key);
        if (empty())
        {
            clear();
        }
    }

    void clear()
    {
        recursive_deallocate(m_root);
        m_root = nullptr;
        m_size = 0U;
        m_size_set = 0U;
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

    std::size_t size_set() const
    {
        return m_size_set;
    }

    bool empty()
    {
        return m_size == 0U;
    }

    std::size_t height()
    {
        if (empty())
        {
            return 0U;
        }

        return get_height(m_root);
    }

    bool is_valid()
    {
        return check_bst_validity(m_root);
    }

    void printTree()
    {
        if (!empty())
        {
            recursive_print_tree(m_root, 0);
        }
    }

private:
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
            m_size++;
            m_size_set++;
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
            m_size++;
            cur->count++;
            return cur;
        }

        // backtrack balancing
        cur->height = std::max(get_height(cur->left), get_height(cur->right)) + 1U;
        int balance = get_balance_factor(cur);

        // left left case
        if (balance > 1 && key < cur->left->data)
        {
            return rotate_right(cur);
        }

        // left right case
        if (balance > 1 && key > cur->left->data)
        {
            cur->left = rotate_left(cur->left); // make it left left case
            return rotate_right(cur);
        }

        // right right case
        if (balance < -1 && key > cur->right->data)
        {
            return rotate_left(cur);
        }

        // right left case
        if (balance < -1 && key < cur->right->data)
        {
            cur->right = rotate_right(cur->right); // make it right right case
            return rotate_left(cur);
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
                m_size_set--;
                Node* temp = cur->right;
                delete cur;
                return temp;
            }
            else if (cur->right == nullptr)
            {
                m_size -= cur->count;
                m_size_set--;
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
                return cur;
            }
        }

        // backtrack balancing
        cur->height = std::max(get_height(cur->left), get_height(cur->right)) + 1U;
        int balance = get_balance_factor(cur);
        int balance_left = get_balance_factor(cur->left);
        int balance_right = get_balance_factor(cur->right);

        // left left case
        if (balance > 1 && balance_left >= 0)
        {
            return rotate_right(cur);
        }

        // left right case
        if (balance > 1 && balance_left < 0)
        {
            cur->left = rotate_left(cur->left); // make it left left case
            return rotate_right(cur);
        }

        // right right case
        if (balance < -1 && balance_right <= 0)
        {
            return rotate_left(cur);
        }

        // right left case
        if (balance < -1 && balance_right > 0)
        {
            cur->right = rotate_right(cur->right); // make it right right case
            return rotate_left(cur);
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

    // use for node that has balance factor > 0
    Node* rotate_right(Node* cur)
    {
        if (cur == nullptr)
        {
            return nullptr;
        }

        Node* cur_left = cur->left;
        Node* cur_left_right = cur_left->right;

        cur_left->right = cur;
        cur->left = cur_left_right;

        cur->height = std::max(get_height(cur->left), get_height(cur->right)) + 1U;
        cur_left->height = std::max(get_height(cur_left->left), get_height(cur_left->right)) + 1U;

        return cur_left;
    }

    // use for node that has balance factor < 0
    Node* rotate_left(Node* cur)
    {
        if (cur == nullptr)
        {
            return nullptr;
        }

        Node* cur_right = cur->right;
        Node* cur_right_left = cur_right->left;

        cur_right->left = cur;
        cur->right = cur_right_left;

        cur->height = std::max(get_height(cur->left), get_height(cur->right)) + 1U;
        cur_right->height = std::max(get_height(cur_right->left), get_height(cur_right->right)) + 1U;

        return cur_right;
    }

    std::size_t get_height(Node* cur)
    {
        if (cur == nullptr)
        {
            return 0U;
        }

        return cur->height;
    }

    int get_balance_factor(Node* cur)
    {
        if (cur == nullptr)
        {
            return 0;
        }

        return static_cast<int>(get_height(cur->left))
             - static_cast<int>(get_height(cur->right));
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

    void recursive_print_tree(Node* cur, int space)
    {
        // Base case
        if (cur == nullptr)
            return;
    
        // Increase distance between levels
        static constexpr int COUNT = 10;
        space += COUNT;
    
        // Process right child first
        recursive_print_tree(cur->right, space);
    
        // Print current node after space
        // count
        std::cout << std::endl;
        for (int i = COUNT; i < space; i++)
            std::cout << " ";
        std::cout << cur->data << "\n";
    
        // Process left child
        recursive_print_tree(cur->left, space);
    }

private:
    Node* m_root;
    std::size_t m_size;
    std::size_t m_size_set;
};


template <typename TK, typename TV>
class AVLMap
{
public:
    struct Node
    {
        TK key;
        TV value;
        std::size_t height;
        Node* left;
        Node* right;

        Node(const TK& k, const TV& v)
            : key(k)
            , value(v)
            , height(0U)
            , left(nullptr)
            , right(nullptr)
        {
        }
    };

    AVLMap()
        : m_root(nullptr)
        , m_size(0U)
    {
    }

    AVLMap(const AVLMap<TK, TV>& another)
        : AVLMap()
    {
        m_root = recursive_clone_tree(m_root, another.m_root);
        m_size = another.m_size;
    }

    AVLMap<TK, TV>& operator=(const AVLMap<TK, TV>& another)
    {
        if (m_root != nullptr)
        {
            clear();
        }

        m_root = recursive_clone_tree(m_root, another.m_root);
        m_size = another.m_size;

        return *this;
    }

    ~AVLMap()
    {
        clear();
    }

    bool operator==(const AVLMap<TK, TV>& another)
    {
        return recursive_equal_compare(m_root, another.m_root);
    }

    void swap(AVLMap<TK, TV>& another)
    {
        std::swap(m_root, another.m_root);
        std::swap(m_size, another.m_size);
    }

    void insert(const TK& key, const TV& value)
    {
        m_root = recursive_insert(m_root, key, value);
    }

    bool contain(const TK& key)
    {
        return recursive_contain(m_root, key);
    }

    Node* get_node(const TK& key)
    {
        return recursive_find_node(m_root, key);
    }

    TV& at(const TK& key)
    {
        Node* find_node = recursive_find_node(m_root, key);
        if (find_node == nullptr)
        {
            throw std::out_of_range("Key is not found");
        }
        return find_node->value;
    }

    TV& operator[](const TK& key)
    {
        Node* find_node = recursive_find_node(m_root, key);
        if (find_node == nullptr)
        {
            insert(key, TV());
            find_node = recursive_find_node(m_root, key);
        }
        return find_node->value;
    }

    void erase(const TK& key)
    {
        m_root = recursive_erase(m_root, key);
    }

    void clear()
    {
        recursive_deallocate(m_root);
        m_root = nullptr;
        m_size = 0U;
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
            this_node = new Node(that_node->key, that_node->value);
        }
        else
        {
            this_node->key = that_node->key;
            this_node->value = that_node->value;
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

        if ((this_node->key != that_node->key)
        ||  (this_node->value != that_node->value))
        {
            return false;
        }

        return recursive_equal_compare(this_node->left, that_node->left)
            && recursive_equal_compare(this_node->right, that_node->right);
    }

    Node* recursive_insert(Node* cur, const TK& key, const TV& value)
    {
        if (cur == nullptr)
        {
            m_size++;
            cur = new Node(key, value);
            return cur;
        }

        if (key < cur->key)
        {
            cur->left = recursive_insert(cur->left, key, value);
        }
        else if (key > cur->key)
        {
            cur->right = recursive_insert(cur->right, key, value);
        }
        else
        {
            return cur;
        }

        // backtracking balancing
        cur->height = std::max(get_height(cur->left), get_height(cur->right)) + 1U;
        int balance = get_balance_factor(cur);

        // left left case
        if (balance > 1 && key < cur->left->key)
        {
            return rotate_right(cur);
        }

        // left right case
        if (balance > 1 && key > cur->left->key)
        {
            cur->left = rotate_left(cur->left); // make it left left case
            return rotate_right(cur);
        }

        // right right case
        if (balance < -1 && key > cur->right->key)
        {
            return rotate_left(cur);
        }

        // right left case
        if (balance < -1 && key < cur->right->key)
        {
            cur->right = rotate_right(cur->right); // make it right right case
            return rotate_left(cur);
        }

        return cur;
    }

    bool recursive_contain(Node* cur, const TK& key)
    {
        if (cur == nullptr)
        {
            return false;
        }

        if (key == cur->key)
        {
            return true;
        }

        if (key < cur->key)
        {
            return recursive_contain(cur->left, key);
        }
        else
        {
            return recursive_contain(cur->right, key);
        }
    }

    Node* recursive_find_node(Node* cur, const TK& key)
    {
        if (cur == nullptr)
        {
            return nullptr;
        }

        if (key == cur->key)
        {
            return cur;
        }

        if (key < cur->key)
        {
            return recursive_find_node(cur->left, key);
        }
        else
        {
            return recursive_find_node(cur->right, key);
        }
    }

    Node* recursive_erase(Node* cur, const TK& key)
    {
        if (cur == nullptr)
        {
            return nullptr;
        }

        if (key < cur->key)
        {
            cur->left = recursive_erase(cur->left, key);
        }
        else if (key > cur->key)
        {
            cur->right = recursive_erase(cur->right, key);
        }
        else
        {
            if (cur->left == nullptr)
            {
                m_size--;
                Node* temp = cur->right;
                delete cur;
                return temp;
            }
            else if (cur->right == nullptr)
            {
                m_size--;
                Node* temp = cur->left;
                delete cur;
                return temp;
            }
            else
            {
                Node* min_of_right_node = get_min_node(cur->right);
                cur->key = min_of_right_node->key;
                cur->value = min_of_right_node->value;
                cur->right = recursive_erase(cur->right, min_of_right_node->key);
                return cur;
            }
        }

        // backtracking balancing
        if (cur == nullptr)
        {
            return cur;
        }

        cur->height = std::max(get_height(cur->left), get_height(cur->right)) + 1U;
        int balance = get_balance_factor(cur);
        int balance_left = get_balance_factor(cur->left);
        int balance_right = get_balance_factor(cur->right);

        // left left case
        if (balance > 1 && balance_left >= 0)
        {
            return rotate_right(cur);
        }

        // left right case
        if (balance > 1 && balance_left < 0)
        {
            cur->left = rotate_left(cur->left); // make it left left case
            return rotate_right(cur);
        }

        // right right case
        if (balance < -1 && balance_right <= 0)
        {
            return rotate_left(cur);
        }

        // right left case
        if (balance < -1 && balance_right > 0)
        {
            cur->right = rotate_right(cur->right); // make it right right case
            return rotate_left(cur);
        }

        return cur;
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

        if ((minNode != nullptr && cur->key <= minNode->key)
        ||  (maxNode != nullptr && cur->key >= maxNode->key))
        {
            return false;
        }

        return check_bst_validity(cur->left, minNode, cur)
            && check_bst_validity(cur->right, cur, maxNode);
    }

    // use for node that has balance factor > 0
    Node* rotate_right(Node* cur)
    {
        if (cur == nullptr)
        {
            return nullptr;
        }

        Node* cur_left = cur->left;
        Node* cur_left_right = cur_left->right;

        cur_left->right = cur;
        cur->left = cur_left_right;

        cur->height = std::max(get_height(cur->left), get_height(cur->right)) + 1U;
        cur_left->height = std::max(get_height(cur_left->left), get_height(cur_left->right)) + 1U;

        return cur_left;
    }

    // use for node that has balance factor < 0
    Node* rotate_left(Node* cur)
    {
        if (cur == nullptr)
        {
            return nullptr;
        }

        Node* cur_right = cur->right;
        Node* cur_right_left = cur_right->left;

        cur_right->left = cur;
        cur->right = cur_right_left;

        cur->height = std::max(get_height(cur->left), get_height(cur->right)) + 1U;
        cur_right->height = std::max(get_height(cur_right->left), get_height(cur_right->right)) + 1U;

        return cur_right;
    }

    std::size_t get_height(Node* cur)
    {
        if (cur == nullptr)
        {
            return 0U;
        }

        return cur->height;
    }

    int get_balance_factor(Node* cur)
    {
        if (cur == nullptr)
        {
            return 0;
        }

        return static_cast<int>(get_height(cur->left))
             - static_cast<int>(get_height(cur->right));
    }

    Node* get_min_node(Node* cur)
    {
        if (cur == nullptr)
        {
            return cur;
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
            return cur;
        }

        while (cur->right != nullptr)
        {
            cur = cur->right;
        }

        return cur;
    }

private:
    Node* m_root;
    std::size_t m_size;
};

#endif // AVL_TREE_H