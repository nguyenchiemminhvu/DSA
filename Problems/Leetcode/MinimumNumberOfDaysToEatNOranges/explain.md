## Problem

https://leetcode.com/problems/minimum-number-of-days-to-eat-n-oranges/description/

There are `n` oranges in the kitchen. Each day you may choose **exactly one** of the following actions:

1. Eat **1** orange.
2. If `n` is divisible by 2, eat `n / 2` oranges (leaving `n / 2`).
3. If `n` is divisible by 3, eat `2 * (n / 3)` oranges (leaving `n / 3`).

Return the **minimum number of days** to eat all `n` oranges.

**Constraints:** `1 <= n <= 2 * 10^9`

---

## Observations

**1. Naive recursion is correct but slow.**

Define `F(n)` = minimum days to eat `n` oranges. Then:

$$
F(n) = 1 + \min \begin{cases} F(n-1) \\ F(n/2) & \text{if } 2 \mid n \\ F(n/3) & \text{if } 3 \mid n \end{cases}
$$

Without memoization this is exponential. Even with memoization, the `F(n-1)` branch forces us to evaluate every integer from `1` to `n` — O(n) states, which is too slow for `n` up to `2 * 10^9`.

**2. Bottom-up DP is O(n) — also too slow.**

Building `dp[0..n]` iteratively is correct but requires O(n) time and space, which is infeasible for `n = 2 * 10^9`.

**3. Key insight: eating 1 orange at a time is only useful as a "remainder reducer".**

The optimal strategy never wastes multiple days on single-orange eating in isolation. Instead, single-orange eating only makes sense to bring `n` to the nearest multiple of 2 or 3, so we can then apply a bulk-eat operation.

- To use the **divide-by-2** operation from `n`:  
  Eat `n % 2` oranges one by one (`n % 2` days), then apply operation 2 (1 day) → left with `n // 2`.  
  Total cost toward this branch: `(n % 2) + 1 + F(n // 2)`.

- To use the **divide-by-3** operation from `n`:  
  Eat `n % 3` oranges one by one (`n % 3` days), then apply operation 3 (1 day) → left with `n // 3`.  
  Total cost toward this branch: `(n % 3) + 1 + F(n // 3)`.

So the recurrence becomes:

$$
F(n) = 1 + \min\bigl(n \bmod 2 + F(\lfloor n/2 \rfloor),\; n \bmod 3 + F(\lfloor n/3 \rfloor)\bigr)
$$

**4. The number of unique states is O(log² n).**

Every recursive call divides `n` by 2 or 3. The complete set of reachable values from `n` is:

$$
\left\{ \left\lfloor \frac{n}{2^a \cdot 3^b} \right\rfloor : a \geq 0,\ b \geq 0 \right\}
$$

Since $a \leq \log_2 n$ and $b \leq \log_3 n$, there are at most $O(\log^2 n)$ distinct values. With memoization this gives **O(log² n) time complexity**, which is perfectly efficient for `n` up to `2 * 10^9`.

---

## Solution

```python
from functools import lru_cache

class Solution:
    def minDays(self, n: int) -> int:
        @lru_cache(None)
        def dfs(val: int) -> int:
            if val <= 1:
                return val          # 0 days for 0 oranges, 1 day for 1 orange
            return 1 + min(
                val % 3 + dfs(val // 3),   # eat (val%3) singles, then divide by 3
                val % 2 + dfs(val // 2)    # eat (val%2) singles, then divide by 2
            )

        return dfs(n)
```

### Step-by-step trace for `n = 10`

| Call | val | val%3 + dfs(val//3) | val%2 + dfs(val//2) | Result |
|------|-----|----------------------|----------------------|--------|
| dfs(10) | 10 | 1 + dfs(3) | 0 + dfs(5) | — |
| dfs(3)  |  3 | 0 + dfs(1) | 1 + dfs(1) | 1 + min(0+1, 1+1) = **2** |
| dfs(5)  |  5 | 2 + dfs(1) | 1 + dfs(2) | — |
| dfs(2)  |  2 | 2 + dfs(0) | 0 + dfs(1) | 1 + min(2+0, 0+1) = **2** |
| dfs(1)  |  1 | — | — | **1** |
| dfs(0)  |  0 | — | — | **0** |
| dfs(5)  |  5 | 2+1=3 | 1+2=3 | 1 + min(3, 3) = **4** |
| dfs(10) | 10 | 1+2=3 | 0+4=4 | 1 + min(3, 4) = **4** ✓ |

### Complexity

| | Time | Space |
|---|---|---|
| Naive recursion | O(3^n) | O(n) stack |
| Bottom-up DP | O(n) | O(n) |
| Memoized O(log²n) | **O(log² n)** | **O(log² n)** |
