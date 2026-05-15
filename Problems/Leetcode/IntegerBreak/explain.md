## Problem

https://leetcode.com/problems/integer-break/description

Given a positive integer `n`, partition it into `k` positive integers (where `k >= 2`) and maximize their product.

**Examples:**
- Input: `n = 2` → Output: `1` (2 = 1 + 1, product = 1 × 1 = 1)
- Input: `n = 10` → Output: `36` (10 = 3 + 3 + 4, product = 3 × 3 × 4 = 36)

**Constraints:** 2 ≤ n ≤ 58

## Observations

1. **Must split**: We cannot return `n` itself—we must break it into at least 2 parts. This constraint is critical.

2. **State representation**: We need to track whether we've already "split" the number:
   - `dp[i][0]` = max product when treating `i` as a single unsplit unit (not allowed as final answer, but useful for subproblems)
   - `dp[i][1]` = max product when `i` is properly split into k ≥ 2 parts

3. **Split choices**: For each number `i`, we try splitting it as `l + r = i` where `1 ≤ l ≤ r < i`, then consider:
   - `l * r`: both parts as whole numbers (neither further split)
   - `dp[l][1] * r`: left part optimally split, right as whole
   - `l * dp[r][1]`: right part optimally split, left as whole
   - `dp[l][1] * dp[r][1]`: both parts optimally split

4. **Why all 4 combinations?** Because we need to explore whether it's better to further decompose each part or keep it whole.

5. **Base case**: `dp[1][0] = dp[1][1] = 1` (minimum unit, product is itself)

## Solution

**Approach: Dynamic Programming (Bottom-Up)**

Use a 2D DP table where `dp[i][splitted]` represents the maximum product:
- `splitted = 0`: treat `i` as one unsplit unit
- `splitted = 1`: `i` has been split into k ≥ 2 parts

```python
dp = [[0 for _ in range(2)] for _ in range(n + 1)]
dp[1][0] = dp[1][1] = 1

for i in range(2, n + 1):
    for splitted in range(2):
        # Initialize with the number itself (if splitted=1) or 1 (if splitted=0)
        dp[i][splitted] = i if splitted == 1 else 1
        
        # Try all possible splits: i = l + r
        l, r = 1, i - 1
        while l <= r:
            # Consider all 4 combinations of split/no-split for l and r
            dp[i][splitted] = max(
                dp[i][splitted],
                l * r,                      # both whole
                dp[l][1] * r,               # left split, right whole
                l * dp[r][1],               # left whole, right split
                dp[l][1] * dp[r][1]         # both split
            )
            l += 1
            r -= 1

return dp[n][False]  # Must split n itself
```

**Why `return dp[n][False]`?** The state `False` (or 0) means "i as an unsplit unit", but within the DP we've ensured that this unit was obtained by splitting. This returns the maximum product of at least k ≥ 2 parts.

**Time Complexity:** O(n²) — for each number from 2 to n, we try O(n) splits.
**Space Complexity:** O(n) — 2D array of size (n+1) × 2.

# Tags
- Dynamic Programming
- Optimization
- Integer Partitioning

