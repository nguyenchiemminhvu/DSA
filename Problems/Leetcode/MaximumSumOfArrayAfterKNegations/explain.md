## Problem

https://leetcode.com/problems/maximize-sum-of-array-after-k-negations/

```
Given an integer array nums and an integer k, modify the array in the following way:

choose an index i and replace nums[i] with -nums[i].
You should apply this process exactly k times. You may choose the same index i multiple times.

Return the largest possible sum of the array after modifying it in this way.

Example 1:

Input: nums = [4,2,3], k = 1
Output: 5
Explanation: Choose index 1 and nums becomes [4,-2,3].

Example 2:

Input: nums = [3,-1,0,2], k = 3
Output: 6
Explanation: Choose indices (1, 2, 2) and nums becomes [3,1,0,2].

Example 3:

Input: nums = [2,-3,-1,5,-4], k = 2
Output: 13
Explanation: Choose indices (1, 4) and nums becomes [2,3,-1,5,4].

Constraints:

1 <= nums.length <= 104
-100 <= nums[i] <= 100
1 <= k <= 104
```

## Observations

1. **Greedy Strategy**: To maximize the sum after k negations, we should prioritize negating the most negative numbers first, as this gives us the largest positive contribution.

2. **Sorting Advantage**: By sorting the array, we can easily identify negative numbers (they come first) and process them in order of their absolute value (most negative first).

3. **Two Phases**: 
   - Phase 1: Negate as many negative numbers as possible
   - Phase 2: If we still have negations left and k is odd, we need to negate the smallest absolute value number

4. **Binary Search Optimization**: The solution uses binary search (upper_bound) to find the first non-negative number, which is more efficient than linear search for finding the boundary between negative and non-negative numbers.

5. **Remaining Negations**: After negating all negative numbers, if k is still positive:
   - If k is even: We can negate any number twice (or any pair), resulting in no net change
   - If k is odd: We must negate exactly one number, so we choose the one with minimum absolute value

## Solution

**Algorithm Steps:**

1. **Sort the array** to group negative numbers at the beginning
2. **Find the boundary** between negative and non-negative numbers using binary search
3. **Negate negative numbers** starting from the most negative (leftmost) until either:
   - All negative numbers are negated, or
   - We've used all k negations
4. **Handle remaining negations**: If k > 0 after step 3:
   - Calculate the current sum
   - If k is odd, subtract twice the minimum value (equivalent to negating the smallest absolute value number)
   - If k is even, no additional change needed

**Key Implementation Details:**

- `upper_bound(nums, -1)` finds the first index where `nums[i] > -1` (i.e., first non-negative number)
- The loop `for i in range(0, non_neg_idx)` processes all negative numbers
- `s -= (min(nums) * 2)` when `k & 1` (k is odd) effectively negates the number with minimum absolute value
- After negating negative numbers, `min(nums)` gives us the smallest absolute value in the array

**Time Complexity:** O(n log n) due to sorting
**Space Complexity:** O(1) excluding the input array

**Example Walkthrough:**
```
nums = [2, -3, -1, 5, -4], k = 2

1. Sort: [-4, -3, -1, 2, 5]
2. non_neg_idx = 3 (first non-negative is at index 3)
3. Negate negatives: 
   - i=0: [-4] → [4], k=1
   - i=1: [-3] → [3], k=0
   Result: [4, 3, -1, 2, 5]
4. k=0, so no additional negations needed
5. Sum = 4 + 3 + (-1) + 2 + 5 = 13
```

## Tags

array, greedy, binary search