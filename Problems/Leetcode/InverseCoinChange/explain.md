## Problem

https://leetcode.com/problems/inverse-coin-change/description

Given a 1-indexed integer array `numWays`, where `numWays[i]` is the number of ways to select coins totalling exactly `i` using an **infinite supply** of some fixed coin denominations (each denomination is a positive integer ≤ `numWays.length`), recover the set of denominations that could have produced it.

Return a sorted array of the unique denominations, or an empty array if no valid set exists.

**Constraints:** `1 <= numWays.length <= 100`, `0 <= numWays[i] <= 2 * 10^8`

---

## Observations

**1. The forward problem (Coin Change Counting).**
Given a coin set, you build `dp[0..n]` where `dp[0] = 1` and for each coin `c`:
```
for j = c to n:
    dp[j] += dp[j - c]
```
Processing left-to-right makes this **unbounded** — coin `c` can be used multiple times, because `dp[j-c]` has already been incremented in the same pass.

**2. The inverse: recover coins from `dp`.**
Suppose we scan candidate coin `c` from `1` to `n` and have already **undone** the effect of every coin already found (all coins `< c`). At this moment, `dp[c]` equals the number of ways to make amount `c` using only coins `≥ c`. But any denomination `d > c` cannot form amount `c` on its own (too large), so:

- `dp[c] == 1` → `c` **is** a denomination (the only way is the single coin `c` itself)
- `dp[c] == 0` → `c` is **not** a denomination

**3. Undoing a coin's effect (reverse DP pass).**
The forward pass for coin `c` goes left-to-right and is equivalent to:
```
dp[j] = dp[j] + dp[j-c]   (j = c … n, left to right)
```
To reverse it, go **right-to-left**:
```
dp[j] = dp[j] - dp[j-c]   (j = n … c, right to left)
```
Going right-to-left ensures `dp[j-c]` has not yet been modified in the reverse pass, so it still holds the "post-forward" value that was added during the forward pass.

**4. Validity check.**
After undoing every found coin, all remaining `dp[1..n]` values should be `0` (no unexplained ways). If `sum(dp[1:]) != 0`, the given `numWays` array is inconsistent and we return `[]`.

---

## Solution

```python
class Solution:
    def findCoins(self, dp: List[int]) -> List[int]:
        dp = [1] + dp   # prepend dp[0] = 1 (empty selection base case)
        ndp = len(dp)

        res = []
        for c in range(1, ndp):
            if dp[c] == 1:          # c is a denomination
                res.append(c)
                # undo the contribution of coin c (right-to-left reverse DP)
                for j in range(ndp - 1, c - 1, -1):
                    dp[j] -= dp[j - c]

        return res if sum(dp[1:]) == 0 else []
```

**Step-by-step on Example 1** (`numWays = [0,1,0,2,0,3,0,4,0,5]`, expected `[2,4,6]`):

| Candidate `c` | `dp[c]` | Action |
|---|---|---|
| 1 | 0 | skip |
| 2 | 1 | add 2, undo coin 2 |
| 3 | 0 | skip |
| 4 | 1 | add 4, undo coin 4 |
| 5 | 0 | skip |
| 6 | 1 | add 6, undo coin 6 |
| 7–10 | 0 | skip |

After undoing all three coins, `dp[1:] = [0,…,0]` → return `[2, 4, 6]`. ✓

**Complexity:** `O(n²)` time, `O(n)` space.
