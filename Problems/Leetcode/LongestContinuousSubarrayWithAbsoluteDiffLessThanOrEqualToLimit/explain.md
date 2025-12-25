## Problem

https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/description/

```
Given an array of integers nums and an integer limit, return the size of the longest 
non-empty subarray such that the absolute difference between any two elements of this 
subarray is less than or equal to limit.

Example 1:
Input: nums = [8,2,4,7], limit = 4
Output: 2 
Explanation: The subarray [4,7] has maximum absolute diff |4-7| = 3 <= 4.

Example 2:
Input: nums = [10,1,2,4,7,2], limit = 5
Output: 4 
Explanation: The subarray [2,4,7,2] has maximum absolute diff |2-7| = 5 <= 5.

Example 3:
Input: nums = [4,2,2,2,4,4,2,2], limit = 0
Output: 3

Constraints:
- 1 <= nums.length <= 10^5
- 1 <= nums[i] <= 10^9
- 0 <= limit <= 10^9
```

## Observations

1. **Key Insight**: For a subarray to satisfy the condition, the difference between the **maximum** and **minimum** elements in that subarray must be ≤ limit.

2. **Sliding Window**: Since we're looking for a contiguous subarray, we can use a sliding window approach:
   - Expand the window by adding elements from the right
   - Shrink from the left when the condition is violated

3. **Tracking Min/Max**: We need to efficiently:
   - Track the minimum and maximum values in the current window
   - Remove elements from consideration when they leave the window

4. **Why Two Heaps**: 
   - A min heap tracks the minimum value in the window
   - A max heap tracks the maximum value in the window
   - This allows O(log n) insertion

5. **Lazy Deletion**: Instead of removing elements from heaps immediately when they leave the window (which is expensive), we:
   - Use a frequency map to mark elements as "logically deleted"
   - Only physically remove them from heap tops when we need to access the actual min/max

## Solution

### Algorithm

1. **Data Structures**:
   - `pq_min`: Min heap to track minimum values
   - `pq_max`: Max heap to track maximum values  
   - `freq`: Frequency map to track which elements are still in the window

2. **Sliding Window Process**:
   - Expand window: Add `nums[right]` to both heaps and increment its frequency
   - Check validity: Clean heap tops by removing elements with `freq = 0`
   - Shrink window: While `max - min > limit`, decrement `freq[nums[left]]` and move `left++`
   - Update result: Track maximum window size

3. **Lazy Deletion Details**:
   - When we move `left` pointer, we decrement frequency but DON'T remove from heaps
   - When accessing heap tops, we first pop all elements with `freq = 0`
   - This ensures heap tops always reflect actual min/max in current window

### Complexity

- **Time**: O(n log n)
  - Each element is pushed once to each heap: O(n log n)
  - Each element is popped at most once from each heap: O(n log n)
  - Total: O(n log n)

- **Space**: O(n)
  - Both heaps can contain up to n elements
  - Frequency map stores up to n unique elements

### Why This Works

The key property: **max(window) - min(window) ≤ limit** is equivalent to saying all pairwise differences are ≤ limit. By maintaining the min and max efficiently with heaps and lazy deletion, we can check this property in O(log n) time per window update.

# Tags
`sliding-window` `heap` `two-pointers` `monotonic-queue` `array` `ordered-map`

