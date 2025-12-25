## Problem

https://leetcode.com/problems/continuous-subarrays/description/

```
You are given a 0-indexed integer array nums. A subarray of nums is called continuous if:

Let i, i + 1, ..., j be the indices in the subarray. Then, for each pair of indices 
i <= i1, i2 <= j, we have 0 <= |nums[i1] - nums[i2]| <= 2.

Return the total number of continuous subarrays.

A subarray is a contiguous non-empty sequence of elements within an array.

Example 1:
Input: nums = [5,4,2,4]
Output: 8
Explanation: 
Continuous subarray of size 1: [5], [4], [2], [4].
Continuous subarray of size 2: [5,4], [4,2], [2,4].
Continuous subarray of size 3: [4,2,4].
Total continuous subarrays = 4 + 3 + 1 = 8.

Example 2:
Input: nums = [1,2,3]
Output: 6
Explanation: 
Continuous subarray of size 1: [1], [2], [3].
Continuous subarray of size 2: [1,2], [2,3].
Continuous subarray of size 3: [1,2,3].
Total continuous subarrays = 3 + 2 + 1 = 6.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
```

## Observations

1. **Key Insight**: A subarray is "continuous" if and only if the difference between the maximum and minimum elements in that subarray is at most 2. This is because:
   - If max - min <= 2, then for any two elements a, b in the subarray: |a - b| <= max - min <= 2 ✓
   - If max - min > 2, then |max - min| > 2 ✗

2. **Sliding Window Approach**: Since we need to find all valid subarrays, we can use a sliding window technique:
   - Expand the window to the right
   - Shrink from the left when the window becomes invalid (max - min > 2)
   - Count valid subarrays ending at each position

3. **Counting Subarrays**: For a valid window [left, right], the number of valid subarrays ending at position `right` is `(right - left + 1)` because we can start from any position in [left, right].

4. **Tracking Min/Max Efficiently**: We need to efficiently track the minimum and maximum in the current window as it expands and shrinks. Using heaps with lazy deletion is one approach.

## Solution

**Algorithm: Sliding Window with Two Heaps (Lazy Deletion)**

The solution uses a sliding window approach combined with two heaps to efficiently track the minimum and maximum values in the current window.

**Data Structures:**
- `pq_min`: Min heap to track the minimum element in the window
- `pq_max`: Max heap to track the maximum element in the window  
- `freq`: Hash map to track the count of each element in the current window (enables lazy deletion)
- `left`, `right`: Two pointers defining the current window

**Key Technique - Lazy Deletion:**
Instead of removing elements from the heaps immediately when shrinking the window, we:
1. Mark them as removed by decrementing their frequency to 0
2. Only remove them from the heap when they appear at the top (lazy deletion)

**Step-by-Step Process:**

1. **Expand Window**: For each position `right`:
   - Add `nums[right]` to both heaps
   - Increment its frequency in the hash map

2. **Shrink Window**: While the window is invalid (max - min > 2):
   - Clean up heap tops: Remove elements with freq = 0 from the tops of both heaps
   - Check if `max - min <= 2`; if yes, break
   - Otherwise, decrement `freq[nums[left]]` and increment `left`

3. **Count Subarrays**: Add `(right - left + 1)` to the result
   - This counts all valid subarrays ending at position `right`

**Time Complexity**: O(n log n)
- Each element is pushed to heaps once: O(n log n)
- Each element is popped from heaps at most once: O(n log n)
- Total operations: O(n log n)

**Space Complexity**: O(n)
- Heaps can contain at most n elements
- Frequency map can contain at most n distinct elements

**Example Walkthrough** (nums = [5,4,2,4]):

```
right=0, val=5: window=[5], max=5, min=5, diff=0 ✓, count=1, total=1
right=1, val=4: window=[5,4], max=5, min=4, diff=1 ✓, count=2, total=3
right=2, val=2: window=[5,4,2], max=5, min=2, diff=3 ✗
                shrink: window=[4,2], max=4, min=2, diff=2 ✓, count=2, total=5
right=3, val=4: window=[4,2,4], max=4, min=2, diff=2 ✓, count=3, total=8
```

# Tags
#sliding-window #heap #two-pointers #hash-map #lazy-deletion

