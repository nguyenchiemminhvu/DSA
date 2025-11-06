## Problem

https://leetcode.com/problems/element-appearing-more-than-25-in-sorted-array/description/

```
Given an integer array sorted in non-decreasing order, there is exactly one integer in the array that occurs more than 25% of the time, return that integer.

Example 1:

Input: arr = [1,2,2,6,6,6,6,7,10]
Output: 6

Example 2:

Input: arr = [1,1]
Output: 1

Constraints:

1 <= arr.length <= 104
0 <= arr[i] <= 105
```

## Observations

1. **Problem Requirements:**
   - Find the element that appears more than 25% of the time in a sorted array
   - There is exactly one such element guaranteed to exist
   - The array is sorted in non-decreasing order

2. **Key Insight - Mathematical Relationship:**
   - If an element appears more than 25% of the time, it appears more than `n/4` times
   - In a sorted array, if an element appears at position `i`, and it appears more than `n/4` times, then `arr[i] == arr[i + n/4]`
   - This is because identical elements are grouped together in a sorted array

3. **Why the Algorithm Works:**
   - We calculate `n = len(arr) // 4` (integer division gives us the floor)
   - If an element appears more than `n/4` times, then there must be at least `n + 1` occurrences
   - So if we find `arr[i] == arr[i + n]`, we've found an element that spans at least `n + 1` positions
   - Since `n = floor(len(arr)/4)`, having `n + 1` occurrences means more than `len(arr)/4` occurrences, which is more than 25%

4. **Loop Range Optimization:**
   - We only need to check indices from `0` to `len(arr) - n - 1`
   - This ensures `i + n` doesn't go out of bounds
   - We don't need to check every position since we're guaranteed to find the element

## Solution

1. **Calculate threshold distance:** `n = len(arr) // 4`
   - This represents the floor of 25% of the array length

2. **Check each position:** For each index `i` from `0` to `len(arr) - n - 1`:
   - Compare `arr[i]` with `arr[i + n]`
   - If they're equal, this element spans at least `n + 1` positions
   - Since `n + 1 > len(arr)/4`, this element appears more than 25% of the time

3. **Return the element:** The first element that satisfies this condition is our answer

**Example walkthrough:**
- Input: `arr = [1,2,2,6,6,6,6,7,10]`, length = 9
- `n = 9 // 4 = 2`
- Check positions:
  - `i=0`: `arr[0] = 1`, `arr[2] = 2` → not equal
  - `i=1`: `arr[1] = 2`, `arr[3] = 6` → not equal  
  - `i=2`: `arr[2] = 2`, `arr[4] = 6` → not equal
  - `i=3`: `arr[3] = 6`, `arr[5] = 6` → equal! Return 6

**Time Complexity:** O(n) - single pass through the array
**Space Complexity:** O(1) - only using constant extra space

**Why this is efficient:**
- No need to count frequencies
- No need for hash maps or extra data structures
- Leverages the sorted property of the array
- Guaranteed to find the answer due to the problem constraints

# Tags

array, math, sorted array

