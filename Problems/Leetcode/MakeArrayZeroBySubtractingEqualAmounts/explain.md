## Problem

https://leetcode.com/problems/make-array-zero-by-subtracting-equal-amounts/

```
You are given a non-negative integer array nums. In one operation, you must:

Choose a positive integer x such that x is less than or equal to the smallest non-zero element in nums.
Subtract x from every positive element in nums.
Return the minimum number of operations to make every element in nums equal to 0.

Example 1:

Input: nums = [1,5,0,3,5]
Output: 3
Explanation:
In the first operation, choose x = 1. Now, nums = [0,4,0,2,4].
In the second operation, choose x = 2. Now, nums = [0,2,0,0,2].
In the third operation, choose x = 2. Now, nums = [0,0,0,0,0].

Example 2:

Input: nums = [0]
Output: 0
Explanation: Each element in nums is already 0 so no operations are needed.

Constraints:

1 <= nums.length <= 100
0 <= nums[i] <= 100
```

## Observations

1. **Key Insight**: In each operation, we subtract the same value from all positive elements. This means we're essentially "removing layers" from the array.

2. **Optimal Strategy**: To minimize operations, we should always choose `x` equal to the smallest non-zero element. This ensures we reduce at least one element to zero in each operation.

3. **Pattern Recognition**: After sorting the array, each unique positive value represents one "layer" that needs to be removed. The number of operations equals the number of distinct positive values.

4. **Example Walkthrough**: 
   - `nums = [1,5,0,3,5]` → sorted: `[0,1,3,5,5]`
   - Distinct positive values: `{1, 3, 5}` → 3 operations needed
   - Operation 1: subtract 1 → `[0,0,2,4,4]`
   - Operation 2: subtract 2 → `[0,0,0,2,2]`  
   - Operation 3: subtract 2 → `[0,0,0,0,0]`

5. **Why Sorting Works**: After sorting, we can process elements in ascending order. Each time we encounter a value greater than our current "baseline", it represents a new layer that requires an additional operation.

## Solution

1. **Sort the array**: This allows us to process elements from smallest to largest, identifying distinct "layers" efficiently.

2. **Track current baseline (`cur`)**: This represents the cumulative amount we've already subtracted in previous operations.

3. **Iterate through sorted array**: 
   - If `val > cur`: We've found a new layer that requires subtraction → increment operation count
   - Update `cur = val`: Set new baseline for subsequent elements

4. **Time Complexity**: O(n log n) due to sorting
   **Space Complexity**: O(1) if we can modify input, O(n) otherwise

**Alternative Approach (Set-based)**:
```python
def minimumOperations(self, nums: List[int]) -> int:
    return len(set(nums) - {0})  # Count distinct positive values
```

This works because the answer equals the number of unique positive values in the array.

## Tags

array, greedy