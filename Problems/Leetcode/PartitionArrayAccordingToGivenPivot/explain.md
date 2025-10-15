## Problem

https://leetcode.com/problems/partition-array-according-to-given-pivot/

```
You are given a 0-indexed integer array nums and an integer pivot. Rearrange nums such that the following conditions are satisfied:

Every element less than pivot appears before every element greater than pivot.
Every element equal to pivot appears in between the elements less than and greater than pivot.
The relative order of the elements less than pivot and the elements greater than pivot is maintained.
More formally, consider every pi, pj where pi is the new position of the ith element and pj is the new position of the jth element. If i < j and both elements are smaller (or larger) than pivot, then pi < pj.
Return nums after the rearrangement.

Example 1:

Input: nums = [9,12,5,10,14,3,10], pivot = 10
Output: [9,5,3,10,10,12,14]
Explanation: 
The elements 9, 5, and 3 are less than the pivot so they are on the left side of the array.
The elements 12 and 14 are greater than the pivot so they are on the right side of the array.
The relative ordering of the elements less than and greater than pivot is also maintained. [9, 5, 3] and [12, 14] are the respective orderings.

Example 2:

Input: nums = [-3,4,3,2], pivot = 2
Output: [-3,2,4,3]
Explanation: 
The element -3 is less than the pivot so it is on the left side of the array.
The elements 4 and 3 are greater than the pivot so they are on the right side of the array.
The relative ordering of the elements less than and greater than pivot is also maintained. [-3] and [4, 3] are the respective orderings.

Constraints:

1 <= nums.length <= 105
-106 <= nums[i] <= 106
pivot equals to an element of nums.
```

## Observations

1. **Three-way partitioning**: The problem requires us to partition the array into three sections:
   - Elements less than pivot (maintain relative order)
   - Elements equal to pivot (can be in any order since they're all the same)
   - Elements greater than pivot (maintain relative order)

2. **Stable partitioning**: The relative order within each partition must be preserved. This means we can't use standard quicksort partitioning which might not maintain stability.

3. **Linear scan approach**: Since we need to maintain relative order, a simple linear scan collecting elements into separate arrays is the most straightforward approach.

4. **Memory trade-off**: We use O(n) extra space to create three separate arrays, but this guarantees we maintain the relative ordering requirement.

5. **Single pass**: We only need one pass through the original array to classify each element.

## Solution

1. **Initialize three arrays**: Create separate arrays to store elements less than, equal to, and greater than the pivot.

2. **Single pass classification**: Iterate through the input array once, classifying each element:
   - If `val == pivot`: add to `equal` array
   - If `val < pivot`: add to `less` array  
   - If `val > pivot`: add to `greater` array

3. **Concatenate results**: Combine the three arrays in order: `less + equal + greater`

**Why this works:**
- **Relative order preservation**: Since we append elements to each array in the order we encounter them, the relative order within each partition is maintained.
- **Correct positioning**: Elements less than pivot come first, then equal elements, then greater elements.
- **Handles duplicates**: Multiple occurrences of the pivot value are correctly grouped together.

**Time Complexity:** O(n) - single pass through the array
**Space Complexity:** O(n) - for the three auxiliary arrays

**Alternative approaches:**
- **In-place partitioning**: Could use a more complex two-pass approach to achieve O(1) extra space, but would be more complicated to implement while maintaining stability.
- **Counting approach**: For scenarios with limited range of values, could count occurrences and reconstruct the array.

## Tags

array, greedy