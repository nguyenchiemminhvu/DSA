## Problem

https://leetcode.com/problems/number-of-common-factors/description/

```
Given two positive integers a and b, return the number of common factors of a and b.

An integer x is a common factor of a and b if x divides both a and b.

Example 1:

Input: a = 12, b = 6
Output: 4
Explanation: The common factors of 12 and 6 are 1, 2, 3, 6.

Example 2:

Input: a = 25, b = 30
Output: 2
Explanation: The common factors of 25 and 30 are 1, 5.

Constraints:

1 <= a, b <= 1000
```

## Observations

1. **Key Insight**: The common factors of two numbers `a` and `b` are exactly the factors of their GCD (Greatest Common Divisor).
   - If `x` is a common factor of `a` and `b`, then `x` divides both `a` and `b`
   - This means `x` also divides `gcd(a, b)`
   - Conversely, every factor of `gcd(a, b)` is also a common factor of `a` and `b`

2. **Mathematical Property**: For any two integers `a` and `b`, the set of common factors equals the set of factors of `gcd(a, b)`.

3. **Algorithm Optimization**: Instead of checking all numbers up to `min(a, b)`, we only need to check numbers up to `gcd(a, b)`, which is typically much smaller.

4. **Edge Cases**: 
   - When `a = b`, their GCD is the number itself, so we count all factors of that number
   - The number 1 is always a common factor of any two positive integers

## Solution

1. **Calculate GCD**: `g = math.gcd(a, b)` - Find the greatest common divisor of `a` and `b`
2. **Iterate through potential factors**: Loop from 1 to `g` (inclusive)
3. **Check common divisibility**: For each value, verify it divides both `a` and `b`
4. **Count valid factors**: Increment counter for each common factor found

**Time Complexity**: O(gcd(a, b)) - We iterate up to the GCD value
**Space Complexity**: O(1) - Only using constant extra space

**Alternative Optimization**: Since we know all factors of GCD are common factors, we could just count the factors of GCD directly:

```python
def commonFactors(self, a: int, b: int) -> int:
    g = math.gcd(a, b)
    count = 0
    for i in range(1, g + 1):
        if g % i == 0:  # Only check if i divides the GCD
            count += 1
    return count
```

This optimization reduces redundant divisibility checks since every factor of GCD is guaranteed to be a common factor.

# Tags

- Math
- Number Theory
- GCD
- Factors

