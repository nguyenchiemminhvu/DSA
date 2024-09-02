/**
https://leetcode.com/problems/find-the-student-that-will-replace-the-chalk/description/


*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution
{
public:
    int chalkReplacer(vector<int>& chalk, int k)
    {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(NULL);
        std::cout.tie(NULL);

        long long sum = std::accumulate(chalk.begin(), chalk.end(), 0LL);
        k %= sum;

        for (long long i = 0; i < chalk.size(); i++)
        {
            if (k < chalk[i])
            {
                return i;
            }

            k -= chalk[i];
        }

        return 0;
    }
};

int main()
{
    Solution sol;
    std::vector<int> chalk = {3,4,1,2};
    int k = 25;
    std::cout << sol.chalkReplacer(chalk, k) << std::endl;
    return 0;
}