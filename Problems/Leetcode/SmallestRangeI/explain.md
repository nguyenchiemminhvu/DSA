## Problem

https://leetcode.com/problems/smallest-range-i/

```
You are given an integer array nums and an integer k.

In one operation, you can choose any index i where 0 <= i < nums.length and change nums[i] to nums[i] + x where x is an integer from the range [-k, k]. You can apply this operation at most once for each index i.

The score of nums is the difference between the maximum and minimum elements in nums.

Return the minimum score of nums after applying the mentioned operation at most once for each index in it.

Example 1:

Input: nums = [1], k = 0
Output: 0
Explanation: The score is max(nums) - min(nums) = 1 - 1 = 0.

Example 2:

Input: nums = [0,10], k = 2
Output: 6
Explanation: Change nums to be [2, 8]. The score is max(nums) - min(nums) = 8 - 2 = 6.

Example 3:

Input: nums = [1,3,6], k = 3
Output: 0
Explanation: Change nums to be [4, 4, 4]. The score is max(nums) - min(nums) = 4 - 4 = 0.

Constraints:

1 <= nums.length <= 104
0 <= nums[i] <= 104
0 <= k <= 104
```

## Observations

1. **Goal**: Minimize the difference between maximum and minimum elements after applying operations
2. **Operation**: Each element can be changed by adding any value x where -k ≤ x ≤ k (at most once per element)
3. **Strategy**: To minimize the range, we want to:
   - Increase the minimum element as much as possible (add k)
   - Decrease the maximum element as much as possible (subtract k)
4. **Key insight**: After sorting, the optimal strategy is:
   - Add k to the smallest element: `min_val + k`
   - Subtract k from the largest element: `max_val - k`
5. **Edge case**: If after operations the "new max" ≤ "new min", then all elements can be made equal, resulting in range = 0

## Solution

1. **Sort the array**: This helps us easily identify min and max elements
2. **Apply optimal operations**: 
   - `nums[0] += k`: Increase the smallest element by k (maximum possible increase)
   - `nums[-1] -= k`: Decrease the largest element by k (maximum possible decrease)
3. **Calculate result**: `max(0, nums[-1] - nums[0])`
   - If `nums[-1] - nums[0] ≤ 0`: All elements can be made equal → return 0
   - Otherwise: Return the minimized range

**Time Complexity**: O(n log n) due to sorting
**Space Complexity**: O(1) if we can modify input, O(n) if we need to preserve original array

**Example walkthrough:**
- `nums = [0,10], k = 2`
- After sorting: `[0,10]`
- Apply operations: `[0+2, 10-2] = [2,8]`
- Result: `max(0, 8-2) = 6`

# Tags

- Array
- Math
- Greedy

