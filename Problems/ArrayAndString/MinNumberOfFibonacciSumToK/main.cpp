/**
https://leetcode.com/problems/find-the-minimum-number-of-fibonacci-numbers-whose-sum-is-k/description/

Given an integer k, return the minimum number of Fibonacci numbers whose sum is equal to k. The same Fibonacci number can be used multiple times.

The Fibonacci numbers are defined as:

F1 = 1
F2 = 1
Fn = Fn-1 + Fn-2 for n > 2.
It is guaranteed that for the given constraints we can always find such Fibonacci numbers that sum up to k.

Example 1:

Input: k = 7
Output: 2 
Explanation: The Fibonacci numbers are: 1, 1, 2, 3, 5, 8, 13, ... 
For k = 7 we can use 2 + 5 = 7.
Example 2:

Input: k = 10
Output: 2 
Explanation: For k = 10 we can use 2 + 8 = 10.
Example 3:

Input: k = 19
Output: 3 
Explanation: For k = 19 we can use 1 + 5 + 13 = 19.

Constraints:

1 <= k <= 109
*/

#include <iostream>
#include <vector>

class Solution
{
public:
    int findMinFibonacciNumbers(int k)
    {
        const std::vector<int> fibonacci = {
            1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 
            1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 
            121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 
            3524578, 5702887, 9227465, 14930352, 24157817, 39088169, 
            63245986, 102334155, 165580141, 267914296, 433494437, 701408733
        };

        int count = 0;
        int index = fibonacci.size() - 1;

        while (k > 0)
        {
            // Use the largest Fibonacci number less than or equal to k
            if (fibonacci[index] <= k)
            {
                k -= fibonacci[index];
                ++count;
            }
            // Move to the next smaller Fibonacci number
            --index;
        }

        return count;
    }
};

int main()
{
    Solution sol;
    std::cout << sol.findMinFibonacciNumbers(19) << std::endl;
    return 0;
}