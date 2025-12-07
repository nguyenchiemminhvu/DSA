## Problem

https://leetcode.com/problems/find-the-largest-almost-missing-integer/description/

```
You are given an integer array nums and an integer k.

An integer x is almost missing from nums if x appears in exactly one subarray of size k within nums.

Return the largest almost missing integer from nums. If no such integer exists, return -1.

A subarray is a contiguous sequence of elements within an array.

Example 1:
Input: nums = [3,9,2,1,7], k = 3
Output: 7
Explanation:
1 appears in 2 subarrays of size 3: [9, 2, 1] and [2, 1, 7].
2 appears in 3 subarrays of size 3: [3, 9, 2], [9, 2, 1], [2, 1, 7].
3 appears in 1 subarray of size 3: [3, 9, 2].
7 appears in 1 subarray of size 3: [2, 1, 7].
9 appears in 2 subarrays of size 3: [3, 9, 2], and [9, 2, 1].
We return 7 since it is the largest integer that appears in exactly one subarray of size k.

Example 2:
Input: nums = [3,9,7,2,1,7], k = 4
Output: 3
Explanation:
1 appears in 2 subarrays of size 4: [9, 7, 2, 1], [7, 2, 1, 7].
2 appears in 3 subarrays of size 4: [3, 9, 7, 2], [9, 7, 2, 1], [7, 2, 1, 7].
3 appears in 1 subarray of size 4: [3, 9, 7, 2].
7 appears in 3 subarrays of size 4: [3, 9, 7, 2], [9, 7, 2, 1], [7, 2, 1, 7].
9 appears in 2 subarrays of size 4: [3, 9, 7, 2], [9, 7, 2, 1].
We return 3 since it is the largest and only integer that appears in exactly one subarray of size k.

Example 3:
Input: nums = [0,0], k = 1
Output: -1
Explanation:
There is no integer that appears in only one subarray of size 1.

Constraints:
1 <= nums.length <= 50
0 <= nums[i] <= 50
1 <= k <= nums.length
```

## Observations

1. **Key Insight**: An element can appear in exactly one subarray of size k only if it appears at the boundaries of the array (first k-1 or last k-1 positions).

2. **Why boundary elements matter**:
   - If an element appears in the middle of the array (not in first or last k-1 positions), it will appear in at least 2 subarrays because the sliding window will cover it multiple times.
   - Only elements at the start (index 0 to k-2) or end (index n-k+1 to n-1) can potentially appear in exactly one subarray.

3. **Special cases**:
   - **k = 1**: Every element appears in exactly one subarray of size 1 (itself). Return the largest element that appears at most once in the array.
   - **k = n**: There's only one subarray (the entire array), so all elements appear in exactly one subarray. Return the maximum element.

4. **General case (1 < k < n)**:
   - Only check the first element `nums[0]` and last element `nums[-1]`.
   - These are the only positions where an element can appear in exactly one k-sized subarray.
   - The first element only appears in the first subarray `[0:k]`.
   - The last element only appears in the last subarray `[n-k:n]`.
   - However, we need to verify they don't appear multiple times in the array (counter check).

## Solution

**Time Complexity**: O(n) - for counting elements
**Space Complexity**: O(n) - for the counter dictionary

**Algorithm**:
1. Count the frequency of all elements in the array.
2. Handle the special case where k = 1 (return max element with frequency ≤ 1).
3. Handle the special case where k = n (return max element in array).
4. For the general case, check only the first and last elements, and return the largest one that appears at most once in the entire array.

# Tags

#array #sliding-window #hash-table #counting #optimization

