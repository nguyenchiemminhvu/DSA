/**
https://vjudge.net/contest/690982#problem/H

To help the cows with their spelling, Farmer John wants to fashion a number of wooden blocks, each embossed with a single letter of the alphabet. He wants to make sufficiently many blocks of each letter so that no matter which set of N words is exposed on the upward-facing boards, the cows will be able to spell all of these words using the blocks. For example, if N=3 and the words 'box', 'cat', and 'car' were facing upward, the cows would need at least one 'b' block, one 'o' block, one 'x' block, two 'c' blocks, two 'a' blocks, one 't' block, and one 'r' block.

Please help the Farmer John determine the minimum number of blocks for each letter of the alphabet that he needs to provide, so that irrespective of which face of each board is showing, the cows can spell all N visible words.
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    std::vector<int> blockGame(const std::vector<std::string>& upside, const std::vector<std::string>& downside)
    {
        std::vector<int> res(26, 0);

        for (int i = 0; i < upside.size(); i++)
        {
            std::vector<int> up_freq(26, 0);
            std::vector<int> down_freq(26, 0);

            for (char c : upside[i])
            {
                up_freq[c - 'a']++;
            }

            for (char c : downside[i])
            {
                down_freq[c - 'a']++;
            }

            for (int j = 0; j < 26; j++)
            {
                res[j] += std::max(up_freq[j], down_freq[j]);
            }
        }

        return res;
    }
};

int main()
{
    freopen("blocks.in", "r", stdin);
    freopen("blocks.out", "w", stdout);

    int n;
    std::cin >> n;
    std::vector<std::string> upside(n);
    std::vector<std::string> downside(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> upside[i] >> downside[i];
    }

    Solution sol;
    std::vector<int> res = sol.blockGame(upside, downside);
    for (int i = 0; i < 26; i++)
    {
        std::cout << res[i] << std::endl;
    }

    return 0;
}