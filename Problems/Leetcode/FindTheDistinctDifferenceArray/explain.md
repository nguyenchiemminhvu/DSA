## Problem

https://leetcode.com/problems/find-the-distinct-difference-array/

```
You are given a 0-indexed array nums of length n.

The distinct difference array of nums is an array diff of length n such that diff[i] is equal to the number of distinct elements in the suffix nums[i + 1, ..., n - 1] subtracted from the number of distinct elements in the prefix nums[0, ..., i].

Return the distinct difference array of nums.

Note that nums[i, ..., j] denotes the subarray of nums starting at index i and ending at index j inclusive. Particularly, if i > j then nums[i, ..., j] denotes an empty subarray.

Example 1:

Input: nums = [1,2,3,4,5]
Output: [-3,-1,1,3,5]
Explanation: For index i = 0, there is 1 element in the prefix and 4 distinct elements in the suffix. Thus, diff[0] = 1 - 4 = -3.
For index i = 1, there are 2 distinct elements in the prefix and 3 distinct elements in the suffix. Thus, diff[1] = 2 - 3 = -1.
For index i = 2, there are 3 distinct elements in the prefix and 2 distinct elements in the suffix. Thus, diff[2] = 3 - 2 = 1.
For index i = 3, there are 4 distinct elements in the prefix and 1 distinct element in the suffix. Thus, diff[3] = 4 - 1 = 3.
For index i = 4, there are 5 distinct elements in the prefix and no elements in the suffix. Thus, diff[4] = 5 - 0 = 5.

Example 2:

Input: nums = [3,2,3,4,2]
Output: [-2,-1,0,2,3]
Explanation: For index i = 0, there is 1 element in the prefix and 3 distinct elements in the suffix. Thus, diff[0] = 1 - 3 = -2.
For index i = 1, there are 2 distinct elements in the prefix and 3 distinct elements in the suffix. Thus, diff[1] = 2 - 3 = -1.
For index i = 2, there are 2 distinct elements in the prefix and 2 distinct elements in the suffix. Thus, diff[2] = 2 - 2 = 0.
For index i = 3, there are 3 distinct elements in the prefix and 1 distinct element in the suffix. Thus, diff[3] = 3 - 1 = 2.
For index i = 4, there are 3 distinct elements in the prefix and no elements in the suffix. Thus, diff[4] = 3 - 0 = 3.

Constraints:

1 <= n == nums.length <= 50
1 <= nums[i] <= 50
```

## Observations

1. **Problem Definition**: For each index `i`, we need to calculate `prefix_distinct[i] - suffix_distinct[i]` where:
   - `prefix_distinct[i]` = number of distinct elements in `nums[0...i]` (inclusive)
   - `suffix_distinct[i]` = number of distinct elements in `nums[i+1...n-1]` (inclusive)

2. **Key Insights**:
   - We need to track distinct elements, so using a `set` is natural
   - We can precompute prefix and suffix distinct counts separately
   - For prefix: iterate left to right, adding elements to set and recording size
   - For suffix: iterate right to left, but record the set size BEFORE adding current element

3. **Edge Cases**:
   - At index 0: prefix has 1 element (nums[0]), suffix has all elements after index 0
   - At last index: prefix has all elements up to last index, suffix is empty (0 distinct elements)
   - Duplicate elements don't increase distinct count when already in set

4. **Time Complexity**: O(n) - single pass for prefix, single pass for suffix
5. **Space Complexity**: O(n) - for prefix, suffix arrays, and sets (max size is number of distinct elements)

## Solution

1. **Prefix Calculation**: 
   - Iterate from left to right
   - Add each element to the set and record the set size
   - `prefix[i]` represents distinct elements count in `nums[0...i]`

2. **Suffix Calculation**:
   - Iterate from right to left
   - **Important**: Record the set size FIRST (before adding current element)
   - This gives us the count of distinct elements in `nums[i+1...n-1]`
   - Then add the current element for the next iteration

3. **Final Result**:
   - For each index `i`: `result[i] = prefix[i] - suffix[i]`

**Example Walkthrough** with `nums = [1,2,3,4,5]`:

- **Prefix**: `[1,2,3,4,5]` (distinct counts: 1,2,3,4,5)
- **Suffix**: `[4,3,2,1,0]` (distinct counts in suffix)
- **Result**: `[1-4, 2-3, 3-2, 4-1, 5-0] = [-3,-1,1,3,5]`

# Tags

Array, Hash Table, Prefix Sum

