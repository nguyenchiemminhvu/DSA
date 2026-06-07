## Problem

https://leetcode.com/problems/count-complete-subarrays-in-an-array/description/

Given an array `nums` of positive integers, return the number of **complete subarrays** — subarrays whose number of distinct elements equals the number of distinct elements in the entire array.

**Example:**
```
nums = [1,3,1,2,2]  →  4 complete subarrays
  [1,3,1,2], [1,3,1,2,2], [3,1,2], [3,1,2,2]
```

---

## Solution: Sliding Window

**Key insight:** Count the total distinct elements in the full array. Then use a sliding window `[l, r]` — whenever the window contains all distinct elements, every extension to the right (from `r` to `n-1`) also forms a complete subarray, so we can add `n - r` to the result without iterating further. We then shrink from the left to find more valid windows.

**Algorithm:**

1. Count distinct elements in the full array → `fn`.
2. Expand the right pointer `r`, adding `nums[r]` to the window counter `fa`.
3. When `len(fa) == len(fn)` (window is complete):
   - All subarrays starting at `l` and ending at `r, r+1, ..., n-1` are complete → add `n - r`.
   - Remove `nums[l]` from the window, advance `l`.
   - Repeat while the window is still complete.

```python
class Solution:
    def countCompleteSubarrays(self, nums: List[int]) -> int:
        n = len(nums)
        fn = Counter(nums)        # distinct count of the full array

        res = 0
        l = 0
        fa = Counter()            # sliding window frequency map
        for r in range(n):
            fa[nums[r]] += 1

            while len(fa) == len(fn):   # window is complete
                res += n - r            # subarrays [l..r], [l..r+1], ..., [l..n-1]

                fa[nums[l]] -= 1
                if fa[nums[l]] <= 0:
                    fa.pop(nums[l])
                l += 1

        return res
```

**Complexity:**
- Time: $O(n)$ — each element is added and removed from the window at most once.
- Space: $O(k)$ — where $k$ is the number of distinct elements.
