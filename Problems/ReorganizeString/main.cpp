/**
https://leetcode.com/problems/reorganize-string/

Given a string s, rearrange the characters of s so that any two adjacent characters are not the same.

Return any possible rearrangement of s or return "" if not possible.

Example 1:

Input: s = "aab"
Output: "aba"
Example 2:

Input: s = "aaab"
Output: ""

Constraints:

1 <= s.length <= 500
s consists of lowercase English letters.
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

class Solution
{
public:
    string reorganizeString(const string& s)
    {
        std::string res;

        std::unordered_map<char, int> freq;
        for (char c : s)
        {
            freq[c]++;
        }

        std::priority_queue<std::pair<int, char>> pq;
        for (const auto& p : freq)
        {
            pq.push({p.second, p.first});
        }

        if (pq.top().first > ((s.length() + 1) / 2))
        {
            return res;
        }

        while (pq.size() > 1)
        {
            std::pair<int, char> mostFreq = pq.top(); pq.pop();
            std::pair<int, char> secondFreq = pq.top(); pq.pop();
            res += mostFreq.second;
            res += secondFreq.second;
            mostFreq.first--;
            secondFreq.first--;

            if (mostFreq.first > 0)
            {
                pq.push(mostFreq);
            }

            if (secondFreq.first > 0)
            {
                pq.push(secondFreq);
            }
        }

        if (!pq.empty())
        {
            res += pq.top().second;
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::cout << sol.reorganizeString("aab") << std::endl;
    return 0;
}