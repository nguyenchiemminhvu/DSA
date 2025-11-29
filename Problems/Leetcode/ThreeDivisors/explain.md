## Problem

https://leetcode.com/problems/three-divisors/description/

```
Given an integer n, return true if n has exactly three positive divisors. Otherwise, return false.

An integer m is a divisor of n if there exists an integer k such that n = k * m.

Example 1:
Input: n = 2
Output: false
Explanation: 2 has only two divisors: 1 and 2.

Example 2:
Input: n = 4
Output: true
Explanation: 4 has three divisors: 1, 2, and 4.

Constraints:
1 <= n <= 10^4
```

## Observations

1. **Key insight**: A number has exactly 3 divisors if and only if it's the square of a prime number.
   - For example: 4 = 2² has divisors {1, 2, 4}, 9 = 3² has divisors {1, 3, 9}, 25 = 5² has divisors {1, 5, 25}
   - Any composite (non-prime) square like 16 = 4² has more than 3 divisors: {1, 2, 4, 8, 16}

2. **Divisor pairing**: For any divisor `i` where `i * i <= n`, there's a corresponding divisor `n / i`
   - If `i * i = n`, then `i` is the only divisor at the "middle" (perfect square)
   - Otherwise, `i` and `n / i` are distinct divisors

3. **Edge cases**:
   - `n = 1` has only 1 divisor (itself)
   - Prime numbers have exactly 2 divisors (1 and itself)
   - Perfect squares of primes have exactly 3 divisors

## Solution

1. Initialize an empty set `s` to store unique divisors
2. Iterate from `i = 1` to `√n` (while `i * i <= n`)
3. For each `i` that divides `n`:
   - Add `i` to the set
   - If `i² ≠ n`, also add `n / i` to the set (the paired divisor)
4. Return `true` if the set has exactly 3 elements

**Why this works**:
- We only iterate up to `√n` for efficiency, capturing all divisor pairs
- The set automatically handles uniqueness
- For perfect squares, we avoid adding the square root twice with the `i * i != n` check
- Time complexity: O(√n)
- Space complexity: O(d) where d is the number of divisors (at most O(√n))

**Alternative approach**: Since only squares of primes have 3 divisors, we could check if `n` is a perfect square and if `√n` is prime, which would be slightly more efficient.

# Tags
#math #number-theory #divisors #prime-numbers

