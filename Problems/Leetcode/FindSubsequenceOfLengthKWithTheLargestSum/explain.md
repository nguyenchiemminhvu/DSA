## Problem

https://leetcode.com/problems/find-subsequence-of-length-k-with-the-largest-sum/description/

```
You are given an integer array nums and an integer k. You want to find a subsequence of nums of length k that has the largest sum.

Return any such subsequence as an integer array of length k.

A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.

Example 1:
Input: nums = [2,1,3,3], k = 2
Output: [3,3]
Explanation: The subsequence has the largest sum of 3 + 3 = 6.

Example 2:
Input: nums = [-1,-2,3,4], k = 3
Output: [-1,3,4]
Explanation: The subsequence has the largest sum of -1 + 3 + 4 = 6.

Example 3:
Input: nums = [3,4,3,3], k = 2
Output: [3,4]
Explanation: The subsequence has the largest sum of 3 + 4 = 7. Another possible subsequence is [4, 3].

Constraints:
- 1 <= nums.length <= 1000
- -10^5 <= nums[i] <= 10^5
- 1 <= k <= nums.length
```

## Observations

1. **Subsequence Property**: We need to maintain the original order of elements from the input array. This is different from finding k largest elements and sorting them.

2. **Maximizing Sum**: To get the largest sum, we should select the k largest values from the array.

3. **Order Preservation**: After selecting the k largest values, we must arrange them in the same relative order as they appeared in the original array.

4. **Index Tracking**: Since we need to preserve order, we must track the original indices of the elements we select.

## Solution

### Approach: Sort by Value, Restore by Index

**Algorithm:**
1. **Pair with Indices**: Create pairs of (value, original_index) for each element
2. **Sort by Value**: Sort these pairs by value to identify the k largest elements
3. **Select k Largest**: Take the last k elements from the sorted array (largest values)
4. **Restore Original Order**: Sort the selected elements by their original indices
5. **Extract Values**: Return just the values (without indices)

**Example Walkthrough (nums = [2,1,3,3], k = 2):**
1. After pairing: `[(2,0), (1,1), (3,2), (3,3)]`
2. After sorting by value: `[(1,1), (2,0), (3,2), (3,3)]`
3. Select k=2 largest: `[(3,3), (3,2)]`
4. Sort by index: `[(3,2), (3,3)]`
5. Extract values: `[3, 3]`

**Time Complexity:** O(n log n)
- Sorting the array takes O(n log n)
- Selecting k elements takes O(k)
- Sorting k elements by index takes O(k log k)
- Overall: O(n log n) dominates

**Space Complexity:** O(n)
- Storage for the paired array: O(n)
- Storage for result: O(k)
- Overall: O(n)

**Key Insight:** By storing original indices, we can first identify which elements to include (the k largest), then restore their original order to satisfy the subsequence requirement.

# Tags
#array #sorting #greedy #subsequence

