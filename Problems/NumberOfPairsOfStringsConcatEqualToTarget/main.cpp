/**
https://leetcode.com/problems/number-of-pairs-of-strings-with-concatenation-equal-to-target/

Given an array of digit strings nums and a digit string target, return the number of pairs of indices (i, j) (where i != j) such that the concatenation of nums[i] + nums[j] equals target.

Example 1:

Input: nums = ["777","7","77","77"], target = "7777"
Output: 4
Explanation: Valid pairs are:
- (0, 1): "777" + "7"
- (1, 0): "7" + "777"
- (2, 3): "77" + "77"
- (3, 2): "77" + "77"

Example 2:

Input: nums = ["123","4","12","34"], target = "1234"
Output: 2
Explanation: Valid pairs are:
- (0, 1): "123" + "4"
- (2, 3): "12" + "34"

Example 3:

Input: nums = ["1","1","1"], target = "11"
Output: 6
Explanation: Valid pairs are:
- (0, 1): "1" + "1"
- (1, 0): "1" + "1"
- (0, 2): "1" + "1"
- (2, 0): "1" + "1"
- (1, 2): "1" + "1"
- (2, 1): "1" + "1"

Constraints:

2 <= nums.length <= 100
1 <= nums[i].length <= 100
2 <= target.length <= 100
nums[i] and target consist of digits.
nums[i] and target do not have leading zeros.
 */

#include <iostream>
#include <unordered_map>
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
    int numOfPairs(vector<string>& nums, const string& target)
    {
        int res = 0;
        std::unordered_map<std::string, int> counter;
        for (const std::string& num: nums)
        {
            counter[num]++;
        }

        for (const std::string& num : nums)
        {
            if (num.length() >= target.length())
            {
                continue;
            }

            if (target.compare(0, num.length(), num) == 0)
            {
                std::string suffix(target.begin() + num.length(), target.end());
                if (counter.find(suffix) != counter.end())
                {
                    res += counter[suffix];
                    if (suffix == num)
                    {
                        res--;
                    }
                }
            }
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::vector<std::string> nums = {
        "777","7","77","77"
    };
    std::string target = "7777";
    std::cout << sol.numOfPairs(nums, target) << std::endl;
    return 0;
}