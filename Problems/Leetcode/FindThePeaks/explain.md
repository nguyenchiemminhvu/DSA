## Problem

https://leetcode.com/problems/find-the-peaks/description/

```
You are given a 0-indexed array mountain. Your task is to find all the peaks in the mountain array.

Return an array that consists of indices of peaks in the given array in any order.

Notes:

A peak is defined as an element that is strictly greater than its neighboring elements.
The first and last elements of the array are not a peak.

Example 1:

Input: mountain = [2,4,4]
Output: []
Explanation: mountain[0] and mountain[2] can not be a peak because they are first and last elements of the array.
mountain[1] also can not be a peak because it is not strictly greater than mountain[2].
So the answer is [].

Example 2:

Input: mountain = [1,4,3,8,5]
Output: [1,3]
Explanation: mountain[0] and mountain[4] can not be a peak because they are first and last elements of the array.
mountain[2] also can not be a peak because it is not strictly greater than mountain[3] and mountain[1].
But mountain [1] and mountain[3] are strictly greater than their neighboring elements.
So the answer is [1,3].

Constraints:

3 <= mountain.length <= 100
1 <= mountain[i] <= 100
```

## Observations

1. **Boundary Conditions**: Since a peak needs both left and right neighbors, we only need to check elements from index 1 to n-2 (where n is the length of the array).

2. **Peak Definition**: An element at index i is a peak if:
   - `mountain[i-1] < mountain[i]` (greater than left neighbor)
   - `mountain[i] > mountain[i+1]` (greater than right neighbor)
   
3. **Linear Search Sufficiency**: We can solve this in a single pass since each element's peak status is independent of other peaks.

4. **No Edge Cases for Empty Results**: If no peaks exist, we simply return an empty list.

5. **Constraint Analysis**: With array length between 3-100 and values 1-100, we don't need to worry about overflow or performance optimization.

## Solution

1. **Initialize Result List**: `res = []` to store the indices of peaks.

2. **Iterate Through Potential Peaks**: 
   - Start from index 1 (second element)
   - End at index `len(mountain) - 2` (second-to-last element)
   - This ensures we always have valid left and right neighbors

3. **Check Peak Condition**:
   - `mountain[i - 1] < mountain[i] > mountain[i + 1]`
   - This is a chained comparison that checks both conditions simultaneously
   - Left neighbor is strictly less than current element
   - Current element is strictly greater than right neighbor

4. **Collect Results**: If the condition is met, append the current index `i` to the result list.

5. **Return Results**: Return the list of all peak indices found.

### Complexity Analysis:

- **Time Complexity**: O(n) where n is the length of the mountain array
  - We visit each element exactly once
  - Each comparison operation is O(1)

- **Space Complexity**: O(k) where k is the number of peaks found
  - In the worst case, this could be O(n) if every possible position is a peak
  - The algorithm uses constant extra space aside from the result array

### Example Walkthrough:

For `mountain = [1,4,3,8,5]`:
- i=1: mountain[0]=1 < mountain[1]=4 > mountain[2]=3 ✓ → Peak at index 1
- i=2: mountain[1]=4 > mountain[2]=3 < mountain[3]=8 ✗ → Not a peak  
- i=3: mountain[2]=3 < mountain[3]=8 > mountain[4]=5 ✓ → Peak at index 3

Result: `[1, 3]`

### Key Insights:

- The solution is elegant in its simplicity - no complex data structures needed
- The chained comparison `mountain[i-1] < mountain[i] > mountain[i+1]` is both readable and efficient
- The algorithm naturally handles all edge cases through the loop bounds
- This is an optimal solution as we must examine each potential peak position at least once

# Tags

