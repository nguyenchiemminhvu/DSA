## Problem

https://leetcode.com/problems/sum-of-all-odd-length-subarrays/

```
Given an array of positive integers arr, return the sum of all possible odd-length subarrays of arr.

A subarray is a contiguous subsequence of the array.

Example 1:

Input: arr = [1,4,2,5,3]
Output: 58
Explanation: The odd-length subarrays of arr and their sums are:
[1] = 1
[4] = 4
[2] = 2
[5] = 5
[3] = 3
[1,4,2] = 7
[4,2,5] = 11
[2,5,3] = 10
[1,4,2,5,3] = 15
If we add all these together we get 1 + 4 + 2 + 5 + 3 + 7 + 11 + 10 + 15 = 58

Example 2:

Input: arr = [1,2]
Output: 3
Explanation: There are only 2 subarrays of odd length, [1] and [2]. Their sum is 3.

Example 3:

Input: arr = [10,11,12]
Output: 66

Constraints:

1 <= arr.length <= 100
1 <= arr[i] <= 1000
```

## Observations

1. **Problem Understanding**: We need to find the sum of all possible odd-length subarrays. Odd lengths are 1, 3, 5, 7, etc.

2. **Brute Force Approach**: For each possible odd length, generate all subarrays of that length and sum their elements.

3. **Key Insight**: We can use prefix sums to calculate subarray sums efficiently in O(1) time instead of O(k) where k is the subarray length.

4. **Pattern**: For an array of length n, the odd lengths we need to consider are: 1, 3, 5, ..., up to the largest odd number ≤ n.

5. **Efficiency**: Using prefix sums, we can calculate any subarray sum from index i to j as `prefix[j+1] - prefix[i]`.

## Solution

**Approach: Prefix Sum with Sliding Window**

**Algorithm:**
1. **Build Prefix Sum Array**: Create a prefix sum array where `prefix[i]` represents the sum of elements from index 0 to i-1.
2. **Iterate Through Odd Lengths**: For each odd length (1, 3, 5, ...), find all subarrays of that length.
3. **Use Prefix Sum**: For each subarray from index `left` to `right`, calculate sum as `prefix[right+1] - prefix[left]`.
4. **Accumulate Results**: Add all subarray sums to get the final result.

**Key Points:**
- `sublen` represents length-1, so when `sublen=0`, actual length=1; when `sublen=2`, actual length=3, etc.
- `range(0, n, 2)` gives us 0, 2, 4, ... which corresponds to odd lengths 1, 3, 5, ...
- The sliding window approach ensures we consider all possible subarrays of each odd length.

**Time Complexity:** O(n²) - We iterate through O(n) odd lengths and for each length, we slide the window O(n) times.

**Space Complexity:** O(n) - For the prefix sum array.

**Example Walkthrough (arr = [1,4,2,5,3]):**
- Length 1: [1]=1, [4]=4, [2]=2, [5]=5, [3]=3 → Sum = 15
- Length 3: [1,4,2]=7, [4,2,5]=11, [2,5,3]=10 → Sum = 28  
- Length 5: [1,4,2,5,3]=15 → Sum = 15
- Total: 15 + 28 + 15 = 58

## Tags

