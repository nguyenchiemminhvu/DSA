// https://leetcode.com/problems/using-a-robot-to-print-the-lexicographically-smallest-string/description/

#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    std::string robotWithString(const std::string& s)
    {
        std::string res;
        std::stack<char> t;
        size_t last_idx = 0U;
        int n = s.length();

        std::vector<char> min_suffix(n + 1);
        min_suffix[n] = min_suffix[n - 1] = s[n - 1];
        for (int i = n - 2; i >= 0; i--)
        {
            min_suffix[i] = std::min(s[i], min_suffix[i + 1]);
        }

        for (int i = 0; i < n; i++)
        {
            t.push(s[i]);

            while (!t.empty() && t.top() <= min_suffix[i + 1])
            {
                res += t.top();
                t.pop();
            }
        }

        while (!t.empty())
        {
            res += t.top();
            t.pop();
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::string s;
    std::cin >> s;
    std::cout << sol.robotWithString(s) << std::endl;
    return 0;
}