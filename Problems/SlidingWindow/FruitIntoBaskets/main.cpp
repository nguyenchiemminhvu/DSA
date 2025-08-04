// https://leetcode.com/problems/fruit-into-baskets/description

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    int totalFruit(vector<int>& fruits)
    {
        int n = fruits.size();
        int res = 0;
        int left = 0;
        int right = 0;
        std::unordered_map<int, int> freq;
        while (right < n)
        {
            freq[fruits[right]]++;
            while (freq.size() > 2)
            {
                freq[fruits[left]]--;
                if (freq[fruits[left]] <= 0)
                {
                    freq.erase(fruits[left]);
                }
                left++;
            }

            int total = 0;
            for (auto p : freq)
            {
                total += p.second;
            }
            res = std::max(res, total);

            right++;
        }

        return res;
    }
};

int main()
{
    Solution sol;
    vector<int> fruits = {1, 2, 1};
    cout << sol.totalFruit(fruits) << endl; // Output: 3

    fruits = {0, 1, 2, 2};
    cout << sol.totalFruit(fruits) << endl; // Output: 3

    fruits = {1, 2, 3, 2, 2};
    cout << sol.totalFruit(fruits) << endl; // Output: 4

    return 0;
}