## Problem

https://leetcode.com/problems/longest-arithmetic-subsequence/description

Given an array `nums` of integers, return the length of the **longest arithmetic subsequence** in `nums`.

- A **subsequence** is derived by deleting some or no elements without changing the order of remaining elements.
- A sequence `seq` is **arithmetic** if `seq[i+1] - seq[i]` is the same value for all valid `i`.

**Examples:**
- `[3,6,9,12]` → `4` (the whole array, diff = 3)
- `[9,4,7,2,10]` → `3` (`[4,7,10]`, diff = 3)
- `[20,1,15,3,10,5,8]` → `4` (`[20,15,10,5]`, diff = -5)

**Constraints:** `2 <= nums.length <= 1000`, `0 <= nums[i] <= 500`

## Observations

1. **Subsequence, not subarray.** Elements don't need to be contiguous, so we must consider all pairs `(j, i)` with `j < i`.

2. **An arithmetic sequence is defined by its difference.** Any two elements `nums[j]` and `nums[i]` (with `j < i`) can start or extend an arithmetic subsequence with `diff = nums[i] - nums[j]`. The diff uniquely characterizes the sequence.

3. **Extending a sequence at index `i` requires knowing the last diff.** To extend a subsequence ending at `j` with difference `diff`, we need `nums[i] - nums[j] == diff`. This naturally suggests a DP state `(index, diff)`.

4. **The diff can be negative, zero, or positive.** Using a hash map (dictionary) per index to store diffs is the right data structure — the range of diffs can be wide.

5. **A single element is a trivial arithmetic sequence of length 1; two elements always form one of length 2.** So any pair `(j, i)` contributes at least length 2.

## Solution

### Approach 1 — Top-down Memoization (commented out)

Define `F(i, diff)` = length of the longest arithmetic subsequence ending at index `i` with common difference `diff`.

**Recurrence:**
$$F(i, \text{diff}) = 1 + \max_{j < i,\ nums[i]-nums[j]=\text{diff}} F(j, \text{diff})$$

Base: if no such `j` exists, `F(i, diff) = 1`.

We memoize on `(i, diff)`. For each `i`, we try all `j < i` and recurse. The answer is `max over all (i, diff) of F(i, diff)`.

**Complexity:** $O(n^2)$ states × $O(n)$ work per state without careful memoization, but with memoization each `(i, diff)` pair is computed once → effectively $O(n^2)$ time overall, $O(n^2)$ space.

---

### Approach 2 — Bottom-up DP (the actual solution)

**State:** `dp[i][diff]` = length of the longest arithmetic subsequence ending at index `i` with common difference `diff`.

**Transition:** For each pair `(j, i)` with `j < i`:
```
diff = nums[i] - nums[j]

if diff not in dp[j]:      # j is the start of a new 2-element sequence
    dp[i][diff] = 2
else:                      # extend the existing sequence ending at j
    dp[i][diff] = dp[j][diff] + 1
```

Why `2` and not `1 + dp[j][diff]` when `diff not in dp[j]`?  
Because `dp[j][diff]` being absent means no sequence ending at `j` with that diff was recorded yet — `j` itself would be a "fresh" start, so the sequence `[nums[j], nums[i]]` has length 2. Setting `dp[i][diff] = 2` is equivalent to `1 (for j) + 1 (for i)`.

**Answer:** `max(dp[i][diff])` over all `i` and all diffs.

**Walk-through on `[9,4,7,2,10]`:**

| i | j | nums[j]→nums[i] | diff | dp[i][diff] |
|---|---|-----------------|------|-------------|
| 1 | 0 | 9→4 | -5 | 2 |
| 2 | 0 | 9→7 | -2 | 2 |
| 2 | 1 | 4→7 | +3 | 2 |
| 3 | 0 | 9→2 | -7 | 2 |
| 3 | 1 | 4→2 | -2 | 2 |
| 3 | 2 | 7→2 | -5 | dp[1][-5]+1 = **3** (sequence 9,4,2) |
| 4 | 0 | 9→10| +1 | 2 |
| 4 | 1 | 4→10| +6 | 2 |
| 4 | 2 | 7→10| +3 | dp[2][3]+1 = **3** (sequence 4,7,10) ✓ |
| 4 | 3 | 2→10| +8 | 2 |

Result: `3` ✓

**Complexity:**
- Time: $O(n^2)$ — two nested loops over all pairs
- Space: $O(n \cdot D)$ where $D$ is the number of distinct diffs, at most $O(n^2)$ in the worst case

```python
class Solution:
    def longestArithSeqLength(self, nums: List[int]) -> int:
        n = len(nums)
        res = 0
        dp = [defaultdict(int) for _ in range(n)]

        for i in range(n):
            for j in range(i):
                diff = nums[i] - nums[j]

                if diff not in dp[j]:
                    dp[i][diff] = 2
                else:
                    dp[i][diff] = max(dp[i][diff], dp[j][diff] + 1)

                res = max(res, dp[i][diff])

        return res
```

## Tags

`Dynamic Programming` `Hash Map` `Subsequence`

