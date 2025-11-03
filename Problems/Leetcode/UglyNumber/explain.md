## Problem

https://leetcode.com/problems/ugly-number/description

```
An ugly number is a positive integer which does not have a prime factor other than 2, 3, and 5.

Given an integer n, return true if n is an ugly number.

Example 1:

Input: n = 6
Output: true
Explanation: 6 = 2 × 3

Example 2:

Input: n = 1
Output: true
Explanation: 1 has no prime factors.

Example 3:

Input: n = 14
Output: false
Explanation: 14 is not ugly since it includes the prime factor 7.

Constraints:

-231 <= n <= 231 - 1
```

## Observations

1. **Definition of Ugly Number**: An ugly number is a positive integer whose only prime factors are 2, 3, and 5.

2. **Special Cases**:
   - `n = 1` is considered ugly (has no prime factors)
   - `n <= 0` cannot be ugly (ugly numbers must be positive)

3. **Key Insight**: If a number is ugly, we can completely divide it by 2, 3, and 5 repeatedly until we're left with 1.

4. **Algorithm Strategy**: 
   - Divide `n` by 2, 3, and 5 as many times as possible
   - If the result is 1, then `n` was composed only of these prime factors
   - If the result is not 1, then `n` had other prime factors

5. **Time Complexity**: O(log n) - we divide by at most 3 different numbers
6. **Space Complexity**: O(1) - only using constant extra space

## Solution

```python
class Solution:
    def isUgly(self, n: int) -> bool:
        for d in [2, 3, 5]:
            while n > 1 and n % d == 0:
                n //= d
        return n == 1
```

### Explanation:

**Step-by-step breakdown:**

1. **Input Validation**: The algorithm implicitly handles `n <= 0` cases because:
   - If `n <= 0`, the while loop condition `n > 1` will be false
   - We'll return `n == 1`, which is false for `n <= 0`

2. **Prime Factor Elimination**: For each divisor `d` in `[2, 3, 5]`:
   - Keep dividing `n` by `d` while `n` is divisible by `d` and `n > 1`
   - This removes all occurrences of prime factor `d` from `n`

3. **Final Check**: After removing all factors of 2, 3, and 5:
   - If `n == 1`: The original number was composed only of 2s, 3s, and 5s → ugly
   - If `n != 1`: The original number had other prime factors → not ugly

### Examples Walkthrough:

**Example 1: n = 6**
- Initial: n = 6
- d = 2: 6 % 2 == 0, so n = 6 // 2 = 3
- d = 2: 3 % 2 != 0, move to next divisor
- d = 3: 3 % 3 == 0, so n = 3 // 3 = 1
- d = 3: 1 % 3 != 0 and n == 1, move to next divisor
- d = 5: 1 % 5 != 0 and n == 1, exit loop
- Return: n == 1 → **true**

**Example 2: n = 14**
- Initial: n = 14
- d = 2: 14 % 2 == 0, so n = 14 // 2 = 7
- d = 2: 7 % 2 != 0, move to next divisor
- d = 3: 7 % 3 != 0, move to next divisor
- d = 5: 7 % 5 != 0, exit loop
- Return: n == 7 ≠ 1 → **false** (7 is a prime factor other than 2, 3, 5)

**Example 3: n = 1**
- Initial: n = 1
- For all d in [2, 3, 5]: condition `n > 1` is false, skip while loops
- Return: n == 1 → **true**

### Alternative Approach (with explicit edge case handling):

```python
class Solution:
    def isUgly(self, n: int) -> bool:
        if n <= 0:
            return False
        
        for divisor in [2, 3, 5]:
            while n % divisor == 0:
                n //= divisor
        
        return n == 1
```

Both approaches are equivalent, but the given solution is more concise by combining the edge case handling within the loop condition.

# Tags

- **Math**
- **Number Theory** 
- **Prime Factorization**

