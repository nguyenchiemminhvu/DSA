## Problem

https://leetcode.com/problems/maximum-difference-between-increasing-elements/description/

```
Given a 0-indexed integer array nums of size n, find the maximum difference between nums[i] and nums[j] (i.e., nums[j] - nums[i]), such that 0 <= i < j < n and nums[i] < nums[j].

Return the maximum difference. If no such i and j exists, return -1.

Example 1:

Input: nums = [7,1,5,4]
Output: 4
Explanation:
The maximum difference occurs with i = 1 and j = 2, nums[j] - nums[i] = 5 - 1 = 4.
Note that with i = 1 and j = 0, the difference nums[j] - nums[i] = 7 - 1 = 6, but i > j, so it is not valid.

Example 2:

Input: nums = [9,4,3,2]
Output: -1
Explanation:
There is no i and j such that i < j and nums[i] < nums[j].

Example 3:

Input: nums = [1,5,2,10]
Output: 9
Explanation:
The maximum difference occurs with i = 0 and j = 3, nums[j] - nums[i] = 10 - 1 = 9.

Constraints:

n == nums.length
2 <= n <= 1000
1 <= nums[i] <= 109
```

## Observations

1. **Problem Requirements**: We need to find the maximum difference `nums[j] - nums[i]` where `i < j` and `nums[i] < nums[j]`.

2. **Key Constraints**: 
   - Index constraint: `i < j` (left element must come before right element)
   - Value constraint: `nums[i] < nums[j]` (left element must be smaller)

3. **Edge Cases**: 
   - If no valid pair exists (array is non-increasing), return -1
   - Need at least 2 elements in the array

4. **Brute Force Approach**: Check all pairs O(n²) - but we can do better

5. **Optimization Insight**: For each position, we want to know the maximum element that appears after it, and the minimum element that appears before it.

## Solution

1. **Reverse Processing**: By using `nums.pop()`, we process the array from right to left (from the last element to the first).

2. **Running Maximum**: `cur_max` keeps track of the maximum element we've seen so far from the right side.

3. **Valid Pair Detection**: When `val < cur_max`, we have found a valid pair where:
   - `val` is at position `i` (current element from left perspective)
   - `cur_max` represents the maximum element at some position `j > i`
   - Since `val < cur_max`, we satisfy `nums[i] < nums[j]`

4. **Update Result**: We update `res` with the maximum difference found so far.

**Time Complexity**: O(n) - single pass through the array
**Space Complexity**: O(1) - only using constant extra space (note: the solution modifies the input array)

**Example Walkthrough** with `nums = [7,1,5,4]`:
- Start from right: `val = 4`, `cur_max = 4`, `res = -1`
- Next: `val = 5`, `cur_max = 5`, `res = -1` 
- Next: `val = 1`, `1 < 5`, so `res = max(-1, 5-1) = 4`
- Next: `val = 7`, `cur_max = 7`, `res = 4`
- Return `4`

**Alternative O(n) Approach** (without modifying input):
```python
def maximumDifference(self, nums: List[int]) -> int:
    min_so_far = nums[0]
    max_diff = -1
    
    for i in range(1, len(nums)):
        if nums[i] > min_so_far:
            max_diff = max(max_diff, nums[i] - min_so_far)
        min_so_far = min(min_so_far, nums[i])
    
    return max_diff
```

# Tags
- Array
- Greedy
- Dynamic Programming
- Two Pointers

