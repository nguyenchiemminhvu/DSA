## Problem

https://leetcode.com/problems/maximum-unique-subarray-sum-after-deletion/description/

```
You are given an integer array nums.

You are allowed to delete any number of elements from nums without making it empty. 
After performing the deletions, select a subarray of nums such that:
- All elements in the subarray are unique.
- The sum of the elements in the subarray is maximized.

Return the maximum sum of such a subarray.

Example 1:
Input: nums = [1,2,3,4,5]
Output: 15
Explanation: Select the entire array without deleting any element to obtain the maximum sum.

Example 2:
Input: nums = [1,1,0,1,1]
Output: 1
Explanation: Delete the element nums[0] == 1, nums[1] == 1, nums[2] == 0, and nums[3] == 1. 
Select the entire array [1] to obtain the maximum sum.

Example 3:
Input: nums = [1,2,-1,-2,1,0,-1]
Output: 3
Explanation: Delete the elements nums[2] == -1 and nums[3] == -2, and select the subarray [2, 1] 
from [1, 2, 1, 0, -1] to obtain the maximum sum.

Constraints:
- 1 <= nums.length <= 100
- -100 <= nums[i] <= 100
```

## Observations

1. **Key Insight**: Since we can delete any elements and need unique elements in the final subarray, we can think about which elements to keep rather than which to delete.

2. **Negative Numbers**: Negative numbers will always decrease the sum, so we should avoid including them if possible.

3. **Duplicate Handling**: Since we need unique elements, we can only keep one occurrence of each value. Using a set naturally handles this.

4. **Optimization Strategy**: 
   - We want to maximize the sum with unique elements
   - We should keep all non-negative unique values (they contribute positively or neutrally)
   - We need to handle the edge case where all numbers are negative

5. **Edge Cases**:
   - All elements are negative: We must keep at least one element (the maximum one)
   - All elements are the same: We can only keep one occurrence
   - Mix of positive and negative: Keep all unique non-negative values

## Solution

**Time Complexity**: O(n) where n is the length of nums
- One pass to find max: O(n)
- One pass to create set and sum: O(n)

**Space Complexity**: O(n) for storing the set of unique non-negative values

**Why This Works**:

1. **Deletion Freedom**: Since we can delete any elements, we're essentially choosing which elements to keep, not bound by subarray constraints initially.

2. **Unique Constraint**: By using a set, we automatically ensure all selected elements are unique.

3. **Maximization Strategy**: 
   - Including any non-negative number (>= 0) either increases or maintains the sum
   - Excluding any negative number improves the sum
   - Therefore, keeping all unique non-negative values gives the maximum

4. **Baseline with max(nums)**: This ensures we return a valid answer even when all numbers are negative (we must keep at least one element).

**Example Walkthrough**:

Example 3: `nums = [1,2,-1,-2,1,0,-1]`
- `max(nums) = 2`
- Non-negative unique values: `{0, 1, 2}`
- Sum of non-negative unique values: `0 + 1 + 2 = 3`
- Result: `max(2, 3) = 3` ✓

# Tags

`Array` `Greedy` `Hash Table` `Set`

