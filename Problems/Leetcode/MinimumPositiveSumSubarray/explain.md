## Problem

https://leetcode.com/problems/minimum-positive-sum-subarray/description/

```
You are given an integer array nums and two integers l and r. Your task is to find the minimum sum of a subarray whose size is between l and r (inclusive) and whose sum is greater than 0.

Return the minimum sum of such a subarray. If no such subarray exists, return -1.

A subarray is a contiguous non-empty sequence of elements within an array.

Example 1:

Input: nums = [3, -2, 1, 4], l = 2, r = 3

Output: 1

Explanation:

The subarrays of length between l = 2 and r = 3 where the sum is greater than 0 are:

[3, -2] with a sum of 1
[1, 4] with a sum of 5
[3, -2, 1] with a sum of 2
[-2, 1, 4] with a sum of 3
Out of these, the subarray [3, -2] has a sum of 1, which is the smallest positive sum. Hence, the answer is 1.

Example 2:

Input: nums = [-2, 2, -3, 1], l = 2, r = 3

Output: -1

Explanation:

There is no subarray of length between l and r that has a sum greater than 0. So, the answer is -1.

Example 3:

Input: nums = [1, 2, 3, 4], l = 2, r = 4

Output: 3

Explanation:

The subarray [1, 2] has a length of 2 and the minimum sum greater than 0. So, the answer is 3.

Constraints:

1 <= nums.length <= 100
1 <= l <= r <= nums.length
-1000 <= nums[i] <= 1000
```

## Observations

1. **Problem Understanding**: We need to find the minimum positive sum among all subarrays whose length is between `l` and `r` (inclusive).

2. **Key Constraints**:
   - Subarray length must be between `l` and `r`
   - Sum must be positive (> 0)
   - We want the minimum such sum
   - Return -1 if no such subarray exists

3. **Approach Analysis**: The solution uses prefix sums to efficiently calculate subarray sums:
   - Convert the array to prefix sums for O(1) subarray sum calculation
   - Try all possible subarray lengths from `l` to `r`
   - For each length, try all possible starting positions
   - Track the minimum positive sum found

4. **Edge Cases**:
   - All subarrays in the valid range have negative or zero sums → return -1
   - Multiple subarrays with positive sums → return the minimum

## Solution

**Algorithm: Prefix Sum with Brute Force**

1. **Prefix Sum Construction**: Transform `nums` into cumulative sums where `nums[i]` represents sum from index 0 to i.

2. **Add Zero Padding**: Prepend 0 to make subarray sum calculation easier: `nums[i-1] - nums[i-sub-1]` gives sum of subarray of length `sub` ending at position `i-1`.

3. **Nested Loop Structure**:
   - Outer loop: iterate through all valid subarray lengths (`l` to `r`)
   - Inner loop: iterate through all possible ending positions for current length

4. **Subarray Sum Calculation**: For a subarray of length `sub` ending at position `i-1`, the sum is `nums[i-1] - nums[i-sub-1]`.

5. **Track Minimum**: Keep track of the minimum positive sum found.

**Time Complexity**: O(n × (r - l + 1)) where n is array length
**Space Complexity**: O(1) if we modify input array, O(n) if we create new prefix array

**Example Walkthrough** (nums = [3, -2, 1, 4], l = 2, r = 3):
- Prefix sums: [0, 3, 1, 2, 6]
- Length 2 subarrays: [3,-2]=1, [-2,1]=-1, [1,4]=5
- Length 3 subarrays: [3,-2,1]=2, [-2,1,4]=3  
- Minimum positive sum: 1

# Tags

- Array
- Prefix Sum
- Sliding Window
- Brute Force

