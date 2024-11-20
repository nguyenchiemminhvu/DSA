/**
https://leetcode.com/problems/split-array-into-fibonacci-sequence/description/

You are given a string of digits num, such as "123456579". We can split it into a Fibonacci-like sequence [123, 456, 579].

Formally, a Fibonacci-like sequence is a list f of non-negative integers such that:

0 <= f[i] < 231, (that is, each integer fits in a 32-bit signed integer type),
f.length >= 3, and
f[i] + f[i + 1] == f[i + 2] for all 0 <= i < f.length - 2.
Note that when splitting the string into pieces, each piece must not have extra leading zeroes, except if the piece is the number 0 itself.

Return any Fibonacci-like sequence split from num, or return [] if it cannot be done.

Example 1:

Input: num = "1101111"
Output: [11,0,11,11]
Explanation: The output [110, 1, 111] would also be accepted.

Example 2:

Input: num = "112358130"
Output: []
Explanation: The task is impossible.

Example 3:

Input: num = "0123"
Output: []
Explanation: Leading zeroes are not allowed, so "01", "2", "3" is not valid.

Constraints:

1 <= num.length <= 200
num contains only digits.
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <climits>

using namespace std;

class Solution
{
public:
    vector<int> splitIntoFibonacci(const string& num)
    {
        std::vector<int> res;
        if (backtracking(num, 0, res))
            return res;
        return {};
    }
private:
    bool backtracking(const std::string& num, int idx, std::vector<int>& sequence)
    {
        if (idx >= num.length() && sequence.size() >= 3)
        {
            return true;
        }
        
        long long cur_val = 0LL;
        for (int i = idx; i < num.length(); i++)
        {
            // prevent leading zeros
            if (num[idx] == '0' && i > idx)
            {
                break;
            }

            cur_val = cur_val * 10 + (num[i] - '0');

            if (cur_val > INT_MAX)
            {
                break;
            }

            if (sequence.size() < 2 || cur_val == (long long)sequence[sequence.size() - 1] + sequence[sequence.size() - 2])
            {
                sequence.push_back(cur_val);
                if (backtracking(num, i + 1, sequence))
                {
                    return true;
                }
                sequence.pop_back();
            }
            else if (sequence.size() >= 2 && cur_val > (long long)sequence[sequence.size() - 1] + sequence[sequence.size() - 2])
            {
                break;
            }
        }

        return false;
    }
};

int main()
{
    Solution sol;
    std::vector<int> res = sol.splitIntoFibonacci("1101111");
    for (int n : res)
    {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    return 0;
}