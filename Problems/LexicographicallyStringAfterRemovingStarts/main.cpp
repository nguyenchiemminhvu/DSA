// https://leetcode.com/problems/lexicographically-minimum-string-after-removing-stars/description/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
};

class Solution
{
public:
    string clearStars(string& s)
    {
        int n = s.length();
        std::vector<std::deque<std::pair<char, int>>> stacks(26);
        int i = 0;
        for (char c : s)
        {
            if (c == '*')
            {
                for (int i = 0; i < 26; i++)
                {
                    if (stacks[i].empty())
                    {
                        continue;
                    }

                    stacks[i].pop_back();
                    break;
                }
            }
            else
            {
                stacks[c - 'a'].push_back({c, i});
            }

            i++;
        }

        std::string res(n, ' ');
        for (int i = 0; i < 26; i++)
        {
            for (auto& p : stacks[i])
            {
                res[p.second] = p.first;
            }
        }

        res.erase(std::remove(res.begin(), res.end(), ' '), res.end());
        return res;
    }
};

int main()
{
    Solution sol;
    string s;
    cin >> s;
    string result = sol.clearStars(s);
    cout << result << endl;
    return 0;
}