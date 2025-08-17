/**
https://leetcode.com/problems/lexicographical-numbers/

Given an integer n, return all the numbers in the range [1, n] sorted in lexicographical order.
You must write an algorithm that runs in O(n) time and uses O(1) extra space. 

Example 1:

Input: n = 13
Output: [1,10,11,12,13,2,3,4,5,6,7,8,9]

Example 2:

Input: n = 2
Output: [1,2]
 

Constraints:

1 <= n <= 5 * 104
*/

#include <iostream>
#include <vector>

using namespace std;

auto bpsn = [](){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 'sk';
}();

class Solution
{
public:
    vector<int> lexicalOrder(int n)
    {
        std::vector<int> res;
        for (int i = 1; i <= 9; i++)
        {
            generating(n, i, res);
        }
        return res;
    }
private:
    void generating(int n, int cur, std::vector<int>& res)
    {
        if (cur > n)
        {
            return;
        }

        res.push_back(cur);
        for (int i = 0; i <= 9; i++)
        {
            generating(n, cur * 10 + i, res);
        }
    }
};

int main()
{
    Solution sol;
    std::vector<int> res = sol.lexicalOrder(100);
    for (int n : res)
    {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    return 0;
}