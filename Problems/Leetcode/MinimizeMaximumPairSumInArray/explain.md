## Problem

https://leetcode.com/problems/minimize-maximum-pair-sum-in-array/description/

```
The pair sum of a pair (a,b) is equal to a + b. The maximum pair sum is the largest pair sum in a list of pairs.

For example, if we have pairs (1,5), (2,3), and (4,4), the maximum pair sum would be max(1+5, 2+3, 4+4) = max(6, 5, 8) = 8.
Given an array nums of even length n, pair up the elements of nums into n / 2 pairs such that:

Each element of nums is in exactly one pair, and
The maximum pair sum is minimized.
Return the minimized maximum pair sum after optimally pairing up the elements.

Example 1:

Input: nums = [3,5,2,3]
Output: 7
Explanation: The elements can be paired up into pairs (3,3) and (5,2).
The maximum pair sum is max(3+3, 5+2) = max(6, 7) = 7.

Example 2:

Input: nums = [3,5,4,2,4,6]
Output: 8
Explanation: The elements can be paired up into pairs (3,5), (4,4), and (6,2).
The maximum pair sum is max(3+5, 4+4, 6+2) = max(8, 8, 8) = 8.

Constraints:

n == nums.length
2 <= n <= 105
n is even.
1 <= nums[i] <= 105
```

## Observations

1. **Problem Goal**: We need to pair up elements to minimize the maximum pair sum.

2. **Key Insight**: To minimize the maximum pair sum, we should pair the largest element with the smallest element, the second largest with the second smallest, and so on.

3. **Why this works**: 
   - If we pair two large numbers together, their sum will be very large
   - If we pair two small numbers together, we'll be left with large numbers that must be paired together
   - The optimal strategy is to "balance" the pairs by pairing extremes

4. **Greedy Approach**: After sorting, pair `nums[0]` with `nums[n-1]`, `nums[1]` with `nums[n-2]`, etc.

5. **Mathematical Proof**: 
   - Suppose we have sorted array: `a₁ ≤ a₂ ≤ ... ≤ aₙ`
   - Any pairing will include at least one pair with `aₙ` (the largest element)
   - To minimize the sum involving `aₙ`, we should pair it with `a₁` (the smallest element)
   - This gives us `a₁ + aₙ`, and we can apply the same logic recursively to the remaining elements

## Solution

1. **Sort the array**: `O(n log n)` - This allows us to easily access smallest and largest elements

2. **Two-pointer technique**: 
   - `left` starts at the beginning (smallest elements)
   - `right` starts at the end (largest elements)

3. **Pairing strategy**: Always pair `nums[left]` with `nums[right]`

4. **Track maximum**: Keep updating the result with the maximum pair sum seen so far

### Example Walkthrough

**Example 1**: `nums = [3,5,2,3]`
- After sorting: `[2,3,3,5]`
- Pair 1: `nums[0] + nums[3] = 2 + 5 = 7`
- Pair 2: `nums[1] + nums[2] = 3 + 3 = 6`
- Maximum: `max(7, 6) = 7`

**Example 2**: `nums = [3,5,4,2,4,6]`
- After sorting: `[2,3,4,4,5,6]`
- Pair 1: `nums[0] + nums[5] = 2 + 6 = 8`
- Pair 2: `nums[1] + nums[4] = 3 + 5 = 8`
- Pair 3: `nums[2] + nums[3] = 4 + 4 = 8`
- Maximum: `max(8, 8, 8) = 8`

### Complexity Analysis

- **Time Complexity**: `O(n log n)` due to sorting
- **Space Complexity**: `O(1)` if we don't count the space used by sorting algorithm

### Why This Greedy Approach Works

The key insight is that we want to "waste" as little as possible on any single pair. If we pair two large numbers together, we get a very large sum. If we pair two small numbers together, we're forced to pair the remaining large numbers together later. The optimal strategy is to pair each large number with a small number to balance out the sums.

## Tags

array, greedy