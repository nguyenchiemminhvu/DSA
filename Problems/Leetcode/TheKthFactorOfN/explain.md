## Problem

https://leetcode.com/problems/the-kth-factor-of-n/description/

Given two positive integers `n` and `k`, return the `k`th smallest factor of `n`, or `-1` if `n` has fewer than `k` factors.

A **factor** of `n` is an integer `i` such that `n % i == 0`.

**Examples:**
- `n=12, k=3` → factors are `[1, 2, 3, 4, 6, 12]` → answer is `3`
- `n=7, k=2` → factors are `[1, 7]` → answer is `7`
- `n=4, k=4` → factors are `[1, 2, 4]` → only 3 factors → answer is `-1`

**Constraints:** `1 <= k <= n <= 1000`

---

## Solution

```python
class Solution:
    def kthFactor(self, n: int, k: int) -> int:
        def get_factors(val: int) -> list[int]:
            factors = set()
            for i in range(1, int(val ** 0.5) + 1):
                if val % i == 0:
                    factors.add(i)
                    factors.add(val // i)
            return sorted(list(factors))
        
        factors = get_factors(n)
        return -1 if k - 1 >= len(factors) else factors[k - 1]
```

---

## Explanation

### Key Insight: Factor Pairs

Every factor `i` of `n` comes with a paired factor `n // i`. For example, for `n = 12`:
- `i = 1` → pair is `12`
- `i = 2` → pair is `6`
- `i = 3` → pair is `4`

This means we only need to iterate up to $\sqrt{n}$, collecting both `i` and `n // i` at each step.

### Algorithm

1. **Collect factors using a set** — iterate `i` from `1` to `floor(√n)`. If `n % i == 0`, add both `i` and `n // i` to a set. Using a set handles the case where `i == n // i` (i.e., `n` is a perfect square, e.g., `n=4, i=2` gives the same factor `2` on both sides).

2. **Sort the factors** — sort the collected set in ascending order.

3. **Return the k-th element** — use 0-based index `k - 1`. If `k - 1 >= len(factors)`, return `-1`.

### Complexity

| | Naive O(n) | This Solution |
|---|---|---|
| **Time** | $O(n)$ | $O(\sqrt{n} \log \sqrt{n})$ |
| **Space** | $O(n)$ | $O(\sqrt{n})$ |

The dominant cost is the $O(\sqrt{n})$ loop plus $O(\sqrt{n} \log \sqrt{n})$ sort over at most $O(\sqrt{n})$ factors.

### Walkthrough: n=12, k=3

| `i` | `n % i == 0?` | Added factors |
|-----|--------------|---------------|
| 1   | Yes          | `{1, 12}`     |
| 2   | Yes          | `{1, 2, 6, 12}` |
| 3   | Yes          | `{1, 2, 3, 4, 6, 12}` |

After sorting: `[1, 2, 3, 4, 6, 12]`  
Index `k-1 = 2` → return `3` ✓
