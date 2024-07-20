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
 * https://www.hackerearth.com/practice/notes/binary-indexed-tree-or-fenwick-tree
 * https://cp-algorithms.com/data_structures/fenwick.html
 * https://www.topcoder.com/thrive/articles/Binary%20Indexed%20Trees
 */

template <typename T>
class BinaryIndexedTree
{
public:
    BinaryIndexedTree(const std::size_t& size)
        : m_tree(size + 1U, T())
        , m_size(size)
    {
    }

    ~BinaryIndexedTree()
    {
        
    }

    // Update function to add 'delta' to element at index 'idx'
    void update(const std::size_t& idx, const T& delta)
    {

    }

    // Query function to get the prefix sum up to index 'idx'
    T query_prefix_sum(const std::size_t& idx)
    {
        return T();
    }

    // Query function to get the sum between two indices (inclusive)
    T query_range(const std::size_t& left, const std::size_t& right)
    {
        return query_prefix_sum(right) - query_prefix_sum(left - 1U);
    }

private:
    std::vector<T> m_tree;
    std::size_t m_size;
};

#endif // BINARY_INDEXED_TREE_H