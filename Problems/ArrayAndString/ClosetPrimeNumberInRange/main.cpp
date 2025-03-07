/**
https://leetcode.com/problems/closest-prime-numbers-in-range

Given two positive integers left and right, find the two integers num1 and num2 such that:

left <= num1 < num2 <= right .
Both num1 and num2 are prime numbers.
num2 - num1 is the minimum amongst all other pairs satisfying the above conditions.
Return the positive integer array ans = [num1, num2]. If there are multiple pairs satisfying these conditions, return the one with the smallest num1 value. If no such numbers exist, return [-1, -1].

Example 1:

Input: left = 10, right = 19
Output: [11,13]
Explanation: The prime numbers between 10 and 19 are 11, 13, 17, and 19.
The closest gap between any pair is 2, which can be achieved by [11,13] or [17,19].
Since 11 is smaller than 17, we return the first pair.

Example 2:

Input: left = 4, right = 6
Output: [-1,-1]
Explanation: There exists only one prime number in the given range, so the conditions cannot be satisfied.

Constraints:

1 <= left <= right <= 106
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    vector<int> closestPrimes(int left, int right)
    {
        // Sieve of Eratosthenes
        std::vector<bool> prime_table(right + 1, true);
        prime_table[0] = prime_table[1] = false;
        for (int p = 2; p * p <= right; p++)
        {
            if (prime_table[p])
            {
                for (int i = p * p; i <= right; i += p)
                {
                    prime_table[i] = false;
                }
            }
        }

        std::vector<int> res = {-1, -1};
        int prev = INT_MIN;
        int min_diff = INT_MAX;
        for (int i = left; i <= right; i++)
        {
            if (prime_table[i])
            {
                if (prev == INT_MIN)
                {
                    prev = i;
                }
                else
                {
                    if (i - prev < min_diff)
                    {
                        min_diff = i - prev;
                        res = {prev, i};
                    }
                    prev = i;
                }
            }
        }

        return res;
    }
};

int main()
{
    Solution sol;
    int left, right;
    cout << "Enter the range (left and right): ";
    cin >> left >> right;

    vector<int> result = sol.closestPrimes(left, right);
    if (result[0] == -1)
    {
        cout << "No prime pairs found in the given range." << endl;
    }
    else
    {
        cout << "The closest prime numbers in the range are: " << result[0] << " and " << result[1] << endl;
    }
    return 0;
}