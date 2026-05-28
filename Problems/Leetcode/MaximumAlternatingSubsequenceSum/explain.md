## Problem

````markdown
## Problem

https://leetcode.com/problems/maximum-alternating-subsequence-sum/description

Given an array `nums`, return the **maximum alternating sum** of any subsequence of `nums` (after reindexing the elements of the subsequence).

The **alternating sum** of a 0-indexed array is defined as the sum of elements at **even indices** minus the sum of elements at **odd indices**.

**Example 1:**
```
Input: nums = [4,2,5,3]
Output: 7
Explanation: Choose subsequence [4,2,5]. Alternating sum = (4 + 5) - 2 = 7.
```

**Example 2:**
```
Input: nums = [5,6,7,8]
Output: 8
Explanation: Choose subsequence [8]. Alternating sum = 8.
```

**Example 3:**
```
Input: nums = [6,2,1,2,4,5]
Output: 10
Explanation: Choose subsequence [6,1,5]. Alternating sum = (6 + 5) - 1 = 10.
```

**Constraints:**
- `1 <= nums.length <= 10^5`
- `1 <= nums[i] <= 10^5`

## Observations

1. **Subsequence reindexing**: When we pick a subsequence, its indices are reset to `0, 1, 2, ...`. So the first picked element is always at an even index (added), the second is at an odd index (subtracted), and so on alternately.

2. **Two states at each element**: At every element in `nums`, we are either:
   - **Ready to add** (next pick will be added, i.e., placed at an even index in the subsequence)
   - **Ready to subtract** (next pick will be subtracted, i.e., placed at an odd index)

3. **Greedy + DP insight**: We want to maximize `add - sub`. To do that:
   - When in the "add" state, we want to pick the highest possible value to add.
   - When in the "sub" state, we want to pick the lowest possible value to subtract — or skip it entirely.

4. **The pair pattern**: The maximum alternating sum always comes from picking pairs `(large, small)` — take a large value at an even position and a small value at an odd position. In fact, it simplifies to: for every increasing step in `nums`, capture `nums[i] - nums[i-1]`, and also grab the last peak.

5. **Key equivalence**: The answer equals the sum of `max(0, nums[i] - nums[i+1])` for each adjacent pair, plus `nums[last]` — but the DP state machine captures this naturally without needing to think about pairs explicitly.

6. **State transitions**: Let:
   - `add` = best alternating sum when the **next** element we pick will be **added** (even index)
   - `sub` = best alternating sum when the **next** element we pick will be **subtracted** (odd index)

   For each value `val` in `nums`:
   - Update `add`: we can either skip `val` (keep `add` as-is), or take `val` as the next even-index element — but we must be coming from a "sub" state: `sub + val`
   - Update `sub`: we can either skip `val` (keep `sub` as-is), or take `val` as the next odd-index element — but we must be coming from an "add" state: `add - val`

   Crucially, both updates must use the **old** values of `add` and `sub` simultaneously.

## Solution

### Approach: Greedy DP with Two States

**State Definition:**
- `add` = maximum alternating sum achievable so far, where the **next chosen element** will be placed at an **even index** (added)
- `sub` = maximum alternating sum achievable so far, where the **next chosen element** will be placed at an **odd index** (subtracted)

**Initial State:**
- `add = 0` — nothing picked yet, ready to add the first element
- `sub = 0` — nothing picked yet, but we're in the "ready to subtract" state (not yet reachable in practice, but `0` is a safe starting bound)

**Transition for each `val` in `nums`:**
```
new_add = max(add, sub + val)   # skip val, or add val (coming from sub state)
new_sub = max(sub, add - val)   # skip val, or subtract val (coming from add state)
```

Both sides use the **old** `add` and `sub`, so compute them simultaneously (or store old values first).

**Answer:** `max(add, sub)` — since we can end at either state; ending on an "add" state (last picked was added) is always at least as good.

**Time Complexity:** $O(n)$ — single pass through `nums`

**Space Complexity:** $O(1)$ — only two variables maintained

### Walkthrough: `nums = [4, 2, 5, 3]`

| val | old add | old sub | new add = max(add, sub+val) | new sub = max(sub, add-val) |
|-----|---------|---------|-----------------------------|-----------------------------|
|  4  |    0    |    0    | max(0, 0+4) = **4**         | max(0, 0-4) = **0**         |
|  2  |    4    |    0    | max(4, 0+2) = **4**         | max(0, 4-2) = **2**         |
|  5  |    4    |    2    | max(4, 2+5) = **7**         | max(2, 4-5) = **2**         |
|  3  |    7    |    2    | max(7, 2+3) = **7**         | max(2, 7-3) = **4**         |

Answer = `max(7, 4)` = **7** ✓

### Code Explanation

```python
class Solution:
    def maxAlternatingSum(self, nums: List[int]) -> int:
        add = 0  # best sum when next pick is at an even index (to be added)
        sub = 0  # best sum when next pick is at an odd index (to be subtracted)
        for val in nums:
            # Use old values of add and sub for both updates
            add = max(add, sub + val)
            sub = max(sub, add - val)
        return max(add, sub)
```

> **Note on ordering**: The line `sub = max(sub, add - val)` uses the **newly updated** `add`. This is safe because `add` was just set to `max(old_add, sub + val)`. If `add` was updated to `sub + val`, then `add - val = sub`, which means `sub` stays the same — a no-op. So the in-place update is equivalent to simultaneous update.

# Tags
Dynamic Programming | Greedy | State Machine | Array


````
