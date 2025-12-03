## Problem

https://leetcode.com/problems/count-the-number-of-incremovable-subarrays-i/description/

```
You are given a 0-indexed array of positive integers nums.

A subarray of nums is called incremovable if nums becomes strictly increasing on removing the subarray. 
For example, the subarray [3, 4] is an incremovable subarray of [5, 3, 4, 6, 7] because removing this 
subarray changes the array [5, 3, 4, 6, 7] to [5, 6, 7] which is strictly increasing.

Return the total number of incremovable subarrays of nums.

Note that an empty array is considered strictly increasing.

A subarray is a contiguous non-empty sequence of elements within an array.

Example 1:
Input: nums = [1,2,3,4]
Output: 10
Explanation: The 10 incremovable subarrays are: [1], [2], [3], [4], [1,2], [2,3], [3,4], [1,2,3], 
[2,3,4], and [1,2,3,4], because on removing any one of these subarrays nums becomes strictly increasing.

Example 2:
Input: nums = [6,5,7,8]
Output: 7
Explanation: The 7 incremovable subarrays are: [5], [6], [5,7], [6,5], [5,7,8], [6,5,7] and [6,5,7,8].

Example 3:
Input: nums = [8,7,6,6]
Output: 3
Explanation: The 3 incremovable subarrays are: [8,7,6], [7,6,6], and [8,7,6,6]. Note that [8,7] is 
not an incremovable subarray because after removing [8,7] nums becomes [6,6], which is sorted in 
ascending order but not strictly increasing.

Constraints:
- 1 <= nums.length <= 50
- 1 <= nums[i] <= 50
```

## Observations

1. **Incremovable Subarray Definition**: A subarray is incremovable if removing it makes the remaining array strictly increasing (each element must be strictly greater than the previous one).

2. **Brute Force Approach**: Since the array length is small (≤ 50), we can afford to check all possible subarrays:
   - There are O(n²) possible subarrays (all combinations of start index i and end index j where i ≤ j)
   - For each subarray removal, we need to verify if the remaining array is strictly increasing

3. **Key Insights**:
   - A subarray from index `i` to `j` (inclusive) can be removed by concatenating `arr[0:i]` and `arr[j+1:]`
   - We need to check if this concatenated array is strictly increasing
   - An empty array is considered strictly increasing (important edge case)

4. **Time Complexity Analysis**:
   - Outer loops: O(n²) to enumerate all subarrays
   - Inner validation: O(n) to check if remaining array is sorted
   - Total: O(n³) - acceptable for n ≤ 50

5. **Edge Cases**:
   - Single element array: All subarrays are incremovable (removes entire array → empty array)
   - Already sorted array: All subarrays are incremovable
   - Array with duplicates: Must ensure strictly increasing (no equal elements)

## Solution

### Approach: Brute Force Enumeration

**Strategy**: Try removing every possible subarray and check if the remaining array is strictly increasing.

**Algorithm**:
1. Iterate through all possible subarray start positions (i from 0 to n-1)
2. For each start position, iterate through all possible end positions (j from i to n-1)
3. For each subarray [i, j]:
   - Create the remaining array by concatenating arr[0:i] and arr[j+1:]
   - Check if this remaining array is strictly increasing
   - If yes, increment the count
4. Return the total count

**Implementation Details**:
- `is_sorted(arr)`: Helper function that checks if an array is strictly increasing
  - Returns `False` if any element is less than or equal to the previous element
  - Returns `True` for empty arrays or strictly increasing arrays
- We use Python slicing to create the remaining array: `arr[0:i] + arr[j+1:]`

**Example Walkthrough** (nums = [6,5,7,8]):
- Remove [6] (i=0, j=0): [5,7,8] → strictly increasing ✓
- Remove [5] (i=1, j=1): [6,7,8] → strictly increasing ✓
- Remove [7] (i=2, j=2): [6,5,8] → not strictly increasing ✗
- Remove [8] (i=3, j=3): [6,5,7] → not strictly increasing ✗
- Remove [6,5] (i=0, j=1): [7,8] → strictly increasing ✓
- Remove [5,7] (i=1, j=2): [6,8] → strictly increasing ✓
- Remove [7,8] (i=2, j=3): [6,5] → not strictly increasing ✗
- Remove [6,5,7] (i=0, j=2): [8] → strictly increasing ✓
- Remove [5,7,8] (i=1, j=3): [6] → strictly increasing ✓
- Remove [6,5,7,8] (i=0, j=3): [] → strictly increasing ✓
- Total: 7 incremovable subarrays

**Time Complexity**: O(n³)
- O(n²) to enumerate all subarrays
- O(n) to check if the remaining array is sorted
- Total: n² × n = n³

**Space Complexity**: O(n)
- O(n) for the concatenated array created in each iteration

# Tags
#array #brute-force #two-pointers #enumeration

