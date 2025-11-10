## Problem

https://leetcode.com/problems/minimum-value-to-get-positive-step-by-step-sum/description/

```
Given an array of integers nums, you start with an initial positive value startValue.

In each iteration, you calculate the step by step sum of startValue plus elements in nums (from left to right).

Return the minimum positive value of startValue such that the step by step sum is never less than 1.

Example 1:

Input: nums = [-3,2,-3,4,2]
Output: 5
Explanation: If you choose startValue = 4, in the third iteration your step by step sum is less than 1.
step by step sum
startValue = 4 | startValue = 5 | nums
  (4 -3 ) = 1  | (5 -3 ) = 2    |  -3
  (1 +2 ) = 3  | (2 +2 ) = 4    |   2
  (3 -3 ) = 0  | (4 -3 ) = 1    |  -3
  (0 +4 ) = 4  | (1 +4 ) = 5    |   4
  (4 +2 ) = 6  | (5 +2 ) = 7    |   2

Example 2:

Input: nums = [1,2]
Output: 1
Explanation: Minimum start value should be positive. 

Example 3:

Input: nums = [1,-2,-3]
Output: 5

Constraints:

1 <= nums.length <= 100
-100 <= nums[i] <= 100
```

## Observations

1. **Step-by-step sum calculation**: We start with `startValue` and keep adding elements from `nums` array from left to right. At each step, the running sum must be ≥ 1.

2. **Key insight**: The problem is asking for the minimum `startValue` such that the cumulative sum never drops below 1. This means we need to find the most negative prefix sum and adjust accordingly.

3. **Prefix sum approach**: If we calculate prefix sums, the minimum prefix sum tells us how much we need to "boost" the initial value to prevent going below 1.

4. **Mathematical relationship**: If the minimum prefix sum is `min_prefix`, then we need `startValue + min_prefix ≥ 1`, which means `startValue ≥ 1 - min_prefix`.

5. **Edge cases**:
   - If all prefix sums are positive, we only need `startValue = 1`
   - The answer must be at least 1 (positive constraint)

## Solution

**Approach**: Prefix Sum + Mathematical Analysis

1. **Calculate prefix sums**: Convert the input array to prefix sums in-place
2. **Find minimum prefix sum**: The smallest value among all prefix sums
3. **Calculate required startValue**: `max(1, 1 - min_prefix_sum)`

**Time Complexity**: O(n) - single pass to calculate prefix sums
**Space Complexity**: O(1) - modifying input array in-place

**Algorithm**:
- Transform `nums` into prefix sum array
- Find the minimum value in the prefix sum array
- Return `max(1, 1 - minimum_prefix_sum)`

# Tags

`Array` `Prefix Sum` `Math` `Simulation`

