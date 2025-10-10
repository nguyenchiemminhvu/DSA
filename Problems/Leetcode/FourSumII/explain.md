## Problem

https://leetcode.com/problems/4sum-ii/description/

```
Given four integer arrays nums1, nums2, nums3, and nums4 all of length n, return the number of tuples (i, j, k, l) such that:

0 <= i, j, k, l < n
nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0

Example 1:

Input: nums1 = [1,2], nums2 = [-2,-1], nums3 = [-1,2], nums4 = [0,2]
Output: 2
Explanation:
The two tuples are:
1. (0, 0, 0, 1) -> nums1[0] + nums2[0] + nums3[0] + nums4[1] = 1 + (-2) + (-1) + 2 = 0
2. (1, 1, 0, 0) -> nums1[1] + nums2[1] + nums3[0] + nums4[0] = 2 + (-1) + (-1) + 0 = 0

Example 2:

Input: nums1 = [0], nums2 = [0], nums3 = [0], nums4 = [0]
Output: 1

Constraints:

n == nums1.length
n == nums2.length
n == nums3.length
n == nums4.length
1 <= n <= 200
-228 <= nums1[i], nums2[i], nums3[i], nums4[i] <= 228
```

## Observations

Checking every possible combination of four numbers is very slow (`O(n^4)`).

We can make the problem faster by splitting it into two parts: (`nums1` + `nums2`) and (`nums3` + `nums4`).

If we know how many ways (`a + b`) can `sum` to a value, we can look for (`c + d`) that `sum` to the negative of that value.

Using a hash table (dictionary) helps us count sums quickly and efficiently.

## Solution
1. Use a dictionary to count all possible sums of pairs from nums1 and `nums2`.
- For each `a` in nums1 and `b` in `nums2`, calculate `a + b` and store how many times each `sum` appears.
2. For each pair `(c, d)` from `nums3` and `nums4`, calculate `-(c + d)`.
- Check if this value exists in the dictionary from step `1`.
- If it does, add the `count` to the result.
3. Return the total `count`.

## Tags

array, hash table