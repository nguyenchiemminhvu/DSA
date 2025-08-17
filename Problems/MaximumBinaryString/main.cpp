/**
https://leetcode.com/problems/maximum-binary-string-after-change/description/

You are given a binary string binary consisting of only 0's or 1's. You can apply each of the following operations any number of times:

Operation 1: If the number contains the substring "00", you can replace it with "10".
For example, "00010" -> "10010"
Operation 2: If the number contains the substring "10", you can replace it with "01".
For example, "00010" -> "00001"
Return the maximum binary string you can obtain after any number of operations. Binary string x is greater than binary string y if x's decimal representation is greater than y's decimal representation.

Example 1:

Input: binary = "000110"
Output: "111011"
Explanation: A valid transformation sequence can be:
"000110" -> "000101" 
"000101" -> "100101" 
"100101" -> "110101" 
"110101" -> "110011" 
"110011" -> "111011"

Example 2:

Input: binary = "01"
Output: "01"
Explanation: "01" cannot be transformed any further.

Constraints:

1 <= binary.length <= 105
binary consist of '0' and '1'.
*/

#include <iostream>
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
    string maximumBinaryString(const string& binary)
    {
        int n = binary.length();
        std::size_t first_zero_index = binary.find_first_of("0");
        if (first_zero_index == std::string::npos)
        {
            return binary;
        }

        int count_zeros = 0;
        for (int i = first_zero_index; i < n; ++i)
        {
            count_zeros += (binary[i] == '0');
        }

        std::string result = std::string(first_zero_index, '1') + // All 1s up to the first zero
                             std::string(count_zeros - 1, '1') + // All 1s except one zero
                             '0' +                          // The single zero
                             string(n - first_zero_index - count_zeros, '1'); // Remaining ones
        return result;
    }
};

int main()
{
    Solution sol;
    std::cout << sol.maximumBinaryString("000110") << std::endl;
    return 0;
}