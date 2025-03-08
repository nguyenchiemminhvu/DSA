/**
https://vjudge.net/contest/691174#problem/E
https://usaco.org/index.php?page=viewproblem2&cpid=1182
 */

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

class Solution
{
public:
    int min_operations(long long a, long long b)
    {
        if (a == b) return 0;
    
        std::queue<pair<long long, int>> q;
        std::unordered_set<long long> visited;
        
        q.push({a, 0});
        visited.insert(a);
        
        while (!q.empty())
        {
            std::pair<long long, int> cur = q.front();
            q.pop();

            long long current = cur.first;
            int steps = cur.second;
            
            std::vector<long long> nextOps = {current * 2, current + 1};
            if (current % 2 == 0)
            {
                nextOps.push_back(current / 2);
            }
            
            for (long long next : nextOps)
            {
                if (next == b) return steps + 1;
                if (next > 0 && visited.find(next) == visited.end())
                {
                    visited.insert(next);
                    q.push({next, steps + 1});
                }
            }
        }
        
        return -1; // Should never reach here
    }
};

int main()
{
    int n;
    std::cin >> n;

    Solution sol;
    for (int i = 0; i < n; i++)
    {
        int a, b;
        std::cin >> a >> b;
        std::cout << sol.min_operations(a, b) << std::endl;
    }

    return 0;
}