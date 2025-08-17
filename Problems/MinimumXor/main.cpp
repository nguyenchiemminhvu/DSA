/**
https://leetcode.com/problems/minimize-xor/description/

Given two positive integers num1 and num2, find the positive integer x such that:

x has the same number of set bits as num2, and
The value x XOR num1 is minimal.
Note that XOR is the bitwise XOR operation.

Return the integer x. The test cases are generated such that x is uniquely determined.

The number of set bits of an integer is the number of 1's in its binary representation.

Example 1:

Input: num1 = 3, num2 = 5
Output: 3
Explanation:
The binary representations of num1 and num2 are 0011 and 0101, respectively.
The integer 3 has the same number of set bits as num2, and the value 3 XOR 3 = 0 is minimal.

Example 2:

Input: num1 = 1, num2 = 12
Output: 3
Explanation:
The binary representations of num1 and num2 are 0001 and 1100, respectively.
The integer 3 has the same number of set bits as num2, and the value 3 XOR 1 = 2 is minimal.

Constraints:

1 <= num1, num2 <= 109
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int minimizeXor(int num1, int num2)
    {
        int res = 0;

        int num_set_bit = __builtin_popcount(num2);

        std::vector<int> bits(32, 0);
        for (int i = 0; i < 32; i++)
        {
            bits[i] = (num1 >> i) & 1;
        }

        std::vector<bool> visited(32, false);
        for (int i = 31; i >= 0 && num_set_bit > 0; i--)
        {
            if (bits[i])
            {
                res |= (1 << i);
                bits[i] = 0;
                visited[i] = true;
                num_set_bit--;
            }
        }

        for (int i = 0; i < 32 && num_set_bit > 0; i++)
        {
            if (!visited[i] && bits[i] == 0)
            {
                res |= (1 << i);
                bits[i] = 1;
                visited[i] = true;
                num_set_bit--;
            }
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::cout << sol.minimizeXor(3, 5) << std::endl;
    return 0;
}