## Problem

https://leetcode.com/problems/split-with-minimum-sum/description/

```
Given a positive integer num, split it into two non-negative integers num1 and num2 such that:

The concatenation of num1 and num2 is a permutation of num.
In other words, the sum of the number of occurrences of each digit in num1 and num2 is equal to the number of occurrences of that digit in num.
num1 and num2 can contain leading zeros.
Return the minimum possible sum of num1 and num2.

Notes:

It is guaranteed that num does not contain any leading zeros.
The order of occurrence of the digits in num1 and num2 may differ from the order of occurrence of num.

Example 1:

Input: num = 4325
Output: 59
Explanation: We can split 4325 so that num1 is 24 and num2 is 35, giving a sum of 59. We can prove that 59 is indeed the minimal possible sum.

Example 2:

Input: num = 687
Output: 75
Explanation: We can split 687 so that num1 is 68 and num2 is 7, which would give an optimal sum of 75.

Constraints:

10 <= num <= 109
```

## Observations

1. **Key Insight**: To minimize the sum of two numbers formed by splitting digits, we need to minimize the most significant digits of both numbers.

2. **Greedy Approach**: Sort all digits in ascending order, then distribute them alternately between the two numbers. This ensures:
   - The smallest digits go to the most significant positions
   - Both numbers are roughly balanced in length
   - The overall sum is minimized

3. **Distribution Strategy**: 
   - After sorting digits, assign digits at even indices (0, 2, 4, ...) to the first number
   - Assign digits at odd indices (1, 3, 5, ...) to the second number
   - This creates the most balanced distribution possible

4. **Example Walkthrough**:
   - Input: 4325 → sorted: "2345"
   - First number: digits at indices 0,2 → "24" 
   - Second number: digits at indices 1,3 → "35"
   - Sum: 24 + 35 = 59 (minimum possible)

5. **Why This Works**: 
   - By placing smaller digits in higher positions (leftmost), we minimize their contribution to the final sum
   - Alternating distribution ensures neither number gets disproportionately larger digits
   - This greedy strategy guarantees the optimal solution

## Solution

The algorithm follows these steps:

1. **Convert and Sort**: Convert the integer to string and sort digits in ascending order
2. **Alternate Distribution**: 
   - Build first number using digits at even indices (0, 2, 4, ...)
   - Build second number using digits at odd indices (1, 3, 5, ...)
3. **Convert and Sum**: Convert both strings back to integers and return their sum

**Time Complexity**: O(n log n) where n is the number of digits (due to sorting)
**Space Complexity**: O(n) for storing the digit string and two result strings

**Edge Cases Handled**:
- Single digit numbers (constraint ensures num ≥ 10)
- Numbers with repeated digits
- Numbers where one result string might be shorter than the other

## Tags

array, string, greedy