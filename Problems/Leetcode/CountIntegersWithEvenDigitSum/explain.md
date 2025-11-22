## Problem

https://leetcode.com/problems/count-integers-with-even-digit-sum/description/

```
Given a positive integer num, return the number of positive integers less than or equal to num whose digit sums are even.

The digit sum of a positive integer is the sum of all its digits.

Example 1:

Input: num = 4
Output: 2
Explanation:
The only integers less than or equal to 4 whose digit sums are even are 2 and 4.    

Example 2:

Input: num = 30
Output: 14
Explanation:
The 14 integers less than or equal to 30 whose digit sums are even are
2, 4, 6, 8, 11, 13, 15, 17, 19, 20, 22, 24, 26, and 28.

Constraints:

1 <= num <= 1000
```

## Observations

1. **Problem Requirements**: Count positive integers ≤ num where the sum of digits is even
2. **Range**: We need to check numbers from 1 to num (inclusive)
3. **Digit Sum Calculation**: For each number, sum all its digits
4. **Even Check**: A sum is even if it's divisible by 2 (sum % 2 == 0)
5. **Examples Analysis**:
   - For num = 4: Check 1,2,3,4 → digit sums are 1,2,3,4 → even sums: 2,4 → count = 2
   - For num = 30: Numbers with even digit sums include 2,4,6,8,11,13,15,17,19,20,22,24,26,28 → count = 14

## Solution

1. **Initialize counter** to 0
2. **Iterate through range [2, num]**: Start from 2 because 1 has digit sum 1 (odd)
3. **Calculate digit sum** for each number:
   - Extract digits using modulo 10 and integer division
   - Sum all extracted digits
4. **Check if sum is even**: Use bitwise operation `not s & 1`
   - `s & 1` returns 1 if s is odd, 0 if s is even
   - `not (s & 1)` returns True if s is even, False if s is odd
   - `int(not s & 1)` converts to 1 or 0 for counting
5. **Return total count**

**Time Complexity**: O(n × log₁₀(n)) where n is the input number
- We iterate through n numbers
- For each number, we extract digits which takes O(log₁₀(number)) time

**Space Complexity**: O(1) - only using constant extra space

**Key Insight**: The bitwise trick `not s & 1` efficiently checks if a number is even without using modulo operator.

# Tags

