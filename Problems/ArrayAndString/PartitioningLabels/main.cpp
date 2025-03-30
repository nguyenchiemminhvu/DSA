/**
https://leetcode.com/problems/partition-labels/description/
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    vector<int> partitionLabels(string& s)
    {
        std::vector<int> res;

        int n = s.length();
        std::unordered_map<char, int> last_idx;
        for (int i = 0; i < n; i++)
        {
            last_idx[s[i]] = i;
        }

        int left = 0;
        int i = 0;
        while (true)
        {
            int right = last_idx[s[i]];
            while (i < right)
            {
                right = std::max(right, last_idx[s[i]]);
                i++;
            }

            res.push_back(right - left + 1);
            i++;
            left = i;

            if (right == n - 1)
            {
                break;
            }
        }

        return res;
    }
};

int main()
{
    Solution sol;
    string s = "ababcbacadefegdehijhklij";
    vector<int> res = sol.partitionLabels(s);
    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << " ";
    }
    cout << endl;
    s = "eccbbbbdec";
    res = sol.partitionLabels(s);
    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << " ";
    }
    cout << endl;
    s = "caedbdedda";
    res = sol.partitionLabels(s);
    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << " ";
    }
    cout << endl;
    s = "ababcbacadefegdehijhklij";
    res = sol.partitionLabels(s);
    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << " ";
    }
    cout << endl;
    s = "a";
    res = sol.partitionLabels(s);
    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << " ";
    }
    cout << endl;
    s = "ab";
    res = sol.partitionLabels(s);
    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << " ";
    }
    cout << endl;
    s = "abc";
    res = sol.partitionLabels(s);
    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << " ";
    }
    cout << endl;
    return 0;
}