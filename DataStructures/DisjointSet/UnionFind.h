#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <iostream>
#include <vector>
#include <algorithm>

class UnionFind
{
public:
    UnionFind(std::size_t num_element)
        : m_parents(num_element)
        , m_rank(num_element, 0)
    {
        for (std::size_t i = 0U; i < num_element; i++)
        {
            m_parents[i] = i;
        }
    }

    ~UnionFind()
    {
    }

    void unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY)
        {
            // Union by rank
            if (m_rank[rootX] > m_rank[rootY])
            {
                m_parents[rootY] = rootX;
            }
            else if (m_rank[rootX] < m_rank[rootY])
            {
                m_parents[rootX] = rootY;
            }
            else
            {
                m_parents[rootY] = rootX;
                m_rank[rootX]++;
            }
        }
    }

    int find(int x)
    {
        if (m_parents[x] != x)
        {
            // Path compression
            m_parents[x] = find(m_parents[x]);
        }

        return m_parents[x];
    }

    bool same_group(int x, int y)
    {
        return find(x) == find(y);
    }

private:
    std::vector<int> m_parents;
    std::vector<int> m_rank;
};

#endif // UNION_FIND_H