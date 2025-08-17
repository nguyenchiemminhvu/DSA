/**
https://leetcode.com/problems/steps-to-make-array-non-decreasing/
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

class Solution
{
public:
    int totalSteps(vector<int>& nums)
    {
        int res = 0;

        std::stack<std::pair<int, int>> st;
        for (int n : nums)
        {
            int steps = 0;
            while (!st.empty() && n >= st.top().first)
            {
                steps = std::max(steps, st.top().second);
                st.pop();
            }

            if (st.empty())
            {
                steps = 0;
            }
            else
            {
                steps++;
            }

            res = std::max(res, steps);
            st.push({n, steps});
        }

        return res;    
    }
};

int main()
{
    Solution s;
    vector<int> nums = {5, 1, 3, 4, 2};
    cout << s.totalSteps(nums) << endl;
    return 0;
}