/**
https://vjudge.net/contest/691168#problem/J
https://usaco.guide/problems/usaco-646-closing-the-farm/solution

Farmer John and his cows are planning to leave town for a long vacation, and so FJ wants to temporarily close down his farm to save money in the meantime.
The farm consists of N barns connected with M bidirectional paths between some pairs of barns (1≤N,M≤3000). To shut the farm down, FJ plans to close one barn at a time. When a barn closes, all paths adjacent to that barn also close, and can no longer be used.

FJ is interested in knowing at each point in time (initially, and after each closing) whether his farm is "fully connected" -- meaning that it is possible to travel from any open barn to any other open barn along an appropriate series of paths. Since FJ's farm is initially in somewhat in a state of disrepair, it may not even start out fully connected.
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

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

    int cluster_size(int x)
    {
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

bool is_connected(unordered_map<int, vector<int>>& adj_list, int n, std::unordered_set<int>& closed)
{
    UnionFind uf(n);
    for (int i = 0; i < n; i++)
    {
        if (closed.count(i))
        {
            continue;
        }

        for (int adj : adj_list[i])
        {
            if (closed.count(adj))
            {
                continue;
            }

            uf.unite(i, adj);
        }
    }

    std::unordered_set<int> group_ids;
    for (int i = 0; i < n; i++)
    {
        if (closed.count(i))
        {
            continue;
        }

        group_ids.insert(uf.find(i));
    }

    return group_ids.size() == 1;
}

int main()
{
    freopen("closing.in", "r", stdin);
    freopen("closing.out", "w", stdout);

    int n, m;
    cin >> n >> m;

    unordered_map<int, vector<int>> adj_list;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj_list[u - 1].push_back(v - 1);
        adj_list[v - 1].push_back(u - 1);
    }

    vector<int> closing_order(n);
    for (int i = 0; i < n; i++)
    {
        cin >> closing_order[i];
        closing_order[i]--;
    }

    unordered_set<int> closed;
    if (is_connected(adj_list, n, closed))
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }

    for (int i = 0; i < n - 1; i++)
    {
        int p = closing_order[i];
        closed.insert(p);

        if (is_connected(adj_list, n, closed))
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }

    return 0;
}