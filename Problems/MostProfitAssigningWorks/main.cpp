/**
https://leetcode.com/problems/most-profit-assigning-work/description/


*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <tuple>
#include <climits>

using namespace std;

static bool init = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return true;
}();

class Solution
{
public:
    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker)
    {
        vector<tuple<int, int>> jobs;
        for (int i = 0; i < difficulty.size(); ++i)
        {
            jobs.emplace_back(difficulty[i], profit[i]);
        }

        sort(jobs.begin(), jobs.end());

        int maxProfitSoFar = 0;
        for (int i = 0; i < jobs.size(); ++i) {
            maxProfitSoFar = max(maxProfitSoFar, get<1>(jobs[i]));
            jobs[i] = make_tuple(get<0>(jobs[i]), maxProfitSoFar);
        }

        sort(worker.begin(), worker.end());

        int totalProfit = 0;
        for (int w : worker)
        {
            auto it = upper_bound(jobs.begin(), jobs.end(), make_tuple(w, INT_MAX));
            if (it != jobs.begin())
            {
                --it;
                totalProfit += get<1>(*it);
            }
        }

        return totalProfit;
    }
};

int main()
{
    Solution sol;
    std::vector<int> diff = {2,4,6,8,10};
    std::vector<int> pro = {10,20,30,40,50};
    std::vector<int> workers = {4,5,6,7};
    std::cout << sol.maxProfitAssignment(diff, pro, workers) << std::endl;
    return 0;
}