## Problem

https://leetcode.com/problems/find-subarrays-with-equal-sum/description/

```
Given a 0-indexed integer array nums, determine whether there exist two subarrays of length 2 with equal sum. Note that the two subarrays must begin at different indices.

Return true if these subarrays exist, and false otherwise.

A subarray is a contiguous non-empty sequence of elements within an array.

Example 1:

Input: nums = [4,2,4]
Output: true
Explanation: The subarrays with elements [4,2] and [2,4] have the same sum of 6.

Example 2:

Input: nums = [1,2,3,4,5]
Output: false
Explanation: No two subarrays of size 2 have the same sum.

Example 3:

Input: nums = [0,0,0]
Output: true
Explanation: The subarrays [nums[0],nums[1]] and [nums[1],nums[2]] have the same sum of 0. 
Note that even though the subarrays have the same content, the two subarrays are considered different because they are in different positions in the original array.

Constraints:

2 <= nums.length <= 1000
-109 <= nums[i] <= 109
```

## Observations

1. **Problem Requirements**: We need to find two subarrays of exactly length 2 that have the same sum.
2. **Key Insight**: A subarray of length 2 starting at index `i` has sum `nums[i] + nums[i+1]`.
3. **Approach**: We can iterate through all possible subarrays of length 2 and track their sums.
4. **Frequency Counting**: If any sum appears more than once, we have found our answer.
5. **Edge Cases**: 
   - Minimum array length is 2 (given in constraints)
   - Adjacent subarrays can overlap (e.g., [nums[0],nums[1]] and [nums[1],nums[2]])
   - Same content but different positions count as different subarrays

## Solution

**Algorithm Steps:**
1. Initialize an empty frequency dictionary `f`
2. Iterate through the array starting from index 1
3. For each position `i`, calculate the sum of the subarray `[nums[i-1], nums[i]]`
4. Store/increment the frequency of this sum in the dictionary
5. Return `True` if any sum appears 2 or more times, `False` otherwise

**Time Complexity**: O(n) - single pass through the array
**Space Complexity**: O(n) - in worst case, all sums are unique

**Why it works**: If two subarrays of length 2 have the same sum, that sum will appear at least twice in our frequency map. The `any()` function with generator expression efficiently checks if any frequency is ≥ 2.

# Tags
Hash Map, Array, Frequency Counting

