## Problem

https://leetcode.com/problems/sum-of-primes-between-number-and-its-reverse/description/

Given an integer `n`, let `r` be the integer formed by reversing the digits of `n`. Return the **sum** of all prime numbers in the range `[min(n, r), max(n, r)]`, inclusive.

**Example 1:**
- Input: `n = 13` → reverse `r = 31`, range `[13, 31]`
- Primes: 13, 17, 19, 23, 29, 31 → Output: `132`

**Example 2:**
- Input: `n = 10` → reverse `r = 1`, range `[1, 10]`
- Primes: 2, 3, 5, 7 → Output: `17`

**Example 3:**
- Input: `n = 8` → reverse `r = 8`, range `[8, 8]`
- No primes → Output: `0`

**Constraints:** `1 <= n <= 1000`

---

## Observations

1. **Digit reversal:** Reversing `n`'s digits as a string (e.g. `"10"[::-1] → "01"`) and converting back to int naturally strips leading zeros (e.g. `"01"` → `1`), giving the correct mathematical reverse.

2. **Range can be a single point:** If `n` is a palindrome (e.g. `n = 8`, `n = 121`), then `r == n` and the range is just `[n, n]`. If `n` is not prime, the sum is 0.

3. **Small upper bound:** Since `n ≤ 1000`, the reversed number `r` is also at most 1000 (reversing a 4-digit number at most gives another 4-digit number in this range). So the sieve only ever needs to cover up to **1000**, making it very efficient.

4. **Sieve of Eratosthenes is ideal here:** Instead of testing each number individually for primality, a sieve pre-computes all primes up to `max(n, r)` in `O(m log log m)` time, then each range query is `O(1)` per element.

5. **Off-by-one in sieve call:** The code calls `get_primes(right + 1)` but builds the sieve up to `right + 1` inclusive — `right` itself is still covered. This is safe but slightly over-allocates by one element; `get_primes(right)` would suffice.

---

## Solution Explanation

```python
class Solution:
    def sumOfPrimesInRange(self, n: int) -> int:
        def get_primes(limit: int) -> Set[int]:
            primes = [True] * (limit + 1)
            primes[0] = primes[1] = False
            for i in range(2, int(limit ** 0.5) + 1):
                if primes[i]:
                    for j in range(i * i, limit + 1, i):
                        primes[j] = False
            return set([i for i in range(limit + 1) if primes[i]])
        
        rev = int(str(n)[::-1])
        left = min(n, rev)
        right = max(n, rev)
        primes = get_primes(right + 1)
        res = 0
        for val in range(left, right + 1):
            if val in primes:
                res += val
        return res
```

**Step 1 — Compute the reverse:**
`str(n)[::-1]` reverses the digit string, and `int(...)` converts it back, stripping any leading zeros.

**Step 2 — Define the range:**
`left = min(n, rev)`, `right = max(n, rev)` ensures the range is always well-ordered regardless of which is larger.

**Step 3 — Sieve of Eratosthenes up to `right`:**
- Start with a boolean array `primes[0..limit]`, all `True`.
- Mark `0` and `1` as not prime.
- For every `i` from `2` to `√limit`: if `i` is still marked prime, mark all multiples starting from `i²` as composite.
- The key insight is starting at `i²` — all smaller multiples of `i` were already marked by earlier primes.
- Return the set of indices still marked `True`.

**Step 4 — Sum primes in range:**
Iterate `[left, right]` and accumulate values that are in the prime set. Set membership is `O(1)`.

**Complexity:**
- Time: `O(m log log m)` for the sieve, where `m = max(n, r) ≤ 1000`, plus `O(m)` for the range sum → effectively `O(m log log m)`.
- Space: `O(m)` for the sieve array and prime set.
