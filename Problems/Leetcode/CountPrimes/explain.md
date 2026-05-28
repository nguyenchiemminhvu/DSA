## Problem

https://leetcode.com/problems/count-primes/

```
Given an integer n, return the number of prime numbers that are strictly less than n.

Example 1:
Input: n = 10
Output: 4
Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.

Example 2:
Input: n = 0
Output: 0

Example 3:
Input: n = 1
Output: 0

Constraints:
0 <= n <= 5 * 10^6
```

## Observations

1. **Brute-force is too slow**: Checking each number from `2` to `n-1` for primality by trial division costs `O(n × √n)`, which is too slow when `n` can reach `5 × 10^6`.

2. **Sieve of Eratosthenes**: A classic algorithm that marks all **non-primes** in one pass. Start from the smallest prime `2`, and iteratively mark its multiples as composite. Repeat for the next unmarked number.

3. **Start marking from `p * p`**: When processing a prime `p`, all multiples smaller than `p²` (i.e., `2p, 3p, ..., (p-1)p`) have already been marked by a previous, smaller prime. So we safely start marking at `p²`, saving work.

4. **Only loop up to `√n`**: Any composite number `c ≤ n` must have at least one prime factor `≤ √n`. So once we process all primes up to `√n`, every remaining `True` entry in the array is a prime.

5. **Off-by-one caution**: The problem asks for primes **strictly less than** `n`. The final count must exclude index `n` itself even though the boolean array is sized `n+1`.

## Solution

The solution uses the **Sieve of Eratosthenes**:

```python
class Solution:
    def countPrimes(self, n: int) -> int:
        if n < 2:
            return 0

        is_prime = [True] * (n + 1)
        is_prime[0] = is_prime[1] = False  # 0 and 1 are not prime

        for p in range(2, int(n**0.5) + 1):
            if is_prime[p]:
                for i in range(p * p, n + 1, p):
                    is_prime[i] = False

        return sum(1 for p in range(n) if is_prime[p])
```

**Step-by-step walkthrough for `n = 10`:**

| Pass `p` | Action | Marked composite |
|----------|--------|-----------------|
| `p = 2`  | Start from `2² = 4`, step 2 | 4, 6, 8, 10 |
| `p = 3`  | Start from `3² = 9`, step 3 | 9 |
| `p = 4`  | `is_prime[4]` is `False` → skip | — |

Remaining `True` positions below 10: **2, 3, 5, 7** → answer is **4**.

**Key Points:**

1. **Initialization**: Allocate `is_prime[0..n]` as all `True`, then clear indices `0` and `1`.

2. **Outer loop bound**: Run `p` from `2` to `int(√n)` inclusive. Beyond this, all composites are already marked.

3. **Inner loop start**: Begin at `p * p` (not `2 * p`) to avoid redundant work.

4. **Counting**: Sum only indices `p < n` where `is_prime[p]` is still `True`.

5. **Time Complexity**: `O(n log log n)` — the harmonic series of prime reciprocals grows extremely slowly.

6. **Space Complexity**: `O(n)` — for the boolean sieve array.

## Tags

math, sieve of eratosthenes, array
