## Problem

https://leetcode.com/problems/find-all-k-distant-indices-in-an-array/

```
You are given a 0-indexed integer array nums and two integers key and k. A k-distant index is an index i of nums for which there exists at least one index j such that |i - j| <= k and nums[j] == key.

Return a list of all k-distant indices sorted in increasing order.

Example 1:

Input: nums = [3,4,9,1,3,9,5], key = 9, k = 1
Output: [1,2,3,4,5,6]
Explanation: Here, nums[2] == key and nums[5] == key.
- For index 0, |0 - 2| > k and |0 - 5| > k, so there is no j where |0 - j| <= k and nums[j] == key. Thus, 0 is not a k-distant index.
- For index 1, |1 - 2| <= k and nums[2] == key, so 1 is a k-distant index.
- For index 2, |2 - 2| <= k and nums[2] == key, so 2 is a k-distant index.
- For index 3, |3 - 2| <= k and nums[2] == key, so 3 is a k-distant index.
- For index 4, |4 - 5| <= k and nums[5] == key, so 4 is a k-distant index.
- For index 5, |5 - 5| <= k and nums[5] == key, so 5 is a k-distant index.
- For index 6, |6 - 5| <= k and nums[5] == key, so 6 is a k-distant index.
Thus, we return [1,2,3,4,5,6] which is sorted in increasing order.

Example 2:

Input: nums = [2,2,2,2,2], key = 2, k = 2
Output: [0,1,2,3,4]
Explanation: For all indices i in nums, there exists some index j such that |i - j| <= k and nums[j] == key, so every index is a k-distant index. 
Hence, we return [0,1,2,3,4].

Constraints:

1 <= nums.length <= 1000
1 <= nums[i] <= 1000
key is an integer from the array nums.
1 <= k <= nums.length
```

## Observations

1. **Problem Understanding**: We need to find all indices `i` where there exists at least one index `j` such that `|i - j| <= k` and `nums[j] == key`.

2. **Key Insight**: Instead of checking every index against every possible key position, we can:
   - First find all positions where `nums[j] == key`
   - For each key position, determine the range of indices that are k-distant from it
   - Collect all such ranges and remove duplicates

3. **Range Calculation**: For a key at index `j`, all indices in the range `[j-k, j+k]` are k-distant from it (bounded by array limits).

4. **Efficiency Consideration**: The solution uses `set()` to remove duplicates, which is necessary when ranges overlap.

## Solution

1. **Find Key Positions** (Lines 2-4):
   - Iterate through the array and collect all indices where `nums[i] == key`
   - Store these indices in `key_idx` list

2. **Generate K-Distant Ranges** (Lines 6-9):
   - For each key position `idx`, calculate the valid range `[idx-k, idx+k]`
   - Use `max(0, idx-k)` to ensure we don't go below index 0
   - Use `min(n-1, idx+k)` to ensure we don't exceed the last valid index
   - Generate all indices in this range and add them to `res`

3. **Remove Duplicates** (Line 9):
   - Convert `res` to a set to remove duplicates (overlapping ranges)
   - Convert back to list for the final result
   - The set automatically sorts the indices in ascending order

**Time Complexity**: O(n + m*k) where n is the length of nums and m is the number of key occurrences
**Space Complexity**: O(n) in the worst case when all indices are k-distant

**Example Walkthrough** (nums = [3,4,9,1,3,9,5], key = 9, k = 1):
- Key positions: [2, 5]
- For index 2: range [1, 3] → indices [1, 2, 3]
- For index 5: range [4, 6] → indices [4, 5, 6]
- Combined: [1, 2, 3, 4, 5, 6] (no duplicates in this case)

# Tags

Array, Iteration, Range Processing

