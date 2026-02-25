## Problem

https://leetcode.com/problems/max-consecutive-ones-iii/

Given a binary array `nums` and an integer `k`, return the maximum number of consecutive 1's in the array if you can flip at most `k` 0's.

**Example 1:**
```
Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
Output: 6
Explanation: [1,1,1,0,0,1,1,1,1,1,1]
```

**Example 2:**
```
Input: nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3
Output: 10
Explanation: [0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
```

**Constraints:**
- `1 <= nums.length <= 10^5`
- `nums[i]` is either `0` or `1`
- `0 <= k <= nums.length`

## Observations

- Flipping at most `k` zeros is equivalent to finding the **longest subarray that contains at most `k` zeros**.
- The problem reduces to: find the longest contiguous subarray where the number of 0's does not exceed `k`.
- A **sliding window** (two-pointer) approach is ideal here because:
  - The window can always grow to the right.
  - When the constraint is violated (too many 0's), we shrink from the left.
  - The window size at each step is a candidate for the answer.
- The window never needs to shrink below its maximum size seen so far — we just slide it forward.

## Solution

```python
class Solution:
    def longestOnes(self, nums: List[int], k: int) -> int:
        n = len(nums)
        res = 0
        count = [0] * 2   # count[0] = number of 0's in window, count[1] = number of 1's
        left = 0
        for right in range(n):
            count[nums[right]] += 1          # expand window to include nums[right]
            while count[0] > k:              # window has more than k zeros — invalid
                count[nums[left]] -= 1       # shrink from the left
                left += 1
            res = max(res, right - left + 1) # record the valid window size
        return res
```

**Step-by-step logic:**

1. Maintain a sliding window `[left, right]` and a frequency count of 0's and 1's inside it.
2. Extend `right` one step at a time, adding `nums[right]` to the window.
3. If the window now contains more than `k` zeros (`count[0] > k`), advance `left` until the window is valid again.
4. After each adjustment, the window `[left, right]` is the longest valid window ending at `right`. Update `res`.

**Complexity:**
- Time: O(n) — each element is added and removed from the window at most once.
- Space: O(1) — only a fixed-size count array and two pointers.

# Tags

`sliding-window` `two-pointers` `array`

