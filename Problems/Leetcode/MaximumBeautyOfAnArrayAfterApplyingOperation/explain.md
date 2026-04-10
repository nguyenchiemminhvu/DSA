## Problem

https://leetcode.com/problems/maximum-beauty-of-an-array-after-applying-operation/description/

You are given a 0-indexed array `nums` and a non-negative integer `k`.

In one operation, you can choose an index `i` (only once per index) and replace `nums[i]` with any integer in the range `[nums[i] - k, nums[i] + k]`.

The **beauty** of the array is the length of the longest subsequence of equal elements.

Return the maximum possible beauty after applying operations any number of times.

### Constraints
- `1 <= nums.length <= 10^5`
- `0 <= nums[i], k <= 10^5`

### Examples
- Input: `nums = [4,6,1,2], k = 2` → Output: `3`
  - Replace index 1 with 4 → `[4,4,1,2]`
  - Replace index 3 with 4 → `[4,4,1,4]`
  - Three equal elements (4) can form a subsequence

- Input: `nums = [1,1,1,1], k = 10` → Output: `4`
  - All elements are already equal

## Observations

1. **Sorting enables range checking**: If we sort the array, we can use a sliding window to find contiguous groups of elements that can be made equal.

2. **Range overlap condition**: After sorting, elements in a range `[left, right]` can all be made equal to the same value if and only if `nums[right] - nums[left] <= 2*k`.
   - Why? An element `nums[i]` can become any value in `[nums[i] - k, nums[i] + k]`
   - If `nums[right] - nums[left] <= 2*k`, then:
     - `nums[left]` can reach up to `nums[left] + k`
     - `nums[right]` can reach down to `nums[right] - k`
     - Since `nums[right] - k <= nums[left] + k` (when difference ≤ 2k), there's a common value both can reach

3. **Sliding window application**: Use a two-pointer sliding window to find the maximum contiguous subarray (after sorting) where the difference between max and min is at most `2*k`. This subarray size is the maximum possible beauty.

## Solution

**Approach**: Sliding Window on Sorted Array

```python
class Solution:
    def maximumBeauty(self, nums: List[int], k: int) -> int:
        nums.sort()  # Step 1: Sort array
        
        n = len(nums)
        res = 0
        left = 0
        
        # Step 2: Sliding window to find max contiguous range with diff <= 2*k
        for right in range(n):
            # Shrink window while difference exceeds 2*k
            while nums[right] - nums[left] > 2 * k:
                left += 1
            # Track maximum window size
            res = max(res, right - left + 1)
        
        return res
```

**Time Complexity**: `O(n log n)` for sorting + `O(n)` for sliding window = `O(n log n)`

**Space Complexity**: `O(1)` if we don't count the space used by sorting

**Algorithm Walkthrough** (Example: `nums = [4,6,1,2], k = 2`):
1. Sort: `[1, 2, 4, 6]`
2. Iteration:
   - `right=0 (1)`: window `[0,0]`, diff=0 ≤ 4 ✓, size=1
   - `right=1 (2)`: window `[0,1]`, diff=1 ≤ 4 ✓, size=2
   - `right=2 (4)`: window `[0,2]`, diff=3 ≤ 4 ✓, size=3
   - `right=3 (6)`: window `[0,3]`, diff=5 > 4 ✗, move left to 1, diff=4 ≤ 4 ✓, size=3
3. Answer: `3`

# Tags
- Sliding Window
- Two Pointers
- Sorting
- Array

