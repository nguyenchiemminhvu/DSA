/**
https://leetcode.com/problems/plates-between-candles/description/

There is a long table with a line of plates and candles arranged on top of it. You are given a 0-indexed string s consisting of characters '*' and '|' only, where a '*' represents a plate and a '|' represents a candle.

You are also given a 0-indexed 2D integer array queries where queries[i] = [lefti, righti] denotes the substring s[lefti...righti] (inclusive). For each query, you need to find the number of plates between candles that are in the substring. A plate is considered between candles if there is at least one candle to its left and at least one candle to its right in the substring.

For example, s = "||**||**|*", and a query [3, 8] denotes the substring "*||**|". The number of plates between candles in this substring is 2, as each of the two plates has at least one candle in the substring to its left and right.
Return an integer array answer where answer[i] is the answer to the ith query.

Example 1:

ex-1
Input: s = "**|**|***|", queries = [[2,5],[5,9]]
Output: [2,3]
Explanation:
- queries[0] has two plates between candles.
- queries[1] has three plates between candles.

Example 2:

ex-2
Input: s = "***|**|*****|**||**|*", queries = [[1,17],[4,5],[14,17],[5,11],[15,16]]
Output: [9,0,0,0,0]
Explanation:
- queries[0] has nine plates between candles.
- The other queries have zero plates between candles.

Constraints:

3 <= s.length <= 105
s consists of '*' and '|' characters.
1 <= queries.length <= 105
queries[i].length == 2
0 <= lefti <= righti < s.length
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
    vector<int> platesBetweenCandles(const string& s, vector<vector<int>>& queries)
    {
        std::vector<int> res;

        std::vector<int> sum(s.length() + 1, 0);
        std::vector<int> left_candles(s.length(), -1);
        std::vector<int> right_candles(s.length(), -1);
        int cur_candle = -1;
        for (int i = 0; i < s.length(); i++)
        {
            sum[i + 1] += sum[i] + (s[i] == '*');

            if (s[i] == '|')
            {
                cur_candle = i;
            }

            left_candles[i] = cur_candle;
        }

        cur_candle = -1;
        for (int i = s.length() - 1; i >= 0; i--)
        {
            if (s[i] == '|')
            {
                cur_candle = i;
            }

            right_candles[i] = cur_candle;
        }

        for (const std::vector<int>& query : queries)
        {
            int count = 0;
            int left = query[0];
            int right = query[1];
            int candle_left = right_candles[left];
            int candle_right = left_candles[right];

            if (candle_left != -1 && candle_right != -1 && candle_left <= candle_right)
            {
                count = (sum[candle_right + 1] - sum[candle_left]);
            }
            
            res.push_back(count);
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::string s = "**|**|***|";
    std::vector<std::vector<int>> queries = {{2, 5}, {5, 9}};
    std::vector<int> res = sol.platesBetweenCandles(s, queries);
    for (int i : res)
    {
        std::cout << i << " ";
    }
    return 0;
}