/**
https://leetcode.com/problems/minimum-cost-to-reach-every-position/description/
 */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution
{
public:
    vector<int> minCosts(vector<int>& cost)
    {
        std::vector<int> res(cost.size(), 0);

        std::stack<int> st;
        for (int i = 0; i < cost.size(); i++)
        {
            if (st.empty())
            {
                st.push(i);
            }
            else
            {
                if (cost[i] < cost[st.top()])
                {
                    st.push(i);
                }
            }
        }

        int right = cost.size();
        while (!st.empty())
        {
            int left = st.top();
            st.pop();
            for (int i = left; i < right; i++)
            {
                res[i] = cost[left];
            }
            right = left;
        }

        return res;
    }
};

int main()
{
    Solution s;
    vector<int> cost = {1, 2, 3, 4, 5};
    vector<int> res = s.minCosts(cost);
    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << " ";
    }
    cout << endl;
    return 0;
}