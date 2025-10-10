## Problem

https://leetcode.com/problems/median-of-two-sorted-arrays/description/

```
Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.

The overall run time complexity should be O(log (m+n)).
 
 Both input arrays are already sorted.
 The median is the middle value (or average of two middle values) of the combined sorted array.
 The simplest way is to merge both arrays and sort the result, then find the median.
 This approach does not meet the optimal O(log(m+n)) requirement, but is easy to implement and understand.

Example 1:

Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.

Example 2:

Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.

Constraints:

nums1.length == m
nums2.length == n
0 <= m <= 1000
0 <= n <= 1000
1 <= m + n <= 2000
-106 <= nums1[i], nums2[i] <= 106
```

## Solution

Combine both arrays into one.

Sort the combined array.

If the total length is odd, return the middle element.

If the total length is even, return the average of the two middle elements.

## Tags