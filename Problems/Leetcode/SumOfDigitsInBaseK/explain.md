## Problem

https://leetcode.com/problems/sum-of-digits-in-base-k/description/

```
Given an integer n (in base 10) and a base k, return the sum of the digits of n after converting n from base 10 to base k.

After converting, each digit should be interpreted as a base 10 number, and the sum should be returned in base 10.

Example 1:

Input: n = 34, k = 6
Output: 9
Explanation: 34 (base 10) expressed in base 6 is 54. 5 + 4 = 9.

Example 2:

Input: n = 10, k = 10
Output: 1
Explanation: n is already in base 10. 1 + 0 = 1.

Constraints:

1 <= n <= 100
2 <= k <= 10
```

## Observations

1. **Problem Understanding**: We need to:
   - Convert a decimal number `n` to base `k`
   - Sum up all the digits in the base `k` representation
   - Return the sum in decimal (base 10)

2. **Base Conversion Process**: To convert a number from base 10 to base `k`, we repeatedly:
   - Take the remainder when dividing by `k` (this gives us the rightmost digit)
   - Divide the number by `k` (this removes the rightmost digit)
   - Continue until the number becomes 0

3. **Key Insight**: We don't actually need to store the base `k` representation as a string or array. We can directly sum the digits as we extract them during the conversion process.

4. **Example Walkthrough** (n=34, k=6):
   - 34 ÷ 6 = 5 remainder 4 → digit: 4, sum: 4
   - 5 ÷ 6 = 0 remainder 5 → digit: 5, sum: 4+5=9
   - Result: 9

5. **Mathematical Foundation**: 
   - Any number in base `k` can be represented as: `d₀ + d₁×k + d₂×k² + ... + dₙ×kⁿ`
   - The digits `d₀, d₁, d₂, ...` are exactly what we get from `n % k` at each step
   - We want the sum: `d₀ + d₁ + d₂ + ... + dₙ`

## Solution

The solution uses a straightforward base conversion algorithm with digit summation:

1. **Initialize**: Start with `res = 0` to store the sum of digits

2. **Extract Digits**: While the number `val` is greater than 0:
   - Get the rightmost digit: `val % base`
   - Add this digit to our result: `res += (val % base)`
   - Remove the rightmost digit: `val //= base`

3. **Return Sum**: Once `val` becomes 0, we've processed all digits and can return the sum

**Algorithm Correctness**:
- The `%` operator gives us the remainder, which is the digit in the target base
- The `//` operator performs integer division, effectively "removing" the processed digit
- This process naturally extracts digits from right to left (least significant to most significant)

**Time Complexity**: O(logₖ(n)) - we perform at most logₖ(n) iterations since we divide by k each time
**Space Complexity**: O(1) - only using a constant amount of extra space

**Example Execution** (n=34, k=6):
```
Initial: val=34, res=0
Iteration 1: res += 34%6 = 4, val = 34//6 = 5 → res=4, val=5
Iteration 2: res += 5%6 = 5, val = 5//6 = 0 → res=9, val=0
Return: 9
```

# Tags

- Math
- Base Conversion  
- Number Theory

