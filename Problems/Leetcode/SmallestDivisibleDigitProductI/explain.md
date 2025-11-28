## Problem

https://leetcode.com/problems/smallest-divisible-digit-product-i/description/

You are given two integers `n` and `t`. Return the smallest number greater than or equal to `n` such that the product of its digits is divisible by `t`.

**Example 1:**
- Input: n = 10, t = 2
- Output: 10
- Explanation: The digit product of 10 is 0, which is divisible by 2.

**Example 2:**
- Input: n = 15, t = 3
- Output: 16
- Explanation: The digit product of 16 is 6, which is divisible by 3.

**Constraints:**
- 1 <= n <= 100
- 1 <= t <= 10

## Observations

1. **Product of digits**: For any number, we multiply all its digits together. For example:
   - 123 → 1 × 2 × 3 = 6
   - 105 → 1 × 0 × 5 = 0

2. **Zero handling**: If any digit is 0, the product becomes 0. Since 0 is divisible by any non-zero number, any number containing 0 will satisfy the condition.

3. **Brute force approach**: Given the constraint that n ≤ 100, we can check each number starting from n until we find one whose digit product is divisible by t.

4. **Maximum iterations**: Since we're looking for the smallest valid number ≥ n, and given the small constraint, we won't need to check many numbers. In the worst case, we might need to check up to around 100 numbers.

## Solution

The solution uses a brute force approach with a helper function to calculate the digit product:

```python
class Solution:
    def smallestNumber(self, n: int, t: int) -> int:
        def product(val: int) -> int:
            p = 1
            while val:
                p *= (val % 10)
                val //= 10
            return p
        
        for i in range(100):
            val = product(n + i)
            if val % t == 0:
                return n + i
        return -1
```

**Algorithm Breakdown:**

1. **Helper function `product(val)`**: 
   - Calculates the product of all digits in a number
   - Uses modulo 10 to get the last digit and integer division to remove it
   - Multiplies each digit to build the product

2. **Main loop**:
   - Starts from n and checks each subsequent number
   - For each number, calculates its digit product
   - Returns the first number whose digit product is divisible by t

**Time Complexity**: O(k × log(n)) where k is the number of iterations needed and log(n) is for calculating digit product
**Space Complexity**: O(1)

**Why this works**: The constraints guarantee that we'll find a solution within a reasonable range, and the brute force approach is efficient enough for the given limits.

# Tags
- Math
- Brute Force
- Number Theory

