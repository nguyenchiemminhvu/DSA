/**
https://leetcode.com/problems/optimal-partition-of-string/

Given a string s, partition the string into one or more substrings such that the characters in each substring are unique. That is, no letter appears in a single substring more than once.

Return the minimum number of substrings in such a partition.

Note that each character should belong to exactly one substring in a partition.

Example 1:

Input: s = "abacaba"
Output: 4
Explanation:
Two possible partitions are ("a","ba","cab","a") and ("ab","a","ca","ba").
It can be shown that 4 is the minimum number of substrings needed.

Example 2:

Input: s = "ssssss"
Output: 6
Explanation:
The only valid partition is ("s","s","s","s","s","s").

Constraints:

1 <= s.length <= 105
s consists of only English lowercase letters.
*/

#include <iostream>
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
    int partitionString(const string& s)
    {
        int partition = 1;

        int mask = 0;
        for (char c : s)
        {
            if ((mask & (1 << (c - 'a'))) == 0)
            {
                mask |= (1 << (c - 'a'));
            }
            else
            {
                partition++;
                mask = 0;
                mask |= (1 << (c - 'a'));
            }
        }

        return partition;
    }
};

int main()
{
    Solution sol;
    std::cout << sol.partitionString("abacaba") << std::endl;
    return 0;
}