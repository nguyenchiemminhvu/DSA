## Problem

https://leetcode.com/problems/maximum-product-of-three-numbers/

```
Given an integer array nums, find three numbers whose product is maximum and return the maximum product.

Example 1:

Input: nums = [1,2,3]
Output: 6

Example 2:

Input: nums = [1,2,3,4]
Output: 24

Example 3:

Input: nums = [-1,-2,-3]
Output: -6

Constraints:

3 <= nums.length <= 104
-1000 <= nums[i] <= 1000
```

## Observations

1. **Key Insight**: The maximum product of three numbers can occur in two scenarios:
   - Three largest positive numbers
   - Two smallest negative numbers (which become positive when multiplied) times the largest positive number

2. **Edge Cases to Consider**:
   - All numbers are positive: choose the three largest
   - All numbers are negative: choose the three largest (least negative)
   - Mix of positive and negative: need to consider both scenarios above

3. **Mathematical Property**: 
   - Two negative numbers multiplied together give a positive result
   - If we have two very small negative numbers (large absolute values), their product with the largest positive number might be larger than the product of three largest positive numbers

4. **Examples Analysis**:
   - `[1,2,3]` → 1×2×3 = 6 (three largest positives)
   - `[1,2,3,4]` → 2×3×4 = 24 (three largest positives)
   - `[-1,-2,-3]` → (-3)×(-2)×(-1) = -6 (three largest negatives)
   - `[-10,-10,5,2]` → (-10)×(-10)×5 = 500 vs 5×2×(-10) = -100 (two smallest negatives with largest positive wins)

## Solution

The solution uses a **sorting approach** with **two-candidate comparison**:

```python
class Solution:
    def maximumProduct(self, nums: List[int]) -> int:
        nums.sort()
        return max(nums[-1] * nums[-2] * nums[-3], nums[0] * nums[1] * nums[-1])
```

### Algorithm Steps:
1. **Sort the array** in ascending order
2. **Calculate two candidates**:
   - `nums[-1] * nums[-2] * nums[-3]`: Product of three largest numbers
   - `nums[0] * nums[1] * nums[-1]`: Product of two smallest numbers with the largest number
3. **Return the maximum** of these two candidates

### Why This Works:
- After sorting, `nums[0]` and `nums[1]` are the two smallest numbers
- If they're both negative, their product is positive and potentially very large
- `nums[-1]`, `nums[-2]`, `nums[-3]` are the three largest numbers
- We only need to compare these two scenarios because:
  - If the maximum is achieved by three positives, the first candidate wins
  - If the maximum is achieved by two negatives × one positive, the second candidate wins
  - Other combinations (like three negatives) are covered by the first candidate

### Time Complexity: O(n log n) - due to sorting
### Space Complexity: O(1) - only using constant extra space (sorting is in-place)

### Alternative O(n) Solution:
Instead of sorting, we could find the three largest and two smallest numbers in one pass, but the sorting solution is simpler and more readable.

# Tags

- Array
- Math
- Sorting
- Greedy

