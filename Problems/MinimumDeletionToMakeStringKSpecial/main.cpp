// https://leetcode.com/problems/minimum-deletions-to-make-string-k-special/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    int minimumDeletions(string word, int k)
    {
        std::vector<int> freq(26, 0);
        for (char c : word)
        {
            freq[c - 'a']++;
        }

        freq.erase(std::remove(freq.begin(), freq.end(), 0), freq.end());
        std::sort(freq.begin(), freq.end());
        if (freq.front() >= freq.back() - k)
        {
            return 0;
        }

        int res = INT_MAX;
        for (int base : freq)
        {
            int deletion = 0;
            for (int f : freq)
            {
                if (base > f)
                {
                    deletion += f;
                }
                else if (f > base + k)
                {
                    deletion += f - (base + k);
                }
            }

            res = std::min(res, deletion);
        }

        return res == INT_MAX ? 0 : res;
    }
};

int main()
{
    Solution sol;
    string word;
    int k;
    cin >> word >> k;
    int result = sol.minimumDeletions(word, k);
    cout << result << endl;
    return 0;
}