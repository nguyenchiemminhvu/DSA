## Problem

https://leetcode.com/problems/length-of-longest-subarray-with-at-most-k-frequency/description/

Given an integer array `nums` and an integer `k`, return the length of the longest **good** subarray of `nums`.

A subarray is called **good** if the frequency of each element in it is **≤ k**.

**Examples:**
- `nums = [1,2,3,1,2,3,1,2], k = 2` → `6` (subarray `[1,2,3,1,2,3]`)
- `nums = [1,2,1,2,1,2,1,2], k = 1` → `2` (subarray `[1,2]`)
- `nums = [5,5,5,5,5,5,5], k = 4` → `4` (subarray `[5,5,5,5]`)

**Constraints:**
- `1 <= nums.length <= 10^5`
- `1 <= nums[i] <= 10^9`
- `1 <= k <= nums.length`

---

## Observations

1. **Subarray problem with a frequency constraint** — this is a classic sliding window scenario. We want the longest contiguous window where no element appears more than `k` times.

2. **Monotonic window expansion**: As we extend the right pointer `r`, we only ever need to shrink the left pointer `l` when the newly added element `nums[r]` causes a violation (its frequency exceeds `k`). No other element can be in violation at that moment, because the window was valid before adding `nums[r]`.

3. **Key insight — only one element can violate at a time**: When we move `r` to include `nums[r]`, its count becomes `f[nums[r]] + 1`. All other elements already had frequency ≤ k before this step, so only `nums[r]` can be over the limit. This means we only need to check `f[nums[r]] > k` to decide whether to shrink — no need to scan all elements.

4. **Shrinking is targeted**: When shrinking (moving `l` forward), we decrement `f[nums[l]]`. We keep shrinking until `f[nums[r]] <= k`. Because only `nums[r]` is violating, shrinking stops as soon as its count drops back to `k`.

5. **O(n) time**: Each element is added once (right pointer) and removed at most once (left pointer), giving linear time with a hash map for frequency tracking.

---

## Solution Explanation

```python
from collections import defaultdict

class Solution:
    def maxSubarrayLength(self, nums: List[int], k: int) -> int:
        f = defaultdict(int)
        n = len(nums)
        res = 0
        l = 0
        for r in range(n):
            val = nums[r]
            f[val] += 1
            # Only val can be violating — shrink until it's back within limit
            while f[val] > k:
                f[nums[l]] -= 1
                l += 1
            res = max(res, r - l + 1)
        return res
```

**Step-by-step walkthrough:**

1. Maintain a sliding window `[l, r]` and a frequency map `f`.
2. Expand the window by moving `r` right and incrementing `f[nums[r]]`.
3. If `f[nums[r]] > k`, the window is invalid. Shrink from the left:
   - Decrement `f[nums[l]]` and advance `l`.
   - Repeat until `f[nums[r]] <= k`.
4. After restoring validity, update the result with the current window length `r - l + 1`.

**Why the inner `while` loop is safe (not O(n²)):** Even though it's a nested loop, `l` only moves forward — it never resets. Over the entire run, `l` advances at most `n` times total, so the combined work of all inner loop iterations is O(n).

**The commented-out heap approach** is a more general (but overkill) version that tracks the maximum frequency element via a min-heap. It works but has O(n log n) complexity and is much more complex to implement correctly (lazy deletion is needed to keep the heap consistent). The simple sliding window is strictly better here because of observation #3 — only one element can violate at a time.
