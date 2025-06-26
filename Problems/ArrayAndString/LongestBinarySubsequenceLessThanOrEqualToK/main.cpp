// https://leetcode.com/problems/longest-binary-subsequence-less-than-or-equal-to-k/description/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return 0;
}();

class Solution
{
public:
    int longestSubsequence(string& s, int k)
    {
        int res = 0;
        uint64_t val = 0LL;
        std::reverse(s.begin(), s.end());
        int right_most = right_most_set_bit_pos(k);
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == '0')
            {
                res++;
            }
            else
            {
                if (i <= right_most && val + (1LL << i) <= k)
                {
                    val += (1 << i);
                    res++;
                }
            }
        }

        return res;
    }
private:
    int right_most_set_bit_pos(int val)
    {
        if (val == 0)
        {
            return 0;
        }

        int res = 0;
        while (val)
        {
            val >>= 1;
            res++;
        }
        return res;
    }
};

int main()
{
    Solution sol;
    string s;
    int k;
    cin >> s >> k;
    int result = sol.longestSubsequence(s, k);
    cout << result << endl;
    return 0;
}