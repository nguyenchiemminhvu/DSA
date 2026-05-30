## Problem

https://leetcode.com/problems/longest-square-streak-in-an-array/description

Given an integer array `nums`, a **square streak** is a subsequence where:
- Its length is at least `2`, and
- After sorting, each element (except the first) is the **square** of the previous one.

Return the length of the **longest square streak**, or `-1` if none exists.

**Example 1:**
```
Input:  nums = [4,3,6,16,8,2]
Output: 3
# [2, 4, 16] — 4=2², 16=4²
```

**Example 2:**
```
Input:  nums = [2,3,5,6,7]
Output: -1
```

**Constraints:**
- `2 <= nums.length <= 10^5`
- `2 <= nums[i] <= 10^5`

---

## Observations

1. **Order doesn't matter for construction.** Because we only care about the *set* of values present, not their positions, we can sort freely and use a hash set for O(1) lookups.

2. **Each streak is a chain: x → x² → x⁴ → …** Starting from any element `x`, the next element must be `x²`, then `x⁴`, and so on. The chain grows as long as the next square exists in `nums`.

3. **Start from the smallest element in each chain.** If we start from a middle element (e.g., `4` when `2` is also present), we'd double-count. Starting from the smallest root of a chain avoids overlap and ensures we measure the full length.
   - The solution handles this cleverly by **sorting descending** and inserting into the set one by one. When we process `x`, only elements `>= x` are in the set. So `x²` being in the set means `x` is indeed the smallest so far — we are always extending forward, never backward.

4. **Squaring grows very fast.** Even starting from `2`, the chain is at most `2 → 4 → 16 → 256 → 65536 → (> 10^5)`, so the inner `while` loop runs at most ~17 times regardless of input size.

---

## Solution Explanation

```python
class Solution:
    def longestSquareStreak(self, nums: List[int]) -> int:
        n = len(nums)
        nums.sort(reverse=True)   # process large → small

        longest = -1

        s = set()
        for val in nums:          # iterate large → small
            s.add(val)            # add val BEFORE checking, so val itself is in s

            length = 1
            p = val
            while p * p in s:    # walk the chain: val → val² → val⁴ → …
                p = p * p
                length += 1

            if length >= 2:
                longest = max(longest, length)

        return longest
```

### Step-by-step walkthrough (Example 1: `[4,3,6,16,8,2]`)

Sorted descending: `[16, 8, 6, 4, 3, 2]`

| Iteration | `val` | Set `s` after insert | Chain starting at `val` | Length |
|-----------|-------|----------------------|-------------------------|--------|
| 1 | 16 | {16} | 16 → (256 ✗) | 1 |
| 2 | 8  | {16,8} | 8 → (64 ✗) | 1 |
| 3 | 6  | {16,8,6} | 6 → (36 ✗) | 1 |
| 4 | 4  | {16,8,6,4} | 4 → 16 → (256 ✗) | **2** |
| 5 | 3  | {16,8,6,4,3} | 3 → (9 ✗) | 1 |
| 6 | 2  | {16,8,6,4,3,2} | 2 → 4 → 16 → (256 ✗) | **3** |

Result: `3` ✓

### Why sorting descending + incremental insert works

When we process `val = 2`, the set already contains `4` and `16` (they were inserted in earlier iterations). So the chain `2 → 4 → 16` is detected correctly.

When we processed `val = 4`, the set did **not** yet contain `2`. So the check `2² = 4 ∈ s` would have started the chain at `4` (length 2), not at `2`. This prevents double-counting: the full chain length is only reported when we reach the true minimum (`2`).

### Complexity

| | |
|---|---|
| Time | O(n log n) — sort + O(n · 17) loop iterations |
| Space | O(n) — hash set |
