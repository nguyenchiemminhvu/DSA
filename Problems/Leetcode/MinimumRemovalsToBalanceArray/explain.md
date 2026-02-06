## Problem

https://leetcode.com/problems/minimum-removals-to-balance-array/

```
You are given an integer array nums and an integer k.

An array is considered balanced if the value of its maximum element is at most k times the minimum element.

You may remove any number of elements from nums without making it empty.

Return the minimum number of elements to remove so that the remaining array is balanced.

Note: An array of size 1 is considered balanced as its maximum and minimum are equal, and the condition always holds true.

Constraints:
- 1 <= nums.length <= 10^5
- 1 <= nums[i] <= 10^9
- 1 <= k <= 10^5
```

**Examples:**

Example 1:
- Input: nums = [2,1,5], k = 2
- Output: 1
- Explanation: Remove nums[2] = 5 to get nums = [2, 1]. Now max = 2, min = 1 and max <= min * k as 2 <= 1 * 2.

Example 2:
- Input: nums = [1,6,2,9], k = 3
- Output: 2
- Explanation: Remove nums[0] = 1 and nums[3] = 9 to get nums = [6, 2]. Now max = 6, min = 2 and max <= min * k as 6 <= 2 * 3.

Example 3:
- Input: nums = [4,6], k = 2
- Output: 0
- Explanation: nums is already balanced as 6 <= 4 * 2.

## Observations

1. **Balanced Array Condition**: An array is balanced if `max_element <= k * min_element`

2. **Key Insight - Sorted Array**: After sorting, any valid subarray that satisfies the balanced condition will be contiguous. This is because:
   - The minimum element will be at the left end of the subarray
   - The maximum element will be at the right end of the subarray
   - All elements in between will automatically satisfy the condition

3. **Greedy Approach**: We want to find the **longest contiguous subarray** in the sorted array that satisfies the balanced condition. The minimum removals = `n - max_subarray_length`

4. **Sliding Window**: Since the array is sorted, we can use a two-pointer/sliding window approach:
   - For each potential maximum (right pointer), find the leftmost minimum that satisfies `nums[left] * k >= nums[right]`
   - This gives us all valid subarrays ending at position `right`

5. **Why Sorting Works**: 
   - We only care about which elements to keep, not their original order
   - After sorting, checking the balanced condition becomes simple: just compare the first and last elements of the subarray

## Solution

**Algorithm:**

1. **Sort the array**: This allows us to use sliding window to find the longest valid contiguous subarray
2. **Use two pointers** (left and right):
   - `right` iterates through all possible maximum values
   - `left` maintains the minimum value such that `nums[left] * k >= nums[right]`
3. **Sliding window maintenance**:
   - When `nums[left] * k < nums[right]`, the window is invalid
   - Move `left` pointer to the right until the condition is satisfied
4. **Track the maximum valid window size**: The answer is `n - max_window_size`

**Time Complexity**: O(n log n)
- Sorting takes O(n log n)
- Two-pointer traversal takes O(n)

**Space Complexity**: O(1) or O(n) depending on the sorting algorithm

**Python Implementation:**

```python
class Solution:
    def minRemoval(self, nums: List[int], k: int) -> int:
        n = len(nums)
        nums.sort()  # Sort to make min/max checking easy
        
        res = n - 1  # Worst case: keep only 1 element
        l = 0        # Left pointer (minimum element)
        
        # Try each element as the maximum
        for r in range(1, n):
            # Shrink window from left while condition is violated
            # nums[l] must be the minimum that satisfies: nums[l] * k >= nums[r]
            while nums[l] * k < nums[r]:
                l += 1
            
            # Update result with current window size
            # Window size = (r - l + 1)
            # Elements to remove = n - window_size
            res = min(res, n - (r - l + 1))
        
        return res
```

**Step-by-Step Example (nums = [1,6,2,9], k = 3):**

After sorting: `[1, 2, 6, 9]`

```
r=1: nums[r]=2, l=0, nums[l]=1
     Check: 1*3 >= 2? Yes (3 >= 2) ✓
     Window: [1,2], size=2, removals=4-2=2

r=2: nums[r]=6, l=0, nums[l]=1
     Check: 1*3 >= 6? No (3 >= 6) ✗
     Move l to 1: 2*3 >= 6? Yes (6 >= 6) ✓
     Window: [2,6], size=2, removals=4-2=2

r=3: nums[r]=9, l=1, nums[l]=2
     Check: 2*3 >= 9? No (6 >= 9) ✗
     Move l to 2: 6*3 >= 9? Yes (18 >= 9) ✓
     Window: [6,9], size=2, removals=4-2=2

Result: min(2, 2, 2) = 2
```

# Tags
#array #two-pointers #sliding-window #sorting #greedy

