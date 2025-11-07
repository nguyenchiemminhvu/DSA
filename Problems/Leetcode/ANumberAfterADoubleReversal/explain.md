## Problem

https://leetcode.com/problems/a-number-after-a-double-reversal/description/

```
Reversing an integer means to reverse all its digits.

For example, reversing 2021 gives 1202. Reversing 12300 gives 321 as the leading zeros are not retained.
Given an integer num, reverse num to get reversed1, then reverse reversed1 to get reversed2. Return true if reversed2 equals num. Otherwise return false.

Example 1:

Input: num = 526
Output: true
Explanation: Reverse num to get 625, then reverse 625 to get 526, which equals num.

Example 2:

Input: num = 1800
Output: false
Explanation: Reverse num to get 81, then reverse 81 to get 18, which does not equal num.

Example 3:

Input: num = 0
Output: true
Explanation: Reverse num to get 0, then reverse 0 to get 0, which equals num.

Constraints:

0 <= num <= 106
```

## Observations

1. **Key Insight**: A number will remain the same after double reversal if and only if it doesn't have trailing zeros (except for the number 0 itself).

2. **Why trailing zeros matter**:
   - When we reverse a number with trailing zeros, those zeros become leading zeros
   - Leading zeros are dropped during integer representation
   - Example: 1800 → reverse → 0081 → 81 (leading zeros dropped)
   - Then: 81 → reverse → 18 ≠ 1800

3. **Special cases**:
   - `num = 0`: Always returns true (0 reversed is still 0)
   - Single digit numbers (1-9): Always return true
   - Numbers ending in non-zero digits: Always return true
   - Numbers ending in zeros: Always return false (except 0)

4. **Pattern Recognition**:
   - If `num % 10 == 0` and `num != 0`, then the answer is false
   - Otherwise, the answer is true

5. **Examples walkthrough**:
   - 526: 526 → 625 → 526 ✓ (no trailing zeros)
   - 1800: 1800 → 81 → 18 ✗ (has trailing zeros)
   - 0: 0 → 0 → 0 ✓ (special case)

## Solution

The provided solution uses a brute force approach that actually performs both reversals:

```python
def reverse(val: int) -> int:
    res = 0
    while val:
        res = res * 10 + (val % 10)
        val //= 10
    return res
```

**How the reverse function works**:
1. Extract the last digit using `val % 10`
2. Build the result by multiplying current result by 10 and adding the digit
3. Remove the last digit using `val //= 10`
4. Repeat until `val` becomes 0

**Time Complexity**: O(log n) where n is the input number (number of digits)
**Space Complexity**: O(1)

**Optimized Solution**:
Instead of actually performing the reversals, we can use the mathematical insight:

```python
def isSameAfterReversals(self, num: int) -> bool:
    return num == 0 or num % 10 != 0
```

This optimized version has:
- **Time Complexity**: O(1)
- **Space Complexity**: O(1)

**Why the optimization works**:
- If `num == 0`: Special case, always true
- If `num % 10 != 0`: No trailing zeros, so double reversal preserves the number
- If `num % 10 == 0` and `num != 0`: Has trailing zeros, so double reversal changes the number

# Tags

- Math
- Number Theory
- String Manipulation
- Optimization

