/**
https://leetcode.com/problems/count-the-number-of-complete-components/description/
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class DSU
{
private:
    std::vector<int> parent, rank;

public:
    DSU(int n)
    {
        parent.resize(n);
        rank.resize(n, 1);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void union_sets(int a, int b)
    {
        int rootA = find(a);
        int rootB = find(b);
        
        if (rootA != rootB)
        {
            if (rank[rootA] > rank[rootB])
                parent[rootB] = rootA;
            else if (rank[rootA] < rank[rootB])
                parent[rootA] = rootB;
            else
            {
                parent[rootB] = rootA;
                rank[rootA]++;
            }
        }
    }

    bool connected(int a, int b)
    {
        return find(a) == find(b);
    }
};

class Solution
{
public:
    int countCompleteComponents(int n, vector<vector<int>>& edges)
    {
        DSU dsu(n);
        std::unordered_map<int, int> edge_count;
        std::unordered_map<int, int> component_size;
        for (const std::vector<int>& edge : edges)
        {
            dsu.union_sets(edge[0], edge[1]);
        }

        for (int i = 0; i < n; i++)
        {
            component_size[dsu.find(i)]++;
        }

        for (const std::vector<int>& edge : edges)
        {
            edge_count[dsu.find(edge[0])]++;
        }

        int res = 0;
        for (const auto& [root, size] : component_size)
        {
            if (edge_count[root] == size * (size - 1) / 2)
            {
                res++;
            }
        }

        return res;
    }
};

int main()
{
    Solution sol;
    int n;
    cout << "Enter the number of nodes: ";
    cin >> n;

    int m;
    cout << "Enter the number of edges: ";
    cin >> m;

    vector<vector<int>> edges(m, vector<int>(2));
    cout << "Enter the edges (u v):" << endl;
    for (int i = 0; i < m; ++i)
    {
        cin >> edges[i][0] >> edges[i][1];
    }

    int result = sol.countCompleteComponents(n, edges);
    cout << "The number of complete components is: " << result << endl;
    return 0;
}