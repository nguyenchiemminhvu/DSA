## Problem

https://leetcode.com/problems/subarrays-distinct-element-sum-of-squares-i/description/

```
You are given a 0-indexed integer array nums.

The distinct count of a subarray of nums is defined as:

Let nums[i..j] be a subarray of nums consisting of all the indices from i to j such that 0 <= i <= j < nums.length. Then the number of distinct values in nums[i..j] is called the distinct count of nums[i..j].
Return the sum of the squares of distinct counts of all subarrays of nums.

A subarray is a contiguous non-empty sequence of elements within an array.

Example 1:

Input: nums = [1,2,1]
Output: 15
Explanation: Six possible subarrays are:
[1]: 1 distinct value
[2]: 1 distinct value
[1]: 1 distinct value
[1,2]: 2 distinct values
[2,1]: 2 distinct values
[1,2,1]: 2 distinct values
The sum of the squares of the distinct counts in all subarrays is equal to 12 + 12 + 12 + 22 + 22 + 22 = 15.

Example 2:

Input: nums = [1,1]
Output: 3
Explanation: Three possible subarrays are:
[1]: 1 distinct value
[1]: 1 distinct value
[1,1]: 1 distinct value
The sum of the squares of the distinct counts in all subarrays is equal to 12 + 12 + 12 = 3.

Constraints:

1 <= nums.length <= 100
1 <= nums[i] <= 100
```

## Observations

1. **Subarray Generation**: We need to consider all possible subarrays of the input array. For an array of length `n`, there are `n*(n+1)/2` subarrays total.

2. **Distinct Count Calculation**: For each subarray, we need to count distinct elements. Using a set data structure is efficient for this purpose since it automatically handles duplicates.

3. **Squaring Pattern**: The key requirement is to square the distinct count for each subarray and sum all these squared values.

4. **Brute Force Feasibility**: Given the constraints (n ≤ 100), a brute force O(n³) approach is acceptable since 100³ = 1,000,000 operations are manageable.

5. **Example Walkthrough** (nums = [1,2,1]):
   - Single element subarrays: [1], [2], [1] → distinct counts: 1, 1, 1 → squares: 1, 1, 1
   - Two element subarrays: [1,2], [2,1] → distinct counts: 2, 2 → squares: 4, 4  
   - Three element subarray: [1,2,1] → distinct count: 2 → square: 4
   - Total: 1 + 1 + 1 + 4 + 4 + 4 = 15

## Solution

The solution implements a **brute force approach** with three nested loops:

### Algorithm Steps:
1. **Outer loop (sublen)**: Iterate through all possible subarray lengths from 0 to n-1
2. **Middle loop (i)**: For each length, iterate through all valid starting positions
3. **Inner loop (j)**: Build each subarray element by element, adding to a set to track distinct elements
4. **Calculate contribution**: For each complete subarray, square the number of distinct elements and add to result

### Key Insights:
- The set automatically handles duplicate counting, giving us the distinct element count
- The range `range(i, i + sublen + 1)` correctly generates subarrays of length `sublen + 1`
- Each subarray is processed exactly once

### Complexity Analysis:
- **Time Complexity**: O(n³) where n is the length of nums
  - Outer loop: O(n) iterations  
  - Middle loop: O(n) iterations
  - Inner loop: O(n) iterations
  - Set operations: O(1) average case
- **Space Complexity**: O(n) for the set storing distinct elements

### Alternative Approaches:
For larger inputs, more optimized approaches could be considered:
- **Sliding window with hash maps**: O(n²) time complexity
- **Mathematical formulas**: For specific patterns, closed-form solutions might exist

# Tags

- Array
- Hash Table 
- Set
- Brute Force
- Subarray
- Nested Loops

