#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <climits>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

#include "./../DisjointSet/UnionFind.h"

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
    }

    bool has_edge(const std::size_t& source, const std::size_t& dest)
    {
        if (source >= m_num_vertex || dest >= m_num_vertex)
        {
            throw std::out_of_range("Invalid vertex");
        }

        return false;
    }

    void remove_edge(const std::size_t& source, const std::size_t& dest)
    {
        if (source >= m_num_vertex || dest >= m_num_vertex)
        {
            throw std::out_of_range("Invalid vertex");
        }
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

    void add_edge(const std::size_t& source, const std::size_t& dest)
    {
        if (source >= m_num_vertex || dest >= m_num_vertex)
        {
            throw std::out_of_range("Invalid vertex");
        }
    }

    bool has_edge(const std::size_t& source, const std::size_t& dest)
    {
        if (source >= m_num_vertex || dest >= m_num_vertex)
        {
            throw std::out_of_range("Invalid vertex");
        }

        return false;
    }

    void remove_edge(const std::size_t& source, const std::size_t& dest)
    {
        if (source >= m_num_vertex || dest >= m_num_vertex)
        {
            throw std::out_of_range("Invalid vertex");
        }
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