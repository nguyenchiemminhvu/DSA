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
        , m_size(num_element, 1)
        , m_num_clusters(num_element)
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
        if (x < 0 || x >= m_parents.size() || y < 0 || y >= m_parents.size())
        {
            throw std::out_of_range("Index out of range");
        }

        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY)
        {
            // Union by rank
            if (m_rank[rootX] > m_rank[rootY])
            {
                m_parents[rootY] = rootX;
                m_size[rootX] += m_size[rootY];
            }
            else if (m_rank[rootX] < m_rank[rootY])
            {
                m_parents[rootX] = rootY;
                m_size[rootY] += m_size[rootX];
            }
            else
            {
                m_parents[rootY] = rootX;
                m_rank[rootX]++;
                m_size[rootX] += m_size[rootY];
            }

            m_num_clusters--;
        }
    }

    int find(int x)
    {
        if (x < 0 || x >= m_parents.size())
        {
            throw std::out_of_range("Index out of range");
        }

        if (m_parents[x] != x)
        {
            // Path compression
            m_parents[x] = find(m_parents[x]);
        }

        return m_parents[x];
    }

    bool same_group(int x, int y)
    {
        if (x < 0 || x >= m_parents.size() || y < 0 || y >= m_parents.size())
        {
            throw std::out_of_range("Index out of range");
        }

        return find(x) == find(y);
    }

    int cluster_size(int x)
    {
        if (x < 0 || x >= m_parents.size())
        {
            throw std::out_of_range("Index out of range");
        }

        int rootX = find(x);
        return m_size[rootX];
    }

    int num_clusters() const
    {
        return m_num_clusters;
    }

private:
    std::vector<int> m_parents;
    std::vector<int> m_rank;
    std::vector<int> m_size;
    int m_num_clusters;
};

#endif // UNION_FIND_H