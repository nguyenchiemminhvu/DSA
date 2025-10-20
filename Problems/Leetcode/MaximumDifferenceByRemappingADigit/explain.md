## Problem

https://leetcode.com/problems/maximum-difference-by-remapping-a-digit/description/

```
You are given an integer num. You know that Bob will sneakily remap one of the 10 possible digits (0 to 9) to another digit.

Return the difference between the maximum and minimum values Bob can make by remapping exactly one digit in num.

Notes:

When Bob remaps a digit d1 to another digit d2, Bob replaces all occurrences of d1 in num with d2.
Bob can remap a digit to itself, in which case num does not change.
Bob can remap different digits for obtaining minimum and maximum values respectively.
The resulting number after remapping can contain leading zeroes.

Example 1:

Input: num = 11891
Output: 99009
Explanation: 
To achieve the maximum value, Bob can remap the digit 1 to the digit 9 to yield 99899.
To achieve the minimum value, Bob can remap the digit 1 to the digit 0, yielding 890.
The difference between these two numbers is 99009.

Example 2:

Input: num = 90
Output: 99
Explanation:
The maximum value that can be returned by the function is 99 (if 0 is replaced by 9) and the minimum value that can be returned by the function is 0 (if 9 is replaced by 0).
Thus, we return 99.

Constraints:

1 <= num <= 108
```

## Observations

1. **Maximum Value Strategy**: To maximize the number, we should replace the first non-9 digit with 9. This ensures we're making the most significant change possible.

2. **Minimum Value Strategy**: To minimize the number, we should replace the first non-zero digit with 0. However, we need to be careful not to replace the first digit with 0 if it would create a leading zero (which effectively reduces the number of digits).

3. **Edge Cases**: 
   - If all digits are 9, we can't increase the value further
   - If the first digit is the only non-zero digit, replacing it with 0 would make the number 0

4. **Greedy Approach**: Since we want to maximize the difference, we should make the most impactful digit replacements - targeting the leftmost (most significant) digits first.

## Solution

1. **Convert to List**: Convert the number to a list of character digits for easy manipulation.

2. **Find Target Digits**:
   - `first_non_nine`: The leftmost digit that isn't 9 (for maximization)
   - `first_non_zero`: The leftmost digit that isn't 0 (for minimization)

3. **Maximize**: Replace all occurrences of the first non-9 digit with 9. If all digits are 9, the number remains unchanged.

4. **Minimize**: Replace all occurrences of the first non-0 digit with 0. This strategy works because:
   - If the first digit is non-zero, replacing it with 0 significantly reduces the value
   - If the first digit is 0, we look for the next non-zero digit to replace

**Time Complexity**: O(n) where n is the number of digits
**Space Complexity**: O(n) for storing the digit list

**Example Walkthrough** (num = 11891):
- Maximum: Replace first non-9 digit '1' with '9' → 99899
- Minimum: Replace first non-0 digit '1' with '0' → 00890 = 890
- Difference: 99899 - 890 = 99009

## Tags

array, greedy