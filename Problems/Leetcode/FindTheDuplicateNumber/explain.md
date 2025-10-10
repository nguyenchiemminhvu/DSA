## Problem

```
Given an array of integers nums containing n + 1 integers where each integer is in the range [1, n] inclusive.

There is only one repeated number in nums, return this repeated number.

You must solve the problem without modifying the array nums and using only constant extra space.

Example 1:

Input: nums = [1,3,4,2,2]
Output: 2

Example 2:

Input: nums = [3,1,3,4,2]
Output: 3

Example 3:

Input: nums = [3,3,3,3,3]
Output: 3

Constraints:

1 <= n <= 105
nums.length == n + 1
1 <= nums[i] <= n
All the integers in nums appear only once except for precisely one integer which appears two or more times.
```

## Observations

Given an array of integers `nums` containing `n + 1` numbers where each number is between `1` and `n` (inclusive), there is guaranteed to be at least one duplicate. The task is to find any duplicate number.

- The array size is `n + 1`, but the numbers range from `1` to `n`, so by the pigeonhole principle, at least one number must repeat.
- We need to find a duplicate efficiently, ideally in `O(n)` time and `O(1)` or `O(n)` space.

## Solution

The provided solution uses a set to track seen numbers:

1. Initialize an empty set `s`.
2. Iterate through each value in `nums`:
	- If the value is already in the set, return it as the duplicate.
	- Otherwise, add the value to the set.
3. If no duplicate is found (should not happen per problem constraints), return -1.

This approach has:
- Time Complexity: `O(n)`, since each lookup and insertion in a set is `O(1)` on average.
- Space Complexity: `O(n)`, due to the extra set used to store seen numbers.

Alternative solutions include `Floyd's Tortoise and Hare` (cycle detection) for `O(1)` space, but the set-based approach is simple and effective for most cases.

## Tags

array, hash table