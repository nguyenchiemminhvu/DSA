/**
https://leetcode.com/problems/solving-questions-with-brainpower/description/
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    long long mostPoints(vector<vector<int>>& questions)
    {
        std::vector<long long> mem(questions.size() + 1, -1);
        return solve_dp(questions, 0, mem);
    }
private:
    long long solve_dp(const std::vector<std::vector<int>>& quests, int i, std::vector<long long>& mem)
    {
        if (i >= quests.size())
        {
            return 0LL;
        }

        if (mem[i] != -1)
        {
            return mem[i];
        }

        long long points = 0LL;
        points = std::max(
            solve_dp(quests, i + 1, mem),
            quests[i][0] + solve_dp(quests, i + quests[i][1] + 1, mem)
        );

        mem[i] = points;

        return points;
    }
};

int main()
{
    Solution sol;
    std::vector<std::vector<int>> questions = {
        {3, 2},
        {4, 3},
        {4, 4},
        {2, 5}
    };
    std::cout << sol.mostPoints(questions) << std::endl; // 7
    questions = {
        {1, 1},
        {2, 2},
        {3, 3},
        {4, 4}
    };
    std::cout << sol.mostPoints(questions) << std::endl; // 10
    return 0;
}