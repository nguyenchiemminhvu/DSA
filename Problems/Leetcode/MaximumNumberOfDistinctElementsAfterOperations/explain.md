## Problem

https://leetcode.com/problems/maximum-number-of-distinct-elements-after-operations/description/

```
You are given an integer array nums and an integer k.

You are allowed to perform the following operation on each element of the array at most once:

Add an integer in the range [-k, k] to the element.
Return the maximum possible number of distinct elements in nums after performing the operations.

Example 1:

Input: nums = [1,2,2,3,3,4], k = 2

Output: 6

Explanation:

nums changes to [-1, 0, 1, 2, 3, 4] after performing operations on the first four elements.

Example 2:

Input: nums = [4,4,4,4], k = 1

Output: 3

Explanation:

By adding -1 to nums[0] and 1 to nums[1], nums changes to [3, 5, 4, 4].

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 109
0 <= k <= 109
```

## Observations

1. **Goal**: Maximize the number of distinct elements after applying operations
2. **Operation**: Each element can be modified by adding a value in range [-k, k]
3. **Key Insight**: To maximize distinct elements, we want to avoid collisions (same values)
4. **Greedy Approach**: Process elements in sorted order and assign the smallest possible value that doesn't conflict with previous assignments
5. **Range Analysis**: For each element `nums[i]`, the possible values after operation are in range `[nums[i] - k, nums[i] + k]`
6. **Conflict Avoidance**: If we assign values greedily from left to right (smallest to largest), we can ensure maximum distinctness

## Solution

1. **Sort the array**: `nums.sort()`
   - Process elements in ascending order to apply greedy strategy effectively

2. **Initialize tracking variables**:
   - `arr`: stores the final assigned values after operations
   - `prev`: tracks the last assigned value to avoid duplicates

3. **Greedy Assignment Logic**:
   For each element `val` in sorted array:
   - **Lower bound**: `val - k` (minimum possible value after operation)
   - **Upper bound**: `val + k` (maximum possible value after operation)
   - **Conflict avoidance**: `prev + 1` (smallest value greater than previous assignment)
   - **Final assignment**: `min(max(prev + 1, val - k), val + k)`

4. **Assignment Formula Breakdown**:
   - `max(prev + 1, val - k)`: Ensure no collision with previous assignment
   - `min(..., val + k)`: Ensure within valid operation range
   - This gives us the smallest valid value that doesn't conflict

5. **Count distinct elements**: `len(set(arr))`

### Example Walkthrough:

**Example 1**: `nums = [1,2,2,3,3,4], k = 2`

After sorting: `[1,2,2,3,3,4]`

- `val = 1`: range `[-1, 3]`, assign `max(-2, -1) = -1`, `prev = -1`
- `val = 2`: range `[0, 4]`, assign `max(0, 0) = 0`, `prev = 0`
- `val = 2`: range `[0, 4]`, assign `max(1, 0) = 1`, `prev = 1`
- `val = 3`: range `[1, 5]`, assign `max(2, 1) = 2`, `prev = 2`
- `val = 3`: range `[1, 5]`, assign `max(3, 1) = 3`, `prev = 3`
- `val = 4`: range `[2, 6]`, assign `max(4, 2) = 4`, `prev = 4`

Final array: `[-1, 0, 1, 2, 3, 4]` → 6 distinct elements

### Time Complexity: O(n log n)
- Sorting takes O(n log n)
- Processing each element takes O(1)
- Converting to set takes O(n)

### Space Complexity: O(n)
- Array to store assigned values
- Set for counting distinct elements

## Tags

array, greedy