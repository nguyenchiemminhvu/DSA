## Problem

https://leetcode.com/problems/partitioning-into-minimum-number-of-deci-binary-numbers/description/

```
A decimal number is called deci-binary if each of its digits is either 0 or 1 without any leading zeros. For example, 101 and 1100 are deci-binary, while 112 and 3001 are not.

Given a string n that represents a positive decimal integer, return the minimum number of positive deci-binary numbers needed so that they sum up to n.

Example 1:

Input: n = "32"
Output: 3
Explanation: 10 + 11 + 11 = 32

Example 2:

Input: n = "82734"
Output: 8

Example 3:

Input: n = "27346209830709182346"
Output: 9

Constraints:

1 <= n.length <= 105
n consists of only digits.
n does not contain any leading zeros and represents a positive integer.
```

## Observations

1. **Deci-binary definition**: A deci-binary number contains only digits 0 and 1.

2. **Key insight**: When we add deci-binary numbers, each digit position can only contribute at most 1 to the sum (since deci-binary digits are either 0 or 1).

3. **Critical observation**: To form a digit `d` at any position in the result, we need exactly `d` deci-binary numbers that have digit `1` at that position.

4. **Minimum requirement**: The digit with the maximum value in the target number `n` determines the minimum number of deci-binary numbers needed.

5. **Why maximum digit matters**: 
   - If the maximum digit is `k`, we need at least `k` deci-binary numbers
   - We can always construct exactly `k` deci-binary numbers to sum to `n`

6. **Construction proof**: For any number like "82734":
   - We need 8 deci-binary numbers (because of digit 8)
   - We can construct: 11111, 11111, 11111, 11111, 11111, 11111, 11111, 10101
   - This gives us: 8×1=8, 2×1=2, 7×1=7, 3×1=3, 4×1=4

## Solution

The solution is elegantly simple: **return the maximum digit in the string**.

**Algorithm**:
1. Find the maximum character in the string `n`
2. Convert it to integer and return

**Why this works**:
- The maximum digit represents the bottleneck - the position that requires the most deci-binary numbers
- Since each deci-binary number can contribute at most 1 to any digit position, we need exactly `max_digit` numbers
- We can always construct `max_digit` deci-binary numbers that sum to the target

**Time Complexity**: O(n) where n is the length of the string
**Space Complexity**: O(1)

**Example walkthrough**:
- For n = "32": max digit = 3, so we need 3 deci-binary numbers
  - Possible construction: 11 + 11 + 10 = 32
- For n = "82734": max digit = 8, so we need 8 deci-binary numbers
- For n = "27346209830709182346": max digit = 9, so we need 9 deci-binary numbers

## Tags

array, string, greedy