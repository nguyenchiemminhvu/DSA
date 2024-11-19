/**
https://leetcode.com/problems/count-vowel-strings-in-ranges/description/

You are given a 0-indexed array of strings words and a 2D array of integers queries.

Each query queries[i] = [li, ri] asks us to find the number of strings present in the range li to ri (both inclusive) of words that start and end with a vowel.

Return an array ans of size queries.length, where ans[i] is the answer to the ith query.

Note that the vowel letters are 'a', 'e', 'i', 'o', and 'u'.

Example 1:

Input: words = ["aba","bcb","ece","aa","e"], queries = [[0,2],[1,4],[1,1]]
Output: [2,3,0]
Explanation: The strings starting and ending with a vowel are "aba", "ece", "aa" and "e".
The answer to the query [0,2] is 2 (strings "aba" and "ece").
to query [1,4] is 3 (strings "ece", "aa", "e").
to query [1,1] is 0.
We return [2,3,0].

Example 2:

Input: words = ["a","e","i"], queries = [[0,2],[0,1],[2,2]]
Output: [3,2,1]
Explanation: Every string satisfies the conditions, so we return [3,2,1].

Constraints:

1 <= words.length <= 105
1 <= words[i].length <= 40
words[i] consists only of lowercase English letters.
sum(words[i].length) <= 3 * 105
1 <= queries.length <= 105
0 <= li <= ri < words.length
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
    vector<int> vowelStrings(vector<string>& words, vector<vector<int>>& queries)
    {
        std::vector<int> res;

        std::vector<int> sum(words.size() + 1, 0);
        for (int i = 0; i < words.size(); i++)
        {
            sum[i + 1] = (isVowel(words[i][0]) && isVowel(words[i].back()));
            sum[i + 1] += sum[i];
        }

        for (const std::vector<int>& query : queries)
        {
            res.push_back(sum[query[1] + 1] - sum[query[0]]);
        }

        return res;
    }
private:
    bool isVowel(char c)
    {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
};

int main()
{
    Solution sol;
    std::vector<std::string> words = {"aba","bcb","ece","aa","e"};
    std::vector<std::vector<int>> queries = {{0,2}, {1,4}, {1,1}};
    std::vector<int> res = sol.vowelStrings(words, queries);
    for (int n : res)
    {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    return 0;
}