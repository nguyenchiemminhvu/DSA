## Problem

https://leetcode.com/problems/longest-subsequence-with-limited-sum/description/

```
You are given an integer array nums of length n, and an integer array queries of length m.

Return an array answer of length m where answer[i] is the maximum size of a subsequence that you can take from nums such that the sum of its elements is less than or equal to queries[i].

A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.

Example 1:

Input: nums = [4,5,2,1], queries = [3,10,21]
Output: [2,3,4]
Explanation: We answer the queries as follows:
- The subsequence [2,1] has a sum less than or equal to 3. It can be proven that 2 is the maximum size of such a subsequence, so answer[0] = 2.
- The subsequence [4,5,1] has a sum less than or equal to 10. It can be proven that 3 is the maximum size of such a subsequence, so answer[1] = 3.
- The subsequence [4,5,2,1] has a sum less than or equal to 21. It can be proven that 4 is the maximum size of such a subsequence, so answer[2] = 4.

Example 2:

Input: nums = [2,3,4,5], queries = [1]
Output: [0]
Explanation: The empty subsequence is the only subsequence that has a sum less than or equal to 1, so answer[0] = 0.

Constraints:

n == nums.length
m == queries.length
1 <= n, m <= 1000
1 <= nums[i], queries[i] <= 106
```

## Observations

1. **Key Insight**: To maximize the number of elements in a subsequence with a limited sum, we should always choose the smallest available elements first. This is because using smaller elements leaves more "budget" for additional elements.

2. **Greedy Approach**: Since we want the maximum length subsequence, we can greedily pick the smallest elements until we exceed the query limit.

3. **Order Independence**: The problem asks for a subsequence, but since we only care about the count (not the actual elements or their order), we can sort the array without affecting the result.

4. **Optimization with Prefix Sums**: Instead of repeatedly summing elements for each query, we can precompute prefix sums after sorting. This transforms the problem into finding the largest prefix sum that doesn't exceed the query value.

5. **Binary Search**: Since the prefix sums are in non-decreasing order (after sorting), we can use binary search to efficiently find the answer for each query.

## Solution

**Algorithm:**

1. **Sort the input array**: `nums.sort()` - This allows us to greedily pick the smallest elements first.

2. **Convert to prefix sums**: Transform the sorted array into cumulative sums where `nums[i]` represents the sum of the first `i+1` smallest elements.

3. **Binary search for each query**: For each query value, find the largest index where the prefix sum is ≤ query value. This index + 1 represents the maximum number of elements we can include.

**Binary Search Implementation:**
- The `upper_bound` function finds the first position where the value is greater than the target
- If no such position exists, it returns `len(arr)` (meaning all elements can be included)
- The result gives us the count of elements whose prefix sum is ≤ query

**Time Complexity:** O(n log n + m log n)
- Sorting: O(n log n)
- Prefix sum computation: O(n)
- Binary search for each query: O(m log n)

**Space Complexity:** O(1) extra space (modifying input array in-place)

## Tags

array, prefix sum, binary search