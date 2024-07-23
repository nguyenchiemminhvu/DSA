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

        if (source == dest)
        {
            return true;
        }

        std::unordered_set<std::size_t> visited;
        std::queue<std::size_t> Q;
        Q.push(source);
        visited.insert(source);

        while (!Q.empty())
        {
            std::size_t cur = Q.front();
            Q.pop();

            if (cur == dest)
            {
                return true;
            }

            const std::vector<std::size_t>& adj_with_cur = m_adj_list[cur];
            for (const std::size_t& next : adj_with_cur)
            {
                if (visited.find(next) == visited.end())
                {
                    Q.push(next);
                    visited.insert(next);
                }
            }
        }

        return false;
    }

    std::size_t distance(const std::size_t& source, const std::size_t& dest)
    {
        if (source >= m_num_vertex || dest >= m_num_vertex)
        {
            throw std::out_of_range("Invalid vertex");
        }

        if (source == dest)
        {
            return 0U;
        }

        std::unordered_set<std::size_t> visited;
        std::queue<std::pair<std::size_t, std::size_t>> Q;
        Q.push({source, 0U});
        visited.insert(source);

        while (!Q.empty())
        {
            std::pair<std::size_t, std::size_t> cur = Q.front();
            Q.pop();

            if (cur.first == dest)
            {
                return cur.second;
            }

            const std::vector<std::size_t>& adj_with_cur = m_adj_list[cur.first];
            for (const std::size_t& next : adj_with_cur)
            {
                if (visited.find(next) == visited.end())
                {
                    Q.push({next, cur.second + 1U});
                    visited.insert(next);
                }
            }
        }

        return UNREACHABLE_DISTANCE;
    }

    std::vector<std::size_t> shortest_path(const std::size_t& source, const std::size_t& dest)
    {
        if (source >= m_num_vertex || dest >= m_num_vertex)
        {
            throw std::out_of_range("Invalid vertex");
        }

        if (source == dest)
        {
            return {source};
        }

        std::vector<std::size_t> path;
        std::unordered_set<std::size_t> visited;
        std::unordered_map<std::size_t, std::size_t> parents;
        std::queue<std::size_t> Q;
        Q.push(source);
        visited.insert(source);
        parents[source] = source;

        while (!Q.empty())
        {
            std::size_t cur = Q.front();
            Q.pop();

            if (cur == dest)
            {
                // Build path from source to dest using parent mapping
                path.push_back(dest);
                std::size_t parent = parents[dest];
                while (parent != source)
                {
                    path.push_back(parent);
                    parent = parents[parent];
                }
                path.push_back(source);
                std::reverse(path.begin(), path.end());
                break;
            }

            const std::vector<std::size_t>& adj_with_cur = m_adj_list[cur];
            for (const std::size_t& next : adj_with_cur)
            {
                if (visited.find(next) == visited.end())
                {
                    parents[next] = cur;
                    Q.push(next);
                    visited.insert(next);
                }
            }
        }

        return path;
    }

private:
    std::size_t m_num_vertex;
    std::unordered_map<std::size_t, std::vector<std::size_t>> m_adj_list;
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

        if (source == dest)
        {
            return true;
        }

        std::unordered_set<std::size_t> visited;
        std::queue<std::size_t> Q;
        Q.push(source);
        visited.insert(source);

        while (!Q.empty())
        {
            std::size_t cur = Q.front();
            Q.pop();

            if (cur == dest)
            {
                return true;
            }

            const std::vector<std::pair<std::size_t, std::size_t>>& adj_with_cur = m_adj_list[cur];
            for (const std::pair<std::size_t, std::size_t>& next : adj_with_cur)
            {
                if (visited.find(next.first) == visited.end())
                {
                    Q.push(next.first);
                    visited.insert(next.first);
                }
            }
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
    std::size_t m_num_vertex;
    std::unordered_map<std::size_t, std::vector<std::pair<std::size_t, std::size_t>>> m_adj_list;
};

#endif // GRAPH_H