## Problem

https://leetcode.com/problems/divide-two-integers/description/

```
Given two integers dividend and divisor, divide two integers without using multiplication, division, and mod operator.

The integer division should truncate toward zero, which means losing its fractional part. For example, 8.345 would be truncated to 8, and -2.7335 would be truncated to -2.

Return the quotient after dividing dividend by divisor.

Note: Assume we are dealing with an environment that could only store integers within the 32-bit signed integer range: [−231, 231 − 1]. For this problem, if the quotient is strictly greater than 231 - 1, then return 231 - 1, and if the quotient is strictly less than -231, then return -231.

Example 1:

Input: dividend = 10, divisor = 3
Output: 3
Explanation: 10/3 = 3.33333.. which is truncated to 3.

Example 2:

Input: dividend = 7, divisor = -3
Output: -2
Explanation: 7/-3 = -2.33333.. which is truncated to -2.

Constraints:

-231 <= dividend, divisor <= 231 - 1
divisor != 0
```

## Observations

1. **Problem Requirements**:
   - Divide two integers without using multiplication, division, or mod operators
   - Integer division should truncate toward zero (not floor division)
   - Handle 32-bit signed integer overflow: [-2³¹, 2³¹ - 1]

2. **Key Insights**:
   - The provided solution actually violates the constraint by using the `/` division operator
   - Truncation toward zero means: positive results use floor(), negative results use ceil()
   - Need to handle overflow cases where result exceeds 32-bit signed integer range

3. **Edge Cases**:
   - Overflow: dividend = -2³¹, divisor = -1 → result = 2³¹ (exceeds max positive 32-bit)
   - Maximum negative: result < -2³¹
   - Zero dividend: 0 / any_non_zero = 0
   - Negative divisor or dividend affects sign

4. **Truncation Behavior**:
   - For positive quotients: 10/3 = 3.33... → truncate to 3 (floor)
   - For negative quotients: -10/3 = -3.33... → truncate to -3 (ceil, toward zero)

## Solution

**Issues with Current Solution**:
1. **Violates Constraint**: Uses `/` operator which is explicitly forbidden
2. **Incorrect Overflow Bound**: Uses `-0xFFFFFFFF` instead of `-0x80000000` (-2³¹)
3. **Missing Import**: Should import `math` module

**Correct Approach** (without using division):
- Use bit manipulation and repeated subtraction
- Build quotient by finding largest multiples of divisor that fit in dividend
- Handle signs separately to simplify logic
- Use bit shifting to efficiently multiply divisor by powers of 2

**Time Complexity**: O(log n) where n is the quotient
**Space Complexity**: O(1)

## Tags

math, bit manipulation