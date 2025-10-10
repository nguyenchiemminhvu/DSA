## Problem

```
Given an array of integers nums, return the number of good pairs.

A pair (i, j) is called good if nums[i] == nums[j] and i < j.

Example 1:

Input: nums = [1,2,3,1,1,3]
Output: 4
Explanation: There are 4 good pairs (0,3), (0,4), (3,4), (2,5) 0-indexed.

Example 2:

Input: nums = [1,1,1,1]
Output: 6
Explanation: Each pair in the array are good.

Example 3:

Input: nums = [1,2,3]
Output: 0

Constraints:

1 <= nums.length <= 100
1 <= nums[i] <= 100
```

## Observations

With `n` elements, there are `n * (n - 1) // 2` pairs.

However, a "good pair" requires that `nums[i] == nums[j]`.

To efficiently count good pairs, we can:

- Calculate the frequency of each unique value in the array.
- For each value with frequency `f`, number of good pairs it contributes is `f * (f - 1) // 2`.

By summing all these pairs count from each frequency, we obtain the total number of good pairs.