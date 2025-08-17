/**
https://leetcode.com/problems/minimum-number-of-operations-to-move-all-balls-to-each-box/

You have n boxes. You are given a binary string boxes of length n, where boxes[i] is '0' if the ith box is empty, and '1' if it contains one ball.

In one operation, you can move one ball from a box to an adjacent box. Box i is adjacent to box j if abs(i - j) == 1. Note that after doing so, there may be more than one ball in some boxes.

Return an array answer of size n, where answer[i] is the minimum number of operations needed to move all the balls to the ith box.

Each answer[i] is calculated considering the initial state of the boxes.

Example 1:

Input: boxes = "110"
Output: [1,1,3]
Explanation: The answer for each box is as follows:
1) First box: you will have to move one ball from the second box to the first box in one operation.
2) Second box: you will have to move one ball from the first box to the second box in one operation.
3) Third box: you will have to move one ball from the first box to the third box in two operations, and move one ball from the second box to the third box in one operation.

Example 2:

Input: boxes = "001011"
Output: [11,8,5,4,3,4]

Constraints:

n == boxes.length
1 <= n <= 2000
boxes[i] is either '0' or '1'.
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution 
{
public:
    vector<int> minOperations(const string& boxes) 
    {
        int n = boxes.length();
        vector<int> res(n, 0);

        int count = 0;
        int ops = 0;
        for (int i = 0; i < n; i++) 
        {
            res[i] += ops;
            if (boxes[i] == '1') 
                count++;
            ops += count;
        }

        // Backward pass
        count = 0;
        ops = 0;
        for (int i = n - 1; i >= 0; i--) 
        {
            res[i] += ops;
            if (boxes[i] == '1') 
                count++;
            ops += count;
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::cout << sol.minOperations("001011") << std::endl;
    return 0;
}