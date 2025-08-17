/**
https://leetcode.com/problems/report-spam-message/description/

 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    bool reportSpam(vector<string>& messages, vector<string>& banned)
    {
        std::unordered_set<std::string> set_banned(banned.begin(), banned.end());
        
        int count = 0;

        for (const std::string& message : messages)
        {
            std::stringstream ss(message);
            std::string temp;
            while (ss >> temp)
            {
                if (set_banned.find(temp) != set_banned.end())
                {
                    count++;
                }

                if (count >= 2)
                {
                    return true;
                }
            }
        }

        return false;
    }
};

int main()
{
    Solution sol;
    vector<string> messages = {"This is a spam message", "Another spam message here"};
    vector<string> banned = {"spam", "phishing"};
    std::cout << sol.reportSpam(messages, banned) << std::endl;
    return 0;
}