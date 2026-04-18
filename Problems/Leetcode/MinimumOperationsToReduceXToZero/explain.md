## Problem

https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/description/

Given an integer array `nums` and an integer `x`, in one operation you can either remove the leftmost or rightmost element from the array and subtract its value from `x`.

**Task:** Return the minimum number of operations to reduce `x` to exactly 0. If impossible, return -1.

**Examples:**
- `nums = [1,1,4,2,3], x = 5` → Output: 2 (remove [3, 2] from right)
- `nums = [5,6,7,8,9], x = 4` → Output: -1 (impossible)
- `nums = [3,2,20,1,1,3], x = 10` → Output: 5 (remove [3,2] from left and [3,1,1] from right)

## Observations

1. **Key Insight - Complement Problem:** Instead of thinking "which elements to remove", think "which contiguous subarray in the middle to keep". If we remove all elements except a middle subarray, those removed elements must sum to `(total_sum - x)`.

2. **Transform to Subarray Problem:** The minimum operations equals `n - longest_middle_subarray_length`, where the longest subarray has sum equal to `(total_sum - x)`.

3. **Edge Cases:**
   - If `total_sum < x`, impossible (return -1)
   - If `total_sum == x`, remove all elements (return n)
   - If target sum is 0, find the longest empty subarray (length 0)

4. **Sliding Window Applicability:** Since all numbers are positive (≥1), we can use a two-pointer sliding window to find the longest contiguous subarray with a specific sum.

## Solution

**Approach: Two-Pointer Sliding Window**

**Key Insight:** We only remove from the left and right ends. So valid operations consist of removing a **prefix + suffix**. The elements we keep form a contiguous **middle subarray**.

To make x = 0, we need: `x - (sum of removed elements) = 0`, so `sum of removed = x`.

Therefore: `sum of kept middle = total_sum - x`

The minimum operations = minimum elements to remove = `n - maximum_middle_length` where the middle subarray has sum = `(total_sum - x)`.

**Algorithm:**
1. Calculate `target = total_sum - x`
2. If `target < 0`, return -1 (impossible)
3. Use **two-pointer sliding window** to find the longest contiguous subarray with sum = `target`
4. Return `n - longest_length`

**Why Sliding Window Works:**
- All array elements are positive (≥1), so the sum is monotonically increasing as we expand the window
- When current sum exceeds target, shrink from left until sum ≤ target
- Track the maximum window size where sum equals target exactly

**Complexity:**
- Time: **O(n)** - each element visited at most twice (right pointer advances once, left pointer advances once)
- Space: **O(1)** - only constant variables

**Code Walkthrough:**
```python
def minOperations(self, nums: List[int], x: int) -> int:
    n = len(nums)
    s = sum(nums)
    if s < x:  # total sum less than x, impossible
        return -1
    
    s_sub = s - x  # target middle sum
    
    longest = -1
    cur_s = 0
    left = 0
    for right in range(n):
        cur_s += nums[right]  # expand window
        while cur_s > s_sub:  # shrink if sum too large
            cur_s -= nums[left]
            left += 1
        if cur_s == s_sub:  # found matching subarray
            longest = max(longest, right - left + 1)
    
    return -1 if longest == -1 else n - longest
```

**Trace Example:** `nums = [1,1,4,2,3], x = 5`
- total_sum = 11, target = 6
- Find longest middle subarray with sum 6:
  - [1,1,4] (indices 0-2, length 3) ← **longest**
  - [4,2] (indices 2-3, length 2)
- Remove n - longest = 5 - 3 = **2 elements** (the suffix [3,2])
- Verify: x - (3+2) = 5 - 5 = 0 ✓


# Tags

