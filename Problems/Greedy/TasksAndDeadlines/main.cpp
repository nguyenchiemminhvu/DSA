/**
https://vjudge.net/contest/690988#problem/A

You have to process n tasks. Each task has a duration and a deadline, and you will process the tasks in some order one after another. Your reward for a task is d−f where d is its deadline and f is your finishing time. (The starting time is 0, and you have to process all tasks even if a task would yield negative reward.)

What is your maximum reward if you act optimally?
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    long long solve(std::vector<std::vector<long long>>& tasks)
    {
        std::sort(tasks.begin(), tasks.end(), [](const auto& a, const auto& b) {
            if (a[0] < b[0])
                return true;
            if (a[0] > b[0])
                return false;
            return a[1] < b[1];
        });

        long long benefit = 0;
        long long timestamp = 0;
        for (const std::vector<long long>& task : tasks)
        {
            timestamp += task[0];
            benefit += (task[1] - timestamp);
        }
        return benefit;
    }
};

int main()
{
    long long n;
    std::cin >> n;
    std::vector<std::vector<long long>> tasks(n);
    for (long long i = 0; i < n; i++)
    {
        int dur;
        int dead;
        std::cin >> dur >> dead;
        tasks[i].push_back(dur);
        tasks[i].push_back(dead);
    }

    Solution sol;
    std::cout << sol.solve(tasks) << std::endl;

    return 0;
}