## Problem

https://leetcode.com/problems/maximum-prime-difference/description/

Given an integer array `nums`, return the **maximum distance** between the indices of two (not necessarily different) prime numbers in `nums`.

**Examples:**

- `nums = [4,2,9,5,3]` → `3` (`nums[1]=2`, `nums[3]=5`, `nums[4]=3` are prime; `|4-1| = 3`)
- `nums = [4,8,2,8]` → `0` (only `nums[2]=2` is prime; `|2-2| = 0`)

**Constraints:**
- `1 <= nums.length <= 3 * 10^5`
- `1 <= nums[i] <= 100`
- At least one prime exists in `nums`

---

## Observations

1. **We only care about two indices** — the first and last prime in the array. The maximum distance between any two prime indices is always `last_prime_index - first_prime_index`, since distance grows monotonically as we move the endpoints outward.

2. **nums[i] ≤ 100** — the search space for primes is tiny (only 25 primes exist below 100). We can precompute all primes up to 100 using the Sieve of Eratosthenes in O(N log log N), then do O(1) lookups.

3. **Single prime edge case** — if only one prime exists, both the first and last prime index are the same, so the answer is `0`. This is handled automatically.

---

## Solution Explanation

```python
class Solution:
    def maximumPrimeDifference(self, nums: List[int]) -> int:
        def sieve_primes(limit: int) -> set[int]:
            masks = [True] * (limit + 1)
            masks[0] = masks[1] = False
            for p in range(2, int(limit ** 0.5) + 1):
                if masks[p]:
                    for i in range(p * p, limit + 1, p):
                        masks[i] = False
            
            return set(i for i in range(2, limit + 1) if masks[i])

        primes = sieve_primes(max(nums) + 1)
        mp = []
        for i in range(len(nums)):
            if nums[i] in primes:
                mp.append(i)

        return mp[-1] - mp[0]
```

### Step-by-step

**1. Sieve of Eratosthenes (`sieve_primes`)**

Build a boolean array `masks` of size `limit + 1`, initially all `True`. Mark `0` and `1` as non-prime, then for every number `p` from `2` up to `√limit`:
- If `masks[p]` is still `True` (p is prime), mark all multiples of `p` starting from `p²` as `False`.

Starting from `p²` is an optimization — all smaller multiples of `p` were already marked by smaller primes. After the sieve, collect every index `i` where `masks[i]` is `True` into a set for O(1) lookup.

**2. Collect prime indices**

Iterate through `nums` once and append each index `i` where `nums[i]` is prime to the list `mp`.

**3. Return the answer**

Because `mp` is built in increasing index order, `mp[0]` is the first prime index and `mp[-1]` is the last. Their difference `mp[-1] - mp[0]` is the maximum possible distance.

### Complexity

| | |
|---|---|
| Time | O(M log log M + N), where M = max(nums) ≤ 100, N = len(nums) |
| Space | O(M) for the sieve |

Since M ≤ 100, the sieve is effectively O(1), making the overall complexity **O(N)**.
