/**
You are given an integer num. You can swap two digits at most once to get the maximum valued number.

Return the maximum valued number you can get.

Example 1:

Input: num = 2736
Output: 7236
Explanation: Swap the number 2 and the number 7.

Example 2:

Input: num = 9973
Output: 9973
Explanation: No swap.

Constraints:

0 <= num <= 10^8
*/

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class Solution
{
public:
    int maximumSwap(int num)
    {
        std::string s = std::to_string(num);
        int n = s.length();

        int last[10] = {0};
        for (int i = 0; i < n; i++)
        {
            last[s[i] - '0'] = i;
        }

        for (int i = 0; i < n; i++)
        {
            for (int d = 9; d > s[i] - '0'; d--)
            {
                if (last[d] > i)
                {
                    std::swap(s[i], s[last[d]]);
                    return std::stoi(s);
                }
            }
        }

        return num;
    }
};

int main()
{
	Solution sol;
	std::cout << sol.maximumSwap(7993) << std::endl;
	return 0;
}
