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

void add_edge(unordered_map<int, vector<int>>& adj_list, int src, int dst)
{
    adj_list[src].push_back(dst);
    adj_list[dst].push_back(src);
}

void DFS(const unordered_map<int, vector<int>>& adj_list, int from, unordered_set<int>& visited, const unordered_set<int>& open_barns)
{
    visited.insert(from);
    for (int adj : adj_list.at(from))
    {
        if (visited.find(adj) == visited.end() && open_barns.find(adj) != open_barns.end())
        {
            DFS(adj_list, adj, visited, open_barns);
        }
    }
}

bool is_connected(const unordered_map<int, vector<int>>& adj_list, const unordered_set<int>& open_barns)
{
    if (open_barns.empty())
        return true;

    unordered_set<int> visited;
    DFS(adj_list, *open_barns.begin(), visited, open_barns);
    for (int barn : open_barns)
    {
        if (visited.find(barn) == visited.end())
        {
            return false;
        }
    }
    return true;
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
        add_edge(adj_list, u, v);
    }

    vector<int> closing_order(n);
    for (int i = 0; i < n; i++)
    {
        cin >> closing_order[i];
    }

    unordered_set<int> open_barns;
    for (int i = 1; i <= n; i++)
    {
        open_barns.insert(i);
    }

    if (is_connected(adj_list, open_barns))
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
        open_barns.erase(p);

        if (is_connected(adj_list, open_barns))
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }

        open_barns.insert(p);
    }

    return 0;
}