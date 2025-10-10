#ifndef BINARY_INDEXED_TREE_H
#define BINARY_INDEXED_TREE_H

#include <stdexcept>
#include <iostream>
#include <vector>

/**
 * @brief A Binary Indexed Tree (BIT), also known as a Fenwick Tree, 
 * is a data structure that helps efficiently update elements and calculate prefix sums in an array.
 * 
 * @ref
 * https://www.geeksforgeeks.org/fenwick-tree-for-competitive-programming
 * https://www.topcoder.com/thrive/articles/Binary%20Indexed%20Trees
 * https://www.geeksforgeeks.org/two-dimensional-binary-indexed-tree-or-fenwick-tree
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
        if (idx < 0 || idx >= m_tree.size())
        {
            throw std::out_of_range("Index out of range");
        }

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
        if (idx < 0 || idx >= m_tree.size())
        {
            throw std::out_of_range("Index out of range");
        }

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
        if (left < 0 || left > right || right >= m_tree.size())
        {
            throw std::out_of_range("Invalid indices");
        }

        return query_prefix_sum(right) - query_prefix_sum(left - 1);
    }

private:
    std::vector<T> m_tree;
};

template <typename T>
class BinaryIndexedTree2D
{
    static_assert(std::is_arithmetic<T>::value, "Template parameter must be an arithmetic type");

public:
    BinaryIndexedTree2D(const std::size_t& num_row, const std::size_t& num_col)
        : m_tree(num_row + 1, std::vector<T>(num_col + 1, T()))
    {
    }

    BinaryIndexedTree2D(const std::vector<std::vector<T>>& V)
        : BinaryIndexedTree2D(V.size(), V[0].size())
    {
        for (int i = 0; i < V.size(); i++)
        {
            for (int j = 0; j < V[i].size(); j++)
            {
                update(i + 1, j + 1, V[i][j]);
            }
        }
    }

    ~BinaryIndexedTree2D()
    {
        
    }

    // Update function to add 'delta' to element at index 'idx'
    void update(int row_bot_right, int col_bot_right, const T& delta)
    {
        if (row_bot_right < 0
         || row_bot_right >= m_tree.size()
         || col_bot_right < 0
         || col_bot_right >= m_tree[0].size())
        {
            throw std::out_of_range("Invalid indices");
        }

        for (int row = row_bot_right; row < m_tree.size(); row += (row & (-row)))
        {
            for (int col = col_bot_right; col < m_tree[row].size(); col += (col & (-col)))
            {
                m_tree[row][col] += delta;
            }
        }
    }

    // Query function to get the prefix sum up to index 'idx'
    T query_prefix_sum(int row_bot_right, int col_bot_right)
    {
        if (row_bot_right < 0
         || row_bot_right >= m_tree.size()
         || col_bot_right < 0
         || col_bot_right >= m_tree[0].size())
        {
            throw std::out_of_range("Invalid indices");
        }

        T sum = T{};

        for (int row = row_bot_right; row > 0; row -= (row & (-row)))
        {
            for (int col = col_bot_right; col > 0; col -= (col & (-col)))
            {
                sum += m_tree[row][col];
            }
        }

        return sum;
    }

    // Query function to get the sum between two indices (inclusive)
    T query_range(int row_up_left, int col_up_left, int row_bot_right, int col_bot_right)
    {
        if ((row_up_left < 0 || row_up_left > row_bot_right || row_bot_right >= m_tree.size())
         || (col_up_left < 0 || col_up_left > col_bot_right || col_bot_right >= m_tree[0].size()))
        {
            throw std::out_of_range("Invalid indices");
        }

        return query_prefix_sum(row_bot_right, col_bot_right)
             - query_prefix_sum(row_up_left - 1, col_bot_right)
             - query_prefix_sum(row_bot_right, col_up_left - 1)
             + query_prefix_sum(row_up_left - 1, col_up_left - 1);
    }

private:
    std::vector<std::vector<T>> m_tree;
};

#endif // BINARY_INDEXED_TREE_H