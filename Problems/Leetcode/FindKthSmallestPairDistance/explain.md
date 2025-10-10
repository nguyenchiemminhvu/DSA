## Problem

https://leetcode.com/problems/find-k-th-smallest-pair-distance/

```
The distance of a pair of integers a and b is defined as the absolute difference between a and b.

Given an integer array nums and an integer k, return the kth smallest distance among all the pairs nums[i] and nums[j] where 0 <= i < j < nums.length.

Example 1:

Input: nums = [1,3,1], k = 1
Output: 0
Explanation: Here are all the pairs:
(1,3) -> 2
(1,1) -> 0
(3,1) -> 2
Then the 1st smallest distance pair is (1,1), and its distance is 0.

Example 2:

Input: nums = [1,1,1], k = 2
Output: 0

Example 3:

Input: nums = [1,6,1], k = 3
Output: 5

Constraints:

n == nums.length
2 <= n <= 104
0 <= nums[i] <= 106
1 <= k <= n * (n - 1) / 2
```

## Observations

The problem asks for the k-th smallest distance among all pairs in an array.

The distance between a pair `(i,j)` is `∣nums[i]−nums[j]∣`.

Brute-force would require generating all pairs and sorting their distances, which is slow for large arrays.

If the array is sorted, the distance between pairs can be efficiently calculated.

For any distance threshold d, we can count how many pairs have a distance `≤ d` using two pointers.

## Solution

Sort the Array: Sorting helps us efficiently count pairs with a given distance using the two-pointer technique.

**Binary Search on Distance:**

The smallest possible distance is `0` (if there are duplicates).

The largest possible distance is `max(nums) − min(nums)`.

Use binary search to find the smallest distance `d` such that there are at least `k` pairs with distance `≤ d`.

**Counting Pairs:**

For each possible distance d, use two pointers to count how many pairs have a distance `≤ d`.

For each `i`, move `j` as far as possible such that `nums[j] − nums[i] ≤ d`.

The number of pairs for `i` is `(j−i−1)`.

**Binary Search Steps:**

If the count of pairs with distance `≤ d` is at least `k`, try a smaller `d`.

If the count is less than `k`, try a larger `d`.

The answer is the smallest `d` for which the count is at least `k`.

## Tags

array, binary search