## Problem

https://leetcode.com/problems/split-array-largest-sum/

```
Given an integer array nums and an integer k, split nums into k non-empty subarrays such that the largest sum of any subarray is minimized.

Return the minimized largest sum of the split.

A subarray is a contiguous part of the array.

Example 1:

Input: nums = [7,2,5,10,8], k = 2
Output: 18
Explanation: There are four ways to split nums into two subarrays.
The best way is to split it into [7,2,5] and [10,8], where the largest sum among the two subarrays is only 18.

Example 2:

Input: nums = [1,2,3,4,5], k = 2
Output: 9
Explanation: There are four ways to split nums into two subarrays.
The best way is to split it into [1,2,3] and [4,5], where the largest sum among the two subarrays is only 9.

Constraints:

1 <= nums.length <= 1000
0 <= nums[i] <= 106
1 <= k <= min(50, nums.length)
```

## Observations

Goal: We want to partition the array into `k` subarrays such that the maximum subarray sum among them is as small as possible.

The order of elements must be preserved since we can only split into contiguous subarrays.

The minimum possible largest sum can never be less than:

- `max(nums)` — because every subarray must contain at least one element.

The maximum possible largest sum is:

- `sum(nums)` — if we take the entire array as one subarray.

Therefore, the answer must lie within the range:

`[max(nums), sum(nums)]`

This naturally suggests a binary search approach over the possible largest subarray sums.

## Solution

We can binary search over the range `[max(nums), sum(nums)]` to find the smallest possible value `x` such that we can split the array into at most `k` subarrays, each having a `sum ≤ x`.

**Steps:**

Set `left = max(nums)` and `right = sum(nums)`.

While `left < right`:

- Compute `mid = (left + right) // 2`.
- Check if it is possible to split the array into `≤ k` subarrays, each with `sum ≤ mid`.
- If it’s possible, we can try to reduce mid, so set `right = mid`.
- Otherwise, increase `mid` by setting `left = mid + 1`.

The final `left` (or `right`) will be the minimized largest `sum`.

Helper Function: `canSplit(nums, k, mid)`

This function checks whether the array can be split into `≤ k` subarrays such that the sum of each subarray `≤ mid`.

**Time Complexity**

Binary Search Range: `O(log(sum(nums) - max(nums)))`

Check Function: `O(n)` for each binary search iteration

➡ Total: `O(n * log(sum(nums)))`

**Space Complexity**

`O(1)` — Only uses constant extra space.

## Tags

array, binary search