## Problem

https://leetcode.com/problems/smallest-pair-with-different-frequencies/description/

````markdown
## Problem

https://leetcode.com/problems/smallest-pair-with-different-frequencies/description/

Given an integer array `nums`, find a pair of distinct values `(x, y)` where:
- `x < y`
- `x` and `y` appear with **different frequencies** in `nums`

Among all valid pairs, choose the one with:
1. The **smallest x** first
2. If there are ties on `x`, the **smallest y**

Return `[x, y]`. If no valid pair exists, return `[-1, -1]`.

**Example 1:**
- Input: `nums = [1,1,2,2,3,4]`
- Output: `[1, 3]`
- `1` has frequency 2, `3` has frequency 1 → different ✓

**Example 2:**
- Input: `nums = [1,5]`
- Output: `[-1, -1]`
- Both have frequency 1 → no valid pair

**Constraints:**
- `1 <= nums.length <= 100`
- `1 <= nums[i] <= 100`

## Observations

- We want the **smallest x** overall, so `x` must be the global minimum of the array (`nums[0]` after sorting).
- Once `x` is fixed as the minimum, we need the **smallest y > x** such that `freq(y) != freq(x)`.
- Since the array is sorted, iterating from index 1 onward gives us candidates in ascending order — the first one with a different frequency from `x` is our answer.
- There is no need to try any other `x` beyond the minimum, because:
  - The problem asks for the smallest possible `x`.
  - `x` must be a distinct value in `nums`, so sorting and taking index 0 gives the uniquely smallest candidate.
- If no element `y > x` with a different frequency exists, return `[-1, -1]`.

## Solution

```python
from collections import Counter

class Solution:
    def minDistinctFreqPair(self, nums: list[int]) -> list[int]:
        freq = Counter(nums)   # Step 1: count frequencies of all values
        nums.sort()            # Step 2: sort so smallest values come first
        n = len(nums)

        # Step 3: x is fixed as nums[0] (the globally smallest value).
        # Scan left-to-right for the first y with a different frequency.
        for i in range(1, n):
            if freq[nums[i]] != freq[nums[0]]:
                return [nums[0], nums[i]]

        return [-1, -1]
```

**Step-by-step walkthrough (Example 1):**

| Step | Action | State |
|------|--------|-------|
| `Counter` | Count frequencies | `{1:2, 2:2, 3:1, 4:1}` |
| `sort` | Sort array | `[1,1,2,2,3,4]` |
| `i=1` | `nums[1]=1`, `freq[1]=2 == freq[1]=2` | skip |
| `i=2` | `nums[2]=2`, `freq[2]=2 == freq[1]=2` | skip |
| `i=3` | `nums[3]=2`, same as above | skip |
| `i=4` | `nums[4]=3`, `freq[3]=1 != freq[1]=2` ✓ | return `[1, 3]` |

**Time complexity:** $O(n \log n)$ — dominated by sorting  
**Space complexity:** $O(n)$ — for the frequency counter

# Tags

`Array` `Hash Map` `Sorting` `Greedy`
````

## Observations

## Solution

# Tags

