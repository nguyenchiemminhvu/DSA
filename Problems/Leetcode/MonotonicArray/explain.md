## Problem

https://leetcode.com/problems/monotonic-array/description/

```
An array is monotonic if it is either monotone increasing or monotone decreasing.

An array nums is monotone increasing if for all i <= j, nums[i] <= nums[j]. An array nums is monotone decreasing if for all i <= j, nums[i] >= nums[j].

Given an integer array nums, return true if the given array is monotonic, or false otherwise.

Example 1:

Input: nums = [1,2,2,3]
Output: true

Example 2:

Input: nums = [6,5,4,4]
Output: true

Example 3:

Input: nums = [1,3,2]
Output: false

Constraints:

1 <= nums.length <= 105
-105 <= nums[i] <= 105
```

## Observations

1. **Problem Understanding**: An array is monotonic if it's either entirely non-decreasing or entirely non-increasing.
   - Monotone increasing: `nums[i] <= nums[j]` for all `i <= j`
   - Monotone decreasing: `nums[i] >= nums[j]` for all `i <= j`

2. **Key Insights**:
   - Single element arrays are always monotonic
   - Equal adjacent elements don't break monotonicity in either direction
   - We need to determine the overall trend (increasing or decreasing) and check consistency
   - The overall trend can be determined by comparing first and last elements

3. **Edge Cases**:
   - Array with length 1: Always monotonic
   - Arrays with all equal elements: Always monotonic
   - Arrays where first and last elements are equal but middle elements vary

4. **Algorithm Strategy**:
   - Determine expected trend using first and last elements
   - Iterate through array and check if any adjacent pair violates the trend
   - Only check non-equal adjacent pairs (equal pairs don't affect monotonicity)

## Solution

The solution uses a clever approach to determine monotonicity in a single pass:

### Algorithm Explanation:

1. **Base Case**: If array has only one element, return `True` (trivially monotonic)

2. **Determine Overall Trend**:
   ```python
   sign = (nums[-1] - nums[0]) >= 0
   ```
   - If `nums[-1] >= nums[0]`, expect non-decreasing trend (`sign = True`)
   - If `nums[-1] < nums[0]`, expect non-increasing trend (`sign = False`)

3. **Validate Consistency**:
   ```python
   for i in range(1, n):
       if nums[i] != nums[i - 1] and sign != ((nums[i] - nums[i - 1]) >= 0):
           return False
   ```
   - For each adjacent pair `(nums[i-1], nums[i])`:
     - Skip if elements are equal (doesn't affect monotonicity)
     - Check if local trend matches overall expected trend
     - Return `False` if any inconsistency found

### Key Optimizations:

- **Single Pass**: O(n) time complexity
- **Early Termination**: Returns `False` immediately when violation found
- **Handles Edge Cases**: Works correctly for arrays with duplicate elements
- **Trend Detection**: Uses first and last elements to avoid multiple trend checks

### Example Walkthrough:

**Example 1**: `nums = [1,2,2,3]`
- `sign = (3-1) >= 0 = True` (expect non-decreasing)
- Check pairs: (1,2)✓, (2,2)skip, (2,3)✓
- Result: `True`

**Example 2**: `nums = [6,5,4,4]`
- `sign = (4-6) >= 0 = False` (expect non-increasing)
- Check pairs: (6,5)✓, (5,4)✓, (4,4)skip
- Result: `True`

**Example 3**: `nums = [1,3,2]`
- `sign = (2-1) >= 0 = True` (expect non-decreasing)
- Check pairs: (1,3)✓, (3,2)✗ (decreasing violates expected trend)
- Result: `False`

### Complexity:
- **Time Complexity**: O(n) - single pass through array
- **Space Complexity**: O(1) - only using constant extra space

# Tags

Array, Two Pointers, Monotonic Stack

