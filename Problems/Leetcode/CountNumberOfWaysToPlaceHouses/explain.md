## Problem

https://leetcode.com/problems/count-number-of-ways-to-place-houses/description

There is a street with `n * 2` plots — `n` plots on each side. On each plot, a house can optionally be placed. Return the **number of ways** to place houses such that **no two houses are adjacent on the same side of the street**, modulo `10^9 + 7`.

A house on plot `i` of one side does **not** block placement on plot `i` of the other side.

---

## Observations

1. **The two sides are independent.** Adjacency constraints only apply within the same side, not across sides. So the total count is simply:

$$\text{answer} = \text{ways}(n) \times \text{ways}(n)$$

where $\text{ways}(n)$ is the number of valid arrangements for a single row of $n$ plots.

2. **Single-row subproblem is a classic DP.** For a row of `n` plots, each plot is either empty or has a house, with no two consecutive houses. This is exactly the problem of counting binary strings of length `n` with no two consecutive `1`s.

3. **Recurrence:**
   - Let `dp[i]` = number of valid arrangements for `i` plots.
   - `dp[0] = 1` — one way to arrange 0 plots (empty).
   - `dp[1] = 2` — plot is either empty or has a house.
   - For `i >= 2`: if plot `i` is **empty**, the previous `i-1` plots can be anything valid → `dp[i-1]` ways. If plot `i` has a **house**, plot `i-1` must be empty → `dp[i-2]` ways.

$$dp[i] = dp[i-1] + dp[i-2]$$

   This is the **Fibonacci sequence** shifted by one: `dp = [1, 2, 3, 5, 8, ...]`.

---

## Solution Explanation

```python
class Solution:
    def countHousePlacements(self, n: int) -> int:
        mod = 10**9 + 7
        dp = [0] * (n + 1)
        dp[0] = 1
        dp[1] = 1
        for i in range(1, n + 1):
            dp[i] += dp[i - 1]
            if i - 2 >= 0:
                dp[i] += dp[i - 2]
            dp[i] %= mod
        return ((dp[n] % mod) * (dp[n] % mod)) % mod
```

**Step-by-step:**

- `dp[0] = 1`: base case — 0 plots, 1 way (do nothing).
- `dp[1] = 1` initially, then `dp[1] += dp[0]` → `dp[1] = 2`: 1 plot can be empty or occupied.
- For each `i` from `1` to `n`:
  - Add `dp[i-1]` (plot `i` is empty).
  - Add `dp[i-2]` if it exists (plot `i` is occupied, so plot `i-1` must be empty).
- The loop computes `dp[i] = dp[i-1] + dp[i-2]` in-place using the initial seed value of `dp[i] = 1` which is effectively adding `dp[i-2]` when `i=1` from `dp[-1]` edge case — but note `dp[1]` starts at `1` and then adds `dp[0]=1`, yielding `2`. This is equivalent to Fibonacci.
- Final answer: since the two sides are independent, multiply `dp[n]` by itself modulo `10^9 + 7`.

**Complexity:**
- Time: $O(n)$
- Space: $O(n)$ (reducible to $O(1)$ using two variables)
