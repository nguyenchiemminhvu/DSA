## Problem

https://leetcode.com/problems/trionic-array-i/description/

```
You are given an integer array nums of length n.

An array is trionic if there exist indices 0 < p < q < n − 1 such that:

- nums[0...p] is strictly increasing,
- nums[p...q] is strictly decreasing,
- nums[q...n − 1] is strictly increasing.

Return true if nums is trionic, otherwise return false.

Example 1:
Input: nums = [1,3,5,4,2,6]
Output: true
Explanation:
Pick p = 2, q = 4:
- nums[0...2] = [1, 3, 5] is strictly increasing (1 < 3 < 5).
- nums[2...4] = [5, 4, 2] is strictly decreasing (5 > 4 > 2).
- nums[4...5] = [2, 6] is strictly increasing (2 < 6).

Example 2:
Input: nums = [2,1,3]
Output: false
Explanation:
There is no way to pick p and q to form the required three segments.

Constraints:
- 3 <= n <= 100
- -1000 <= nums[i] <= 1000
```

## Observations

1. **Pattern Structure**: A trionic array must have exactly three segments:
   - Ascending segment at the start
   - Descending segment in the middle
   - Ascending segment at the end

2. **Key Requirements**:
   - All segments must be **strictly** increasing/decreasing (no equal consecutive elements)
   - Each segment must contain at least 2 elements (since p > 0, q > p, n-1 > q)
   - The pattern is: UP → DOWN → UP

3. **Edge Cases**:
   - If any two consecutive elements are equal, return false immediately
   - The array must start with an increase (prefix[0] and prefix[1] must be 1)
   - The array must end with an increase (prefix[-1] must be 1)
   - There must be at least one decreasing segment in the middle

4. **Validation Strategy**:
   - Track the direction of change between each consecutive pair
   - Ensure the first segment is ascending
   - Ensure the last segment is ascending  
   - Ensure the middle segment is descending
   - No other pattern variations are allowed

## Solution

**Time Complexity**: O(n) - We iterate through the array a constant number of times
**Space Complexity**: O(n) - We use a prefix array to store direction information

**Algorithm Breakdown**:

1. **Build Direction Array**: Create `prefix` array where each element indicates whether the transition to that index is increasing (1) or decreasing (-1)

2. **Early Exit**: If any consecutive elements are equal, the array cannot be trionic

3. **Find Decreasing Segment Boundaries**:
   - `left`: First index where decrease starts
   - `right`: Last index where decrease ends

4. **Validate Pattern**:
   - Check first two transitions are increasing (ensures valid ascending start)
   - Check last transition is increasing (ensures valid ascending end)
   - Check middle segment exists and is all decreasing

**Example Walkthrough** (nums = [1,3,5,4,2,6]):
- prefix = [1, 1, 1, -1, -1, 1]
- left moves to index 3 (first -1)
- right moves to index 4 (last -1 from right)
- prefix[3:5] = [-1, -1] (all decreasing) ✓
- Returns true

# Tags
#array #greedy #pattern-matching #two-pointers

