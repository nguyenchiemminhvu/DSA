## Problem

https://leetcode.com/problems/check-divisibility-by-digit-sum-and-product/description/

```
You are given a positive integer n. Determine whether n is divisible by the sum of the following two values:

The digit sum of n (the sum of its digits).

The digit product of n (the product of its digits).

Return true if n is divisible by this sum; otherwise, return false.

Example 1:

Input: n = 99

Output: true

Explanation:

Since 99 is divisible by the sum (9 + 9 = 18) plus product (9 * 9 = 81) of its digits (total 99), the output is true.

Example 2:

Input: n = 23

Output: false

Explanation:

Since 23 is not divisible by the sum (2 + 3 = 5) plus product (2 * 3 = 6) of its digits (total 11), the output is false.

Constraints:

1 <= n <= 106
```

## Observations

1. **Key Requirements**: We need to calculate two values from the digits of `n`:
   - Digit sum: sum of all individual digits
   - Digit product: product of all individual digits
   - Then check if `n` is divisible by their sum

2. **Edge Cases**: 
   - If any digit is 0, the product becomes 0, making the divisor `digit_sum + 0 = digit_sum`
   - Single digit numbers: sum and product are the same digit value

3. **Mathematical Properties**:
   - For number 99: digit_sum = 9+9 = 18, digit_product = 9×9 = 81, total = 99. Since 99 % 99 = 0, answer is true
   - For number 23: digit_sum = 2+3 = 5, digit_product = 2×3 = 6, total = 11. Since 23 % 11 ≠ 0, answer is false

4. **Algorithm Approach**: Extract digits one by one using modulo and integer division operations

## Solution

1. **Initialization**: 
   - `temp = n`: working copy to avoid modifying original number
   - `s = 0`: initialize sum of digits
   - `p = 1`: initialize product of digits (start with 1 for multiplication)

2. **Digit Extraction Loop**:
   - `d = temp % 10`: get the rightmost digit
   - `s += d`: add digit to running sum
   - `p *= d`: multiply digit to running product
   - `temp //= 10`: remove the rightmost digit (integer division)

3. **Final Check**: Return whether `n` is divisible by `(digit_product + digit_sum)`

**Time Complexity**: O(log n) - proportional to number of digits
**Space Complexity**: O(1) - only using constant extra space

**Example Walkthrough**:
- n = 99: temp=99 → d=9, s=9, p=9, temp=9 → d=9, s=18, p=81, temp=0 → return 99%(81+18) = 99%99 = 0 → true
- n = 23: temp=23 → d=3, s=3, p=3, temp=2 → d=2, s=5, p=6, temp=0 → return 23%(6+5) = 23%11 = 1 → false

# Tags
- Math
- Implementation
- Number Theory

