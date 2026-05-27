## Problem

https://leetcode.com/problems/number-of-ways-to-stay-in-the-same-place-after-some-steps/description

````markdown
## Problem

https://leetcode.com/problems/number-of-ways-to-stay-in-the-same-place-after-some-steps/description

You have a pointer starting at index `0` in an array of size `arrLen`. At each step, you can:
- Move 1 position to the **left**
- Move 1 position to the **right**
- **Stay** in the same place

The pointer must never go outside the array boundaries. Given two integers `steps` and `arrLen`, return the **number of ways** such that your pointer is back at index `0` after **exactly** `steps` steps. Since the answer may be very large, return it modulo `10^9 + 7`.

**Constraints:**
- `1 <= steps <= 500`
- `1 <= arrLen <= 10^6`

## Observations

1. **State space:** The state is `(position, remaining_steps)`. We want `F(0, steps)` — the number of ways to reach index `0` starting from index `0` using exactly `steps` moves.

2. **Reachable positions are bounded:** Even though `arrLen` can be up to `10^6`, the pointer can travel at most `steps/2` positions away from `0` and still return in the remaining steps. So the effective array width we need to consider is `min(arrLen, steps // 2 + 1)`. This is a critical optimization that keeps the DP table small (at most `251` columns for `steps = 500`).

3. **Overlapping subproblems:** The recursive formulation recomputes the same `(position, remaining_steps)` states many times, making memoization (top-down DP) or a bottom-up table essential.

4. **Transition:** From any position `i` with `k` steps remaining, we can come from `i-1`, `i`, or `i+1` (all within bounds) using 1 step. This means: `dp[i] = dp[i-1] + dp[i] + dp[i+1]` (from the previous step's values).

## Solution

We use **bottom-up dynamic programming** with a 1D rolling array.

**Key insight — shrink the array width:**  
To end at index `0` after `steps` steps, the furthest right we could ever need to go is `steps // 2` (go right `steps/2` times, then come back left `steps/2` times — any remaining steps are spent staying). So we cap `m = min(arrLen, steps // 2 + 1)`.

**DP definition:**  
`dp[i]` = number of ways to be at position `i` after the current number of steps processed so far.

**Initialization:**  
`dp[0] = 1` (we start at index `0`), all others `0`.

**Transition (for each step):**  
For each position `i`, the current `dp[i]` ways contribute to three positions in the next step:
- `nxt[i]` += `dp[i]`   (stay)
- `nxt[i-1]` += `dp[i]`  (move left)
- `nxt[i+1]` += `dp[i]`  (move right)

After `steps` iterations, `dp[0]` holds the answer.

**Complexity:**
- Time: `O(steps × m)` where `m = min(arrLen, steps/2 + 1)` → at most `O(500 × 251)` ≈ `O(125,500)`
- Space: `O(m)`

```python
class Solution:
    def numWays(self, steps: int, n: int) -> int:
        mod = 10**9 + 7

        m = min(n, steps // 2 + 1)
        dp = [0] * m
        dp[0] = 1

        for _ in range(steps):
            nxt = [0] * m
            for i in range(m):
                nxt[i] = (nxt[i] + dp[i]) % mod            # stay
                if i - 1 >= 0:
                    nxt[i - 1] = (nxt[i - 1] + dp[i]) % mod  # move left
                if i + 1 < m:
                    nxt[i + 1] = (nxt[i + 1] + dp[i]) % mod  # move right
            dp = nxt

        return dp[0]
```

**Why the top-down (memoized) approach also works:**  
The commented-out recursive solution defines `F(i, k)` = number of ways to reach index `0` from position `i` in exactly `k` steps. It recurses into all neighbors and memoizes with `(i, k)` as the key. Both approaches are correct; the bottom-up version avoids recursion overhead and call-stack depth issues.

# Tags

`Dynamic Programming` `Memoization` `Array`
````

## Observations

## Solution

# Tags

