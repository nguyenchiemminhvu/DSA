/**
https://leetcode.com/problems/minimum-cost-to-convert-string-i/description/

You are given two 0-indexed strings source and target, both of length n and consisting of lowercase English letters. You are also given two 0-indexed character arrays original and changed, and an integer array cost, where cost[i] represents the cost of changing the character original[i] to the character changed[i].

You start with the string source. In one operation, you can pick a character x from the string and change it to the character y at a cost of z if there exists any index j such that cost[j] == z, original[j] == x, and changed[j] == y.

Return the minimum cost to convert the string source to the string target using any number of operations. If it is impossible to convert source to target, return -1.

Note that there may exist indices i, j such that original[j] == original[i] and changed[j] == changed[i].

Example 1:

Input: source = "abcd", target = "acbe", original = ["a","b","c","c","e","d"], changed = ["b","c","b","e","b","e"], cost = [2,5,5,1,2,20]
Output: 28
Explanation: To convert the string "abcd" to string "acbe":
- Change value at index 1 from 'b' to 'c' at a cost of 5.
- Change value at index 2 from 'c' to 'e' at a cost of 1.
- Change value at index 2 from 'e' to 'b' at a cost of 2.
- Change value at index 3 from 'd' to 'e' at a cost of 20.
The total cost incurred is 5 + 1 + 2 + 20 = 28.
It can be shown that this is the minimum possible cost.

Example 2:

Input: source = "aaaa", target = "bbbb", original = ["a","c"], changed = ["c","b"], cost = [1,2]
Output: 12
Explanation: To change the character 'a' to 'b' change the character 'a' to 'c' at a cost of 1, followed by changing the character 'c' to 'b' at a cost of 2, for a total cost of 1 + 2 = 3. To change all occurrences of 'a' to 'b', a total cost of 3 * 4 = 12 is incurred.

Example 3:

Input: source = "abcd", target = "abce", original = ["a"], changed = ["e"], cost = [10000]
Output: -1
Explanation: It is impossible to convert source to target because the value at index 3 cannot be changed from 'd' to 'e'.

Constraints:

1 <= source.length == target.length <= 105
source, target consist of lowercase English letters.
1 <= cost.length == original.length == changed.length <= 2000
original[i], changed[i] are lowercase English letters.
1 <= cost[i] <= 106
original[i] != changed[i]
*/

#include <iostream>
#include <climits>
#include <vector>
#include <string>

class Solution 
{
public:
    long long minimumCost(const std::string& source
                        , const std::string& target
                        , std::vector<char>& original
                        , std::vector<char>& changed
                        , std::vector<int>& cost)
    {
        long long res = 0;

        std::vector<std::vector<int>> min_cost(26, std::vector<int>(26, INT_MAX));
        
        for (int i = 0; i < 26; i++)
        {
            min_cost[i][i] = 0;
        }

        for (int i = 0; i < original.size(); i++)
        {
            min_cost[original[i] - 'a'][changed[i] - 'a'] = std::min(min_cost[original[i] - 'a'][changed[i] - 'a'], cost[i]);
        }

        for (int inter = 0; inter < 26; inter++)
        {
            for (int from = 0; from < 26; from++)
            {
                if (min_cost[from][inter] == INT_MAX)
                {
                    continue;
                }

                for (int to = 0; to < 26; to++)
                {
                    if (min_cost[inter][to] == INT_MAX)
                    {
                        continue;
                    }

                    if (min_cost[from][inter] + min_cost[inter][to] < min_cost[from][to])
                    {
                        min_cost[from][to] = min_cost[from][inter] + min_cost[inter][to];
                    }
                }
            }
        }

        for (int i = 0; i < source.length(); i++)
        {
            if (min_cost[source[i] - 'a'][target[i] - 'a'] != INT_MAX)
            {
                res += min_cost[source[i] - 'a'][target[i] - 'a'];
            }
            else
            {
                return -1;
            }
        }

        return res;
    }
};

int main()
{
    Solution sol;
    
    std::string source = "abcd";
    std::string target = "acbe";
    std::vector<char> original = {'a','b','c','c','e','d'};
    std::vector<char> changed = {'b','c','b','e','b','e'};
    std::vector<int> cost = {2,5,5,1,2,20};

    std::cout << sol.minimumCost(source, target, original, changed, cost) << std::endl;
    return 0;
}