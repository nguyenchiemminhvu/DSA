/**
https://leetcode.com/problems/time-needed-to-rearrange-a-binary-string/

You are given a binary string s. In one second, all occurrences of "01" are simultaneously replaced with "10". This process repeats until no occurrences of "01" exist.

Return the number of seconds needed to complete this process.

Example 1:

Input: s = "0110101"
Output: 4
Explanation: 
After one second, s becomes "1011010".
After another second, s becomes "1101100".
After the third second, s becomes "1110100".
After the fourth second, s becomes "1111000".
No occurrence of "01" exists any longer, and the process needed 4 seconds to complete,
so we return 4.

Example 2:

Input: s = "11100"
Output: 0
Explanation:
No occurrence of "01" exists in s, and the processes needed 0 seconds to complete,
so we return 0.

Constraints:

1 <= s.length <= 1000
s[i] is either '0' or '1'.

Follow up:

Can you solve this problem in O(n) time complexity?
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
    int secondsToRemoveOccurrences(string& s)
    {
        int count = 0;
        std::vector<int> index_01;
        do
        {
            index_01.clear();

            for (int i = 1; i < s.length(); i++)
            {
                if (s[i] == '1' && s[i - 1] == '0')
                {
                    index_01.push_back(i);
                }
            }

            for (int idx : index_01)
            {
                s[idx] = '0';
                s[idx - 1] = '1';
            }
            
            count += (!index_01.empty());
        } while (!index_01.empty());
        
        return count;
    }
};

int main()
{
    Solution sol;
    std::string s = "0110101";
    std::cout << sol.secondsToRemoveOccurrences(s) << std::endl;
    return 0;
}