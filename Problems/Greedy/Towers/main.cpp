/**
https://vjudge.net/contest/690988#problem/B
https://usaco.guide/problems/cses-1073-towers/solution

You are given n cubes in a certain order, and your task is to build towers using them. Whenever two cubes are one on top of the other, the upper cube must be smaller than the lower cube.

You must process the cubes in the given order. You can always either place the cube on top of an existing tower, or begin a new tower. What is the minimum possible number of towers?
 */

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Solution
{
public:
    int minimumTowers(const std::vector<int>& cubes)
    {
        std::multiset<int> towers;
        for (int i = 0; i < cubes.size(); i++)
        {
            auto it = towers.upper_bound(cubes[i]);
            if (it == towers.end())
            {
                // can not place this cube to the top of any current tower
                // build new tower from it
                towers.insert(cubes[i]);
            }
            else
            {
                // place this cube to the top of the smallest tower
                towers.erase(it);
                towers.insert(cubes[i]);
            }
        }

        return towers.size();
    }
};

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> cubes;
    for (int i = 0; i < n; i++)
    {
        int cube;
        std::cin >> cube;
        cubes.push_back(cube);
    }

    Solution sol;
    std::cout << sol.minimumTowers(cubes) << std::endl;

    return 0;
}