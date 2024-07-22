#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <climits>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <utility>

#include "./../DisjointSet/UnionFind.h"

constexpr std::size_t UNREACHABLE_DISTANCE = std::numeric_limits<std::size_t>::max();

class UnweightedGraph
{
public:
    UnweightedGraph(std::size_t N)
        : m_num_vertex(N)
    {

    }

    ~UnweightedGraph()
    {

    }

    void add_edge(const std::size_t& source, const std::size_t& dest)
    {
        if (source >= m_num_vertex || dest >= m_num_vertex)
        {
            throw std::out_of_range("Invalid vertex");
        }

        m_adj_list[source].push_back(dest);
    }

    bool has_edge(const std::size_t& source, const std::size_t& dest)
    {
        if (source >= m_num_vertex || dest >= m_num_vertex)
        {
            throw std::out_of_range("Invalid vertex");
        }

        const std::vector<std::size_t>& adj_with_source = m_adj_list[source];
        for (const std::size_t& vertex : adj_with_source)
        {
            if (vertex == dest)
            {
                return true;
            }
        }

        return false;
    }

    void remove_edge(const std::size_t& source, const std::size_t& dest)
    {
        if (source >= m_num_vertex || dest >= m_num_vertex)
        {
            throw std::out_of_range("Invalid vertex");
        }

        std::vector<std::size_t>& adj_with_source = m_adj_list[source];
        adj_with_source.erase(std::remove(adj_with_source.begin(), adj_with_source.end(), dest), adj_with_source.end());
    }

    bool is_connected(const std::size_t& source, const std::size_t& dest)
    {
        if (source >= m_num_vertex || dest >= m_num_vertex)
        {
            throw std::out_of_range("Invalid vertex");
        }

        return false;
    }

    std::size_t distance(const std::size_t& source, const std::size_t& dest)
    {
        if (source >= m_num_vertex || dest >= m_num_vertex)
        {
            throw std::out_of_range("Invalid vertex");
        }

        return UNREACHABLE_DISTANCE;
    }

    std::vector<std::size_t> shortest_path(const std::size_t& source, const std::size_t& dest)
    {
        if (source >= m_num_vertex || dest >= m_num_vertex)
        {
            throw std::out_of_range("Invalid vertex");
        }

        return {};
    }

private:
    std::unordered_map<std::size_t, std::vector<std::size_t>> m_adj_list;
    std::size_t m_num_vertex;
};


class WeightedGraph
{
public:
    WeightedGraph(std::size_t N)
        : m_num_vertex(N)
    {

    }

    ~WeightedGraph()
    {

    }

    void add_edge(const std::size_t& source, const std::size_t& dest, const std::size_t& weight)
    {
        if (source >= m_num_vertex || dest >= m_num_vertex)
        {
            throw std::out_of_range("Invalid vertex");
        }

        m_adj_list[source].push_back({dest, weight});
    }

    bool has_edge(const std::size_t& source, const std::size_t& dest)
    {
        if (source >= m_num_vertex || dest >= m_num_vertex)
        {
            throw std::out_of_range("Invalid vertex");
        }

        const std::vector<std::pair<std::size_t, std::size_t>>& adj_with_source = m_adj_list[source];
        for (const std::pair<std::size_t, std::size_t>& p : adj_with_source)
        {
            if (p.first == dest)
            {
                return true;
            }
        }

        return false;
    }

    void remove_edge(const std::size_t& source, const std::size_t& dest)
    {
        if (source >= m_num_vertex || dest >= m_num_vertex)
        {
            throw std::out_of_range("Invalid vertex");
        }

        std::vector<std::pair<std::size_t, std::size_t>>& adj_with_source = m_adj_list[source];
        adj_with_source.erase(
            std::remove_if(
                adj_with_source.begin(),
                adj_with_source.end(),
                [dest](const std::pair<std::size_t, std::size_t>& p)
                {
                    return p.first == dest;
                }
            ),
            adj_with_source.end()
        );
    }

    bool is_connected(const std::size_t& source, const std::size_t& dest)
    {
        if (source >= m_num_vertex || dest >= m_num_vertex)
        {
            throw std::out_of_range("Invalid vertex");
        }

        return false;
    }

    std::size_t distance(const std::size_t& source, const std::size_t& dest)
    {
        if (source >= m_num_vertex || dest >= m_num_vertex)
        {
            throw std::out_of_range("Invalid vertex");
        }

        return 0U;
    }

    std::vector<std::size_t> shortest_path(const std::size_t& source, const std::size_t& dest)
    {
        if (source >= m_num_vertex || dest >= m_num_vertex)
        {
            throw std::out_of_range("Invalid vertex");
        }

        return {};
    }

    std::vector<std::pair<std::size_t, std::size_t>> min_spanning_tree_kruskal()
    {
        return {};
    }

    std::vector<std::pair<std::size_t, std::size_t>> min_spanning_tree_prim()
    {
        return {};
    }

private:
    std::unordered_map<std::size_t, std::vector<std::pair<std::size_t, std::size_t>>> m_adj_list;
    std::size_t m_num_vertex;
};

#endif // GRAPH_H