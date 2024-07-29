#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <climits>
#include <stack>
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
    virtual std::vector<std::size_t> traversal_bfs(const std::size_t& source) = 0;
    virtual std::vector<std::size_t> traversal_dfs(const std::size_t& source) = 0;
    virtual std::vector<std::vector<std::size_t>> connected_components() = 0;
    virtual std::size_t distance(const std::size_t& source, const std::size_t& dest) = 0;
    virtual std::vector<std::size_t> shortest_path(const std::size_t& source, const std::size_t& dest) = 0;
    virtual std::unordered_set<std::size_t> reachable_vertices(const std::size_t& source, const std::size_t& limited_distance) = 0;
    virtual std::vector<std::vector<std::size_t>> min_distance_all_pairs() = 0;

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

        if (source != dest)
        {
            m_adj_list[source].push_back({1U, dest});
        }
    }

    virtual void add_edge(const std::size_t& source, const std::size_t& dest, const std::size_t& weight)
    {
        if (source >= m_num_vertex || dest >= m_num_vertex)
        {
            throw std::out_of_range("Invalid vertex");
        }

        if (source != dest)
        {
            m_adj_list[source].push_back({weight, dest});
        }
    }

    virtual bool has_edge(const std::size_t& source, const std::size_t& dest)
    {
        if (source >= m_num_vertex || dest >= m_num_vertex)
        {
            throw std::out_of_range("Invalid vertex");
        }

        if (source == dest)
        {
            return true;
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
            if (has_cycle_dfs_util(i, visited, waypoints))
            {
                return true;
            }
        }
        return false;
    }

    virtual std::vector<std::size_t> traversal_bfs(const std::size_t& source)
    {
        std::vector<std::size_t> elements;
        std::unordered_set<std::size_t> visited;
        std::queue<std::size_t> Q;
        Q.push(source);
        visited.insert(source);

        while (!Q.empty())
        {
            std::size_t cur = Q.front();
            Q.pop();

            elements.push_back(cur);

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

        return elements;
    }

    virtual std::vector<std::size_t> traversal_dfs(const std::size_t& source)
    {
        std::vector<std::size_t> elements;
        std::unordered_set<std::size_t> visited;
        traversal_dfs_util(source, visited, elements);

        return elements;
    }

    virtual std::vector<std::vector<std::size_t>> connected_components() override
    {
        std::vector<std::vector<std::size_t>> components;

        std::vector<bool> in_scc(m_num_vertex, false);

        for (std::size_t cur = 0U; cur < m_num_vertex; cur++)
        {
            if (in_scc[cur] == false)
            {
                std::vector<std::size_t> component;
                component.push_back(cur);
                in_scc[cur] = true;

                for (std::size_t candidate = 0U; candidate < m_num_vertex; candidate++)
                {
                    if (in_scc[candidate] == false
                     && is_connected(cur, candidate)
                     && is_connected(candidate, cur))
                    {
                        component.push_back(candidate);
                        in_scc[candidate] = true;
                    }
                }

                components.push_back(component);
            }
        }

        return components;
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

    virtual std::unordered_set<std::size_t> reachable_vertices(const std::size_t& source, const std::size_t& limited_distance)
    {
        if (source >= m_num_vertex)
        {
            throw std::out_of_range("Invalid vertex");
        }

        std::unordered_set<std::size_t> reachable_vertices;

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

            if (cur.first > std::min(limited_distance, v_dist[cur.second]))
            {
                continue;
            }

            reachable_vertices.insert(cur.second);

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

        return reachable_vertices;
    }

    virtual std::vector<std::vector<std::size_t>> min_distance_all_pairs()
    {
        std::vector<std::vector<std::size_t>> min_dist(m_num_vertex, std::vector<std::size_t>(m_num_vertex, UNREACHABLE_DISTANCE));

        for (std::size_t cur = 0U; cur < m_num_vertex; cur++)
        {
            min_dist[cur][cur] = 0U;

            const std::vector<std::pair<std::size_t, std::size_t>>& adj_with_cur = m_adj_list[cur];
            for (const std::pair<std::size_t, std::size_t>& adj_vertex : adj_with_cur)
            {
                min_dist[cur][adj_vertex.second] = adj_vertex.first;
            }
        }

        for (std::size_t intermediate = 0U; intermediate < m_num_vertex; intermediate++)
        {
            for (std::size_t source = 0U; source < m_num_vertex; source++)
            {
                if (min_dist[source][intermediate] == UNREACHABLE_DISTANCE)
                {
                    continue;
                }

                for (std::size_t dest = 0U; dest < m_num_vertex; dest++)
                {
                    if (min_dist[intermediate][dest] == UNREACHABLE_DISTANCE)
                    {
                        continue;
                    }

                    if (min_dist[source][intermediate] + min_dist[intermediate][dest] < min_dist[source][dest])
                    {
                        min_dist[source][dest] = min_dist[source][intermediate] + min_dist[intermediate][dest];
                    }
                }
            }
        }

        return min_dist;
    }

    std::vector<std::size_t> topological_sort()
    {
        if (has_cycle())
        {
            return {};
        }

        std::vector<std::size_t> sorted;

        std::unordered_set<std::size_t> visited;
        std::stack<std::size_t> st;
        for (std::size_t cur = 0U; cur < m_num_vertex; cur++)
        {
            if (visited.find(cur) == visited.end())
            {
                topological_sort_dfs(cur, visited, st);
            }
        }

        while (!st.empty())
        {
            sorted.push_back(st.top());
            st.pop();
        }

        return sorted;
    }

    bool is_topologically_sorted(const std::vector<std::size_t>& vertices)
    {
        if (has_cycle())
        {
            return false;
        }

        if (vertices.size() != m_num_vertex)
        {
            return false;
        }

        std::unordered_map<std::size_t, std::size_t> topo_index;
        for (std::size_t i = 0U; i < vertices.size(); i++)
        {
            topo_index[vertices[i]] = i;
        }

        for (std::size_t cur = 0U; cur < m_num_vertex; cur++)
        {
            const std::vector<std::pair<std::size_t, std::size_t>>& adj_with_cur = m_adj_list[cur];
            for (const std::pair<std::size_t, std::size_t>& adj_vertex : adj_with_cur)
            {
                if (topo_index[cur] >= topo_index[adj_vertex.second])
                {
                    return false;
                }
            }
        }

        return true;
    }

private:
    void traversal_dfs_util(std::size_t cur, std::unordered_set<std::size_t>& visited, std::vector<std::size_t>& elements)
    {
        visited.insert(cur);
        elements.push_back(cur);

        const std::vector<std::pair<std::size_t, std::size_t>>& adj_with_cur = m_adj_list[cur];
        for (const std::pair<std::size_t, std::size_t>& next : adj_with_cur)
        {
            if (visited.find(next.second) == visited.end())
            {
                traversal_dfs_util(next.second, visited, elements);       
            }
        }
    }

    bool has_cycle_dfs_util(std::size_t cur, std::vector<bool>& visited, std::vector<bool>& waypoints)
    {
        if (!visited[cur])
        {
            visited[cur] = true;
            waypoints[cur] = true;

            const std::vector<std::pair<std::size_t, std::size_t>>& adj_with_cur = m_adj_list[cur];
            for (const std::pair<std::size_t, std::size_t>& next : adj_with_cur)
            {
                if (!visited[next.second] && has_cycle_dfs_util(next.second, visited, waypoints))
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

    void topological_sort_dfs(std::size_t cur, std::unordered_set<std::size_t>& visited, std::stack<std::size_t>& st)
    {
        visited.insert(cur);

        const std::vector<std::pair<std::size_t, std::size_t>>& adj_with_cur = m_adj_list[cur];
        for (const std::pair<std::size_t, std::size_t>& adj_vertex : adj_with_cur)
        {
            if (visited.find(adj_vertex.second) == visited.end())
            {
                topological_sort_dfs(adj_vertex.second, visited, st);
            }
        }

        st.push(cur);
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

        if (source != dest)
        {
            m_adj_list[source].push_back({1U, dest});
            m_adj_list[dest].push_back({1U, source});
        }
    }

    virtual void add_edge(const std::size_t& source, const std::size_t& dest, const std::size_t& weight) override
    {
        if (source >= m_num_vertex || dest >= m_num_vertex)
        {
            throw std::out_of_range("Invalid vertex");
        }

        if (source != dest)
        {
            m_adj_list[source].push_back({weight, dest});
            m_adj_list[dest].push_back({weight, source});
        }
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
        UnionFind UF(m_num_vertex);
        for (std::size_t cur = 0U; cur < m_num_vertex; cur++)
        {
            const std::vector<std::pair<std::size_t, std::size_t>>& adj_with_cur = m_adj_list[cur];
            for (const std::pair<std::size_t, std::size_t>& adj_vertex : adj_with_cur)
            {
                if (cur < adj_vertex.second)
                {
                    int rootCur = UF.find(cur);
                    int rootNext = UF.find(adj_vertex.second);
                    if (rootCur == rootNext)
                    {
                        return true;
                    }

                    UF.unite(cur, adj_vertex.second);
                }
            }
        }

        return false;
    }

    virtual std::vector<std::vector<std::size_t>> connected_components() override
    {
        std::vector<std::vector<std::size_t>> components;

        UnionFind UF(m_num_vertex);
        for (std::size_t cur = 0U; cur < m_num_vertex; cur++)
        {
            const std::vector<std::pair<std::size_t, std::size_t>>& adj_with_cur = m_adj_list[cur];
            for (const std::pair<std::size_t, std::size_t>& adj_vertex : adj_with_cur)
            {
                UF.unite(cur, adj_vertex.second);
            }
        }

        std::unordered_map<std::size_t, std::vector<std::size_t>> groups;
        for (std::size_t cur = 0U; cur < m_num_vertex; cur++)
        {
            groups[UF.find(cur)].push_back(cur);
        }

        for (std::unordered_map<std::size_t, std::vector<std::size_t>>::iterator it = groups.begin(); it != groups.end(); it++)
        {
            components.push_back(it->second);
        }

        return components;
    }

    virtual std::vector<std::vector<std::size_t>> min_distance_all_pairs() override
    {
        std::vector<std::vector<std::size_t>> min_dist(m_num_vertex, std::vector<std::size_t>(m_num_vertex, UNREACHABLE_DISTANCE));

        for (std::size_t cur = 0U; cur < m_num_vertex; cur++)
        {
            min_dist[cur][cur] = 0U;

            const std::vector<std::pair<std::size_t, std::size_t>>& adj_with_cur = m_adj_list[cur];
            for (const std::pair<std::size_t, std::size_t>& adj_vertex : adj_with_cur)
            {
                min_dist[cur][adj_vertex.second] = adj_vertex.first;
                min_dist[adj_vertex.second][cur] = adj_vertex.first;
            }
        }

        for (std::size_t intermediate = 0U; intermediate < m_num_vertex; intermediate++)
        {
            for (std::size_t source = 0U; source < m_num_vertex; source++)
            {
                if (min_dist[source][intermediate] == UNREACHABLE_DISTANCE)
                {
                    continue;
                }

                for (std::size_t dest = 0U; dest < m_num_vertex; dest++)
                {
                    if (min_dist[intermediate][dest] == UNREACHABLE_DISTANCE)
                    {
                        continue;
                    }

                    if (min_dist[source][intermediate] + min_dist[intermediate][dest] < min_dist[source][dest])
                    {
                        min_dist[source][dest] = min_dist[source][intermediate] + min_dist[intermediate][dest];
                        min_dist[dest][source] = min_dist[source][intermediate] + min_dist[intermediate][dest];
                    }
                }
            }
        }

        return min_dist;
    }

    std::vector<std::pair<std::size_t, std::pair<std::size_t, std::size_t>>> min_spanning_tree_kruskal()
    {
        std::vector<std::pair<std::size_t, std::pair<std::size_t, std::size_t>>> min_tree;

        std::priority_queue<std::pair<std::size_t, std::pair<std::size_t, std::size_t>>,
                            std::vector<std::pair<std::size_t, std::pair<std::size_t, std::size_t>>>,
                            std::greater<std::pair<std::size_t, std::pair<std::size_t, std::size_t>>>> PQ;
        
        for (std::size_t cur = 0U; cur < m_num_vertex; cur++)
        {
            const std::vector<std::pair<std::size_t, std::size_t>>& adj_with_cur = m_adj_list[cur];
            for (const std::pair<std::size_t, std::size_t>& adj_vertex : adj_with_cur)
            {
                if (cur < adj_vertex.second)
                {
                    PQ.push({adj_vertex.first, {cur, adj_vertex.second}});
                }
            }
        }

        UnionFind UF(m_num_vertex);
        while (!PQ.empty() && min_tree.size() < m_num_vertex - 1U)
        {
            std::pair<std::size_t, std::pair<std::size_t, std::size_t>> cur_edge = PQ.top();
            PQ.pop();

            if (UF.find(cur_edge.second.first) == UF.find(cur_edge.second.second))
            {
                continue;
            }
            else
            {
                UF.unite(cur_edge.second.first, cur_edge.second.second);
                min_tree.push_back(cur_edge);
            }
        }

        if (min_tree.size() < m_num_vertex - 1U)
        {
            // Graph is not fully connected, no spanning tree available
            min_tree.clear();
        }

        return min_tree;
    }

    std::vector<std::pair<std::size_t, std::pair<std::size_t, std::size_t>>> min_spanning_tree_prim()
    {
        std::vector<std::pair<std::size_t, std::pair<std::size_t, std::size_t>>> min_tree;

        std::vector<std::size_t> parents(m_num_vertex, UNREACHABLE_DISTANCE);
        std::vector<std::size_t> weights(m_num_vertex, UNREACHABLE_DISTANCE);
        std::unordered_set<std::size_t> mst_set;
        std::priority_queue<std::pair<std::size_t, std::size_t>,
                            std::vector<std::pair<std::size_t, std::size_t>>,
                            std::greater<std::pair<std::size_t, std::size_t>>> PQ;
        PQ.push({0U, 0U});
        weights[0U] = 0U;

        while (!PQ.empty())
        {
            std::pair<std::size_t, std::size_t> cur = PQ.top();
            PQ.pop();

            mst_set.insert(cur.second);

            const std::vector<std::pair<std::size_t, std::size_t>>& adj_with_cur = m_adj_list[cur.second];
            for (const std::pair<std::size_t, std::size_t>& next : adj_with_cur)
            {
                if (mst_set.find(next.second) == mst_set.end())
                {
                    if (weights[next.second] > next.first)
                    {
                        weights[next.second] = next.first;
                        parents[next.second] = cur.second;
                        PQ.push({next.first, next.second});
                    }
                }
            }
        }

        for (std::size_t i = 1U; i < m_num_vertex; i++)
        {
            if (parents[i] != UNREACHABLE_DISTANCE)
            {
                min_tree.push_back({weights[i], {parents[i], i}});
            }
        }

        if (min_tree.size() < m_num_vertex - 1U)
        {
            // Graph is not fully connected, no spanning tree available
            min_tree.clear();
        }

        return min_tree;
    }

    std::vector<std::pair<std::size_t, std::size_t>> find_bridges()
    {
        std::vector<std::pair<std::size_t, std::size_t>> bridges;

        std::unordered_set<std::size_t> visited;
        std::vector<std::size_t> parents(m_num_vertex, UNREACHABLE_DISTANCE);
        std::vector<std::size_t> discovery(m_num_vertex, 0U);
        std::vector<std::size_t> low_link(m_num_vertex, 0U);
        std::size_t f_time = 0U;

        for (std::size_t cur = 0U; cur < m_num_vertex; cur++)
        {
            if (visited.find(cur) == visited.end())
            {
                find_bridges_dfs(cur, visited, parents, discovery, low_link, f_time, bridges);
            }
        }

        return bridges;
    }

    std::vector<std::size_t> find_articulation_points()
    {
        std::vector<std::size_t> articulation_points;

        std::unordered_set<std::size_t> visited;
        std::vector<std::size_t> parents(m_num_vertex, UNREACHABLE_DISTANCE);
        std::vector<std::size_t> discovery(m_num_vertex, 0U);
        std::vector<std::size_t> low_link(m_num_vertex, 0U);
        std::size_t f_time = 0U;

        for (std::size_t cur = 0U; cur < m_num_vertex; cur++)
        {
            if (visited.find(cur) == visited.end())
            {
                find_articulation_points_dfs(cur, visited, discovery, low_link, f_time, UNREACHABLE_DISTANCE, articulation_points);
            }
        }

        return articulation_points;
    }

    std::vector<std::size_t> coloring_graph()
    {
        std::vector<std::size_t> color_map(m_num_vertex, UNREACHABLE_DISTANCE);
        
        std::vector<std::size_t> sorted_vertex(m_num_vertex);
        for (std::size_t i = 0U; i < m_num_vertex; i++)
        {
            sorted_vertex[i] = i;
        }

        std::sort(
            sorted_vertex.begin(), 
            sorted_vertex.end(), 
            [this](std::size_t a, std::size_t b)
            {
                return m_adj_list[a].size() > m_adj_list[b].size();
            }
        );

        for (std::size_t cur : sorted_vertex)
        {
            std::vector<bool> available(m_num_vertex, true);

            const std::vector<std::pair<std::size_t, std::size_t>>& adj_with_cur = m_adj_list[cur];
            for (const std::pair<std::size_t, std::size_t>& adj_vertex : adj_with_cur)
            {
                if (color_map[adj_vertex.second] != UNREACHABLE_DISTANCE)
                {
                    available[color_map[adj_vertex.second]] = false;
                }
            }

            std::size_t chosen_color = UNREACHABLE_DISTANCE;
            for (std::size_t i = 0U; i < m_num_vertex; i++)
            {
                if (available[i])
                {
                    chosen_color = i;
                    break;
                }
            }

            color_map[cur] = chosen_color;
        }

        return color_map;
    }

private:
    void find_bridges_dfs(std::size_t cur
                        , std::unordered_set<std::size_t>& visited
                        , std::vector<std::size_t>& parents
                        , std::vector<std::size_t>& disc
                        , std::vector<std::size_t>& low_link
                        , std::size_t& f_time
                        , std::vector<std::pair<std::size_t, std::size_t>>& bridges)
    {
        f_time++;
        disc[cur] = f_time;
        low_link[cur] = f_time;

        visited.insert(cur);

        const std::vector<std::pair<std::size_t, std::size_t>>& adj_with_cur = m_adj_list[cur];
        for (const std::pair<std::size_t, std::size_t>& adj_vertex : adj_with_cur)
        {
            if (visited.find(adj_vertex.second) == visited.end())
            {
                parents[adj_vertex.second] = cur;
                find_bridges_dfs(adj_vertex.second, visited, parents, disc, low_link, f_time, bridges);

                // backtrack
                low_link[cur] = std::min(low_link[cur], low_link[adj_vertex.second]);
                if (low_link[adj_vertex.second] > disc[cur])
                {
                    bridges.push_back({cur, adj_vertex.second});
                }
            }
            else
            {
                if (adj_vertex.second != parents[cur])
                {
                    low_link[cur] = std::min(low_link[cur], disc[adj_vertex.second]);
                }
            }
        }
    }

    void find_articulation_points_dfs(std::size_t cur
                                    , std::unordered_set<std::size_t>& visited
                                    , std::vector<std::size_t>& disc
                                    , std::vector<std::size_t>& low_link
                                    , std::size_t& f_time
                                    , std::size_t parent
                                    , std::vector<std::size_t>& articulation)
    {
        f_time++;
        disc[cur] = f_time;
        low_link[cur] = f_time;

        visited.insert(cur);

        int children = 0;
        const std::vector<std::pair<std::size_t, std::size_t>>& adj_with_cur = m_adj_list[cur];
        for (const std::pair<std::size_t, std::size_t>& adj_vertex : adj_with_cur)
        {
            if (visited.find(adj_vertex.second) == visited.end())
            {
                children++;
                find_articulation_points_dfs(adj_vertex.second, visited, disc, low_link, f_time, cur, articulation);

                // backtrack
                low_link[cur] = std::min(low_link[cur], low_link[adj_vertex.second]);
                if (parent != UNREACHABLE_DISTANCE && low_link[adj_vertex.second] >= disc[cur])
                {
                    articulation.push_back(cur);
                }
            }
            else
            {
                if (adj_vertex.second != parent)
                {
                    low_link[cur] = std::min(low_link[cur], disc[adj_vertex.second]);
                }
            }
        }
    }
};

#endif // GRAPH_H