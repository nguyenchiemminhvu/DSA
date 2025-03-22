/**
https://leetcode.com/problems/construct-string-with-repeat-limit/
 */

#include <iostream>
#include <vector>
#include <string>
#include <deque>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    string repeatLimitedString(string& s, int limited)
    {
        std::string res;

        std::vector<int> freq(26, 0);
        for (char c : s)
        {
            freq[c - 'a']++;
        }

        std::deque<std::pair<char, int>> bank;
        for (char c = 'z'; c >= 'a'; c--)
        {
            if (freq[c - 'a'] > 0)
            {
                bank.push_back({c, freq[c - 'a']});
            }
        }

        while (!bank.empty())
        {
            if (bank.size() == 1)
            {
                res += std::string(std::min(bank[0].second, limited), bank[0].first);
                break;
            }
            else
            {
                std::pair<char, int> first = bank.front();
                bank.pop_front();

                std::pair<char, int> second = bank.front();
                bank.pop_front();

                if (first.first < second.first)
                {
                    res.push_back(first.first);
                    first.second--;
                }
                else
                {
                    res += std::string(std::min(limited, first.second), first.first);
                    first.second -= std::min(limited, first.second);
                }

                if (first.second > 0)
                {
                    bank.push_front(first);
                }
                bank.push_front(second);
            }
        }

        return res;
    }
};

int main()
{
    Solution sol;
    string s;
    int limited;
    cout << "Enter the string: ";
    cin >> s;
    cout << "Enter the repeat limit: ";
    cin >> limited;

    string result = sol.repeatLimitedString(s, limited);
    cout << "Resulting string: " << result << endl;
    return 0;
}