/**
https://vjudge.net/contest/690986#problem/B
https://usaco.org/index.php?page=viewproblem2&cpid=963
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution
{
public:
    int countPersistency(int k, const std::vector<std::vector<int>>& ranks)
    {
        std::unordered_map<int, std::unordered_set<int>> persistent_map;
        for (int i = 0; i < ranks[0].size(); i++)
        {
            for (int j = i + 1; j < ranks[0].size(); j++)
            {
                persistent_map[ranks[0][i]].insert(ranks[0][j]);
            }
        }

        for (int i = 1; i < k; i++)
        {
            for (int j = 0; j < ranks[i].size(); j++)
            {
                for (int l = j + 1; l < ranks[i].size(); l++)
                {
                    // if the cow ranks[i][l] is higher than ranks[i][j] in the previous session, but now it is lower
                    if (persistent_map[ranks[i][l]].find(ranks[i][j]) != persistent_map[ranks[i][l]].end())
                    {
                        // then remove the pair from the persistent map
                        persistent_map[ranks[i][l]].erase(ranks[i][j]);
                    }
                }
            }
        }

        int count_persistent = 0;
        for (auto it = persistent_map.begin(); it != persistent_map.end(); it++)
        {
            count_persistent += it->second.size();
        }
        return count_persistent;
    }
};

int main()
{
    freopen("gymnastics.in", "r", stdin);
    freopen("gymnastics.out", "w", stdout);

    int k, n;
    std::cin >> k >> n;
    std::vector<std::vector<int>> ranks(k, std::vector<int>(n));
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cin >> ranks[i][j];
        }
    }

    Solution sol;
    std::cout << sol.countPersistency(k, ranks) << std::endl;

    return 0;
}