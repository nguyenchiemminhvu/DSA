## Problem

https://leetcode.com/problems/maximum-subarray-sum-with-length-divisible-by-k/description/

You are given an array of integers `nums` and an integer `k`.

Return the maximum sum of a subarray of `nums`, such that the size of the subarray is divisible by `k`.

**Example 1:**
```
Input: nums = [1,2], k = 1
Output: 3
Explanation: The subarray [1, 2] with sum 3 has length equal to 2 which is divisible by 1.
```

**Example 2:**
```
Input: nums = [-1,-2,-3,-4,-5], k = 4
Output: -10
Explanation: The maximum sum subarray is [-1, -2, -3, -4] which has length equal to 4 which is divisible by 4.
```

**Example 3:**
```
Input: nums = [-5,1,2,-3,4], k = 2
Output: 4
Explanation: The maximum sum subarray is [1, 2, -3, 4] which has length equal to 4 which is divisible by 2.
```

**Constraints:**
- `1 <= k <= nums.length <= 2 * 10^5`
- `-10^9 <= nums[i] <= 10^9`

## Observations

1. **Subarray Length Constraint**: We need subarrays whose length is divisible by `k` (i.e., length = `mk` for some positive integer `m`).

2. **Prefix Sum Approach**: To find subarray sums efficiently, we can use prefix sums. For a subarray from index `i` to `j`, the sum is `prefix[j+1] - prefix[i]`.

3. **Modular Arithmetic Key Insight**: For a subarray from index `i` to `j` to have length divisible by `k`, we need `(j - i + 1) % k == 0`, which means `(j + 1) % k == i % k`.

4. **Optimization Strategy**: For each position with the same modular value, we want to find the minimum prefix sum seen so far to maximize the current subarray sum.

## Solution

1. **Initialization**:
   - `min_prefix[i]`: Stores the minimum prefix sum seen so far for positions with index `% k == i`
   - `min_prefix[0] = 0`: Base case for subarrays starting from index 0
   - `res`: Tracks the maximum subarray sum found
   - `cur_sum`: Running prefix sum

2. **Main Loop Logic**:
   - For each position `i`, calculate the current prefix sum `cur_sum`
   - Find `cur_mod = (i + 1) % k` (using 1-based indexing for length calculation)
   - If we've seen a position with the same modular value before (`min_prefix[cur_mod] != inf`):
     - Calculate subarray sum: `cur_sum - min_prefix[cur_mod]`
     - Update maximum result
   - Update `min_prefix[cur_mod]` with the minimum prefix sum for this modular class

3. **Why This Works**:
   - Two positions `i` and `j` where `(i+1) % k == (j+1) % k` create a subarray of length divisible by `k`
   - To maximize `prefix[j] - prefix[i]`, we want to minimize `prefix[i]` for each modular class
   - By tracking minimum prefix sums for each modular value, we can find the optimal subarray ending at each position

**Time Complexity**: O(n) - single pass through the array
**Space Complexity**: O(k) - for the `min_prefix` array

**Key Insight**: The problem transforms from "find subarray with length divisible by k" to "find two positions with the same modular value that maximize their prefix sum difference."

# Tags
- Array
- Prefix Sum
- Dynamic Programming
- Modular Arithmetic

