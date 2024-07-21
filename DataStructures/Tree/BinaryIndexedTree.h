#ifndef BINARY_INDEXED_TREE_H
#define BINARY_INDEXED_TREE_H

#include <iostream>
#include <vector>

/**
 * @brief A Binary Indexed Tree (BIT), also known as a Fenwick Tree, 
 * is a data structure that helps efficiently update elements and calculate prefix sums in an array.
 * 
 * @ref
 * https://www.geeksforgeeks.org/fenwick-tree-for-competitive-programming
 * https://www.topcoder.com/thrive/articles/Binary%20Indexed%20Trees
 */

template <typename T>
class BinaryIndexedTree
{
    static_assert(std::is_arithmetic<T>::value, "Template parameter must be an arithmetic type");

public:
    BinaryIndexedTree(const std::size_t& size)
        : m_tree(size + 1U, T())
    {
    }

    BinaryIndexedTree(const std::vector<T>& V)
        : BinaryIndexedTree(V.size())
    {
        for (int i = 0; i < V.size(); i++)
        {
            update(i + 1, V[i]);
        }
    }

    ~BinaryIndexedTree()
    {
        
    }

    // Update function to add 'delta' to element at index 'idx'
    void update(int idx, const T& delta)
    {
        while (idx < m_tree.size())
        {
            m_tree[idx] += delta;
            int right_most_set_bit = idx & (-idx);
            idx += right_most_set_bit;
        }
    }

    // Query function to get the prefix sum up to index 'idx'
    T query_prefix_sum(int idx)
    {
        T sum = T{};
        while (idx > 0)
        {
            sum += m_tree[idx];
            int right_most_set_bit = idx & (-idx);
            idx -= right_most_set_bit;
        }
        return sum;
    }

    // Query function to get the sum between two indices (inclusive)
    T query_range(int left, int right)
    {
        return query_prefix_sum(right) - query_prefix_sum(left - 1);
    }

private:
    std::vector<T> m_tree;
};

#endif // BINARY_INDEXED_TREE_H