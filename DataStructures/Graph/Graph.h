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

class IGraph
{
public:
    IGraph(std::size_t N)
        : m_num_vertex(N)
    {
    }

    ~IGraph()
    {
    }

    virtual void add_edge(const std::size_t& source, const std::size_t& dest) = 0;
    virtual void add_edge(const std::size_t& source, const std::size_t& dest, const std::size_t& weight) = 0;
    virtual bool has_edge(const std::size_t& source, const std::size_t& dest) = 0;
    virtual void remove_edge(const std::size_t& source, const std::size_t& dest) = 0;
    virtual bool is_connected(const std::size_t& source, const std::size_t& dest) = 0;
    virtual bool has_cycle() = 0;
    virtual std::size_t distance(const std::size_t& source, const std::size_t& dest) = 0;
    virtual std::vector<std::size_t> shortest_path(const std::size_t& source, const std::size_t& dest) = 0;

protected:
    std::size_t m_num_vertex;
    std::unordered_map<std::size_t, std::vector<std::pair<std::size_t, std::size_t>>> m_adj_list;
};

class DirectedGraph : public IGraph
{
public:
    DirectedGraph(std::size_t N)
        : IGraph(N)
    {
    }

    ~DirectedGraph()
    {
    }

    virtual void add_edge(const std::size_t& source, const std::size_t& dest)
    {
        if (source >= m_num_vertex || dest >= m_num_vertex)
        {
            throw std::out_of_range("Invalid vertex");
        }

        m_adj_list[source].push_back({1U, dest});
    }

    virtual void add_edge(const std::size_t& source, const std::size_t& dest, const std::size_t& weight)
    {
        if (source >= m_num_vertex || dest >= m_num_vertex)
        {
            throw std::out_of_range("Invalid vertex");
        }

        m_adj_list[source].push_back({weight, dest});
    }

    virtual bool has_edge(const std::size_t& source, const std::size_t& dest)
    {
        if (source >= m_num_vertex || dest >= m_num_vertex)
        {
            throw std::out_of_range("Invalid vertex");
        }

        const std::vector<std::pair<std::size_t, std::size_t>>& adj_with_source = m_adj_list[source];
        for (const std::pair<std::size_t, std::size_t>& p : adj_with_source)
        {
            if (p.second == dest)
            {
                return true;
            }
        }

        return false;
    }

    virtual void remove_edge(const std::size_t& source, const std::size_t& dest)
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
                    return p.second == dest;
                }
            ),
            adj_with_source.end()
        );
    }

    virtual bool is_connected(const std::size_t& source, const std::size_t& dest)
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
                if (visited.find(next.second) == visited.end())
                {
                    Q.push(next.second);
                    visited.insert(next.second);
                }
            }
        }

        return false;
    }

    virtual bool has_cycle()
    {
        std::vector<bool> visited(m_num_vertex, false);
        std::vector<bool> waypoints(m_num_vertex, false);
        for (std::size_t i = 0U; i < m_num_vertex; i++)
        {
            if (has_cycle_dfs(i, visited, waypoints))
            {
                return true;
            }
        }
        return false;
    }

    virtual std::size_t distance(const std::size_t& source, const std::size_t& dest)
    {
        if (source >= m_num_vertex || dest >= m_num_vertex)
        {
            throw std::out_of_range("Invalid vertex");
        }

        if (source == dest)
        {
            return 0U;
        }

        std::vector<std::size_t> v_dist(m_num_vertex, UNREACHABLE_DISTANCE);
        v_dist[source] = 0U;

        std::priority_queue<std::pair<std::size_t, std::size_t>,
                            std::vector<std::pair<std::size_t, std::size_t>>,
                            std::greater<std::pair<std::size_t, std::size_t>>> PQ;
        PQ.push({0U, source});

        while (!PQ.empty())
        {
            std::pair<std::size_t, std::size_t> cur = PQ.top();
            PQ.pop();
            
            if (cur.first > v_dist[cur.second])
            {
                continue;
            }

            if (cur.second == dest)
            {
                return cur.first;
            }

            const std::vector<std::pair<std::size_t, std::size_t>>& adj_with_cur = m_adj_list[cur.second];
            for (const std::pair<std::size_t, std::size_t>& next : adj_with_cur)
            {
                if (cur.first + next.first < v_dist[next.second])
                {
                    v_dist[next.second] = cur.first + next.first;
                    PQ.push({v_dist[next.second], next.second});
                }
            }
        }

        return UNREACHABLE_DISTANCE;
    }

    virtual std::vector<std::size_t> shortest_path(const std::size_t& source, const std::size_t& dest)
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

        std::priority_queue<std::pair<std::size_t, std::size_t>,
                            std::vector<std::pair<std::size_t, std::size_t>>,
                            std::greater<std::pair<std::size_t, std::size_t>>> PQ;
        PQ.push({0U, source});

        std::unordered_map<std::size_t, std::size_t> parents;
        parents[source] = source;

        std::vector<std::size_t> v_dist(m_num_vertex, UNREACHABLE_DISTANCE);
        v_dist[source] = 0U;

        while (!PQ.empty())
        {
            std::pair<std::size_t, std::size_t> cur = PQ.top();
            PQ.pop();

            if (cur.first > v_dist[cur.second])
            {
                continue;
            }

            if (cur.second == dest)
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

            const std::vector<std::pair<std::size_t, std::size_t>>& adj_with_cur = m_adj_list[cur.second];
            for (const std::pair<std::size_t, std::size_t>& next : adj_with_cur)
            {
                if (cur.first + next.first < v_dist[next.second])
                {
                    v_dist[next.second] = cur.first + next.first;
                    PQ.push({v_dist[next.second], next.second});
                    parents[next.second] = cur.second;
                }
            }
        }

        return path;
    }

private:
    bool has_cycle_dfs(std::size_t cur, std::vector<bool>& visited, std::vector<bool>& waypoints)
    {
        if (!visited[cur])
        {
            visited[cur] = true;
            waypoints[cur] = true;

            const std::vector<std::pair<std::size_t, std::size_t>>& adj_with_cur = m_adj_list[cur];
            for (const std::pair<std::size_t, std::size_t>& next : adj_with_cur)
            {
                if (!visited[next.second] && has_cycle_dfs(next.second, visited, waypoints))
                {
                    return true;
                }
                else if (waypoints[next.second])
                {
                    return true;
                }
            }
        }

        waypoints[cur] = false;

        return false;
    }
};

class UndirectedGraph : public DirectedGraph
{
public:
    UndirectedGraph(std::size_t N)
        : DirectedGraph(N)
    {     
    }

    ~UndirectedGraph()
    {
    }

    virtual void add_edge(const std::size_t& source, const std::size_t& dest) override
    {
        if (source >= m_num_vertex || dest >= m_num_vertex)
        {
            throw std::out_of_range("Invalid vertex");
        }

        m_adj_list[source].push_back({1U, dest});
        m_adj_list[dest].push_back({1U, source});
    }

    virtual void add_edge(const std::size_t& source, const std::size_t& dest, const std::size_t& weight) override
    {
        if (source >= m_num_vertex || dest >= m_num_vertex)
        {
            throw std::out_of_range("Invalid vertex");
        }

        m_adj_list[source].push_back({weight, dest});
        m_adj_list[dest].push_back({weight, source});
    }

    virtual void remove_edge(const std::size_t& source, const std::size_t& dest) override
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
                    return p.second == dest;
                }
            ),
            adj_with_source.end()
        );

        std::vector<std::pair<std::size_t, std::size_t>>& adj_with_dest = m_adj_list[dest];
        adj_with_dest.erase(
            std::remove_if(
                adj_with_dest.begin(),
                adj_with_dest.end(),
                [source](const std::pair<std::size_t, std::size_t>& p)
                {
                    return p.second == source;
                }
            ),
            adj_with_dest.end()
        );
    }

    virtual bool has_cycle() override
    {
        std::unordered_set<std::size_t> visited;
        for (std::size_t i = 0U; i < m_num_vertex; i++)
        {
            if (visited.find(i) == visited.end())
            {
                if (has_cycle_dfs(i, visited, UNREACHABLE_DISTANCE))
                {
                    return true;
                }
            }
        }
        return false;
    }

    std::vector<std::vector<std::size_t>> connected_components()
    {
        return {};
    }

    std::vector<std::pair<std::size_t, std::pair<std::size_t, std::size_t>>> min_spanning_tree_prim()
    {
        return {};
    }

    std::vector<std::pair<std::size_t, std::pair<std::size_t, std::size_t>>> min_spanning_tree_kruskal()
    {
        return {};
    }

    std::vector<std::vector<std::size_t>> min_distance_all_pairs()
    {
        // Floyd Warshall Algorithm
        return {};
    }

private:
    bool has_cycle_dfs(std::size_t cur, std::unordered_set<std::size_t>& visited, std::size_t parent)
    {
        visited.insert(cur);

        const std::vector<std::pair<std::size_t, std::size_t>>& adj_with_cur = m_adj_list[cur];
        for (const std::pair<std::size_t, std::size_t>& next : adj_with_cur)
        {
            if (visited.find(next.second) == visited.end())
            {
                if (has_cycle_dfs(next.second, visited, cur))
                {
                    return true;
                }
            }
            else if (next.second != parent)
            {
                return true;
            }
        }
        return false;
    }
};

#endif // GRAPH_H