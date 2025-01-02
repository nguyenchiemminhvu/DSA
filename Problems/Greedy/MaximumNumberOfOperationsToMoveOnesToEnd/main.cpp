/**
https://leetcode.com/problems/maximum-number-of-operations-to-move-ones-to-the-end/description/
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
    int maxOperations(const string& s)
    {
        int res = 0;
        bool has_zero = false;
        int count_one = 0;

        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == '0')
            {
                has_zero = true;
            }
            else
            {
                if (has_zero)
                {
                    res += count_one;
                    has_zero = false;
                }
                count_one++;
            }
        }

        if (has_zero)
        {
            res += count_one;
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::cout << sol.maxOperations("010010010") << std::endl;
    return 0;
}