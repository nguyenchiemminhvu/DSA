## Problem

https://leetcode.com/problems/find-closest-number-to-zero/

```
Given an integer array nums of size n, return the number with the value closest to 0 in nums. 
If there are multiple answers, return the number with the largest value.

Example 1:
Input: nums = [-4,-2,1,4,8]
Output: 1
Explanation:
The distance from -4 to 0 is |-4| = 4.
The distance from -2 to 0 is |-2| = 2.
The distance from 1 to 0 is |1| = 1.
The distance from 4 to 0 is |4| = 4.
The distance from 8 to 0 is |8| = 8.
Thus, the closest number to 0 in the array is 1.

Example 2:
Input: nums = [2,-1,1]
Output: 1
Explanation: 1 and -1 are both the closest numbers to 0, so 1 being larger is returned.

Constraints:
- 1 <= n <= 1000
- -10^5 <= nums[i] <= 10^5
```

## Observations

1. **Distance Measurement**: We need to find the number with the smallest absolute value (distance from 0).

2. **Tie-Breaking Rule**: When two numbers have the same distance from 0 (e.g., -1 and 1), we must return the larger value (1 in this case).

3. **Single Pass Solution**: We can solve this in O(n) time by iterating through the array once, keeping track of:
   - The minimum distance found so far
   - The result number corresponding to that minimum distance

4. **Edge Cases**:
   - Array with single element (return that element)
   - All positive numbers (return the smallest)
   - All negative numbers (return the largest, closest to 0)
   - Mix of positive and negative with same absolute values

## Solution

**Algorithm Steps:**

1. **Initialize Tracking Variables**:
   - `dist = float('inf')`: Tracks the minimum distance from 0 found so far
   - `res = float('inf')`: Stores the result number with the minimum distance

2. **Iterate Through Array**:
   - For each value `val` in the array:
     - **Case 1**: If `abs(val) < dist` (found a closer number):
       - Update `dist` to `abs(val)`
       - Update `res` to `val`
     - **Case 2**: If `abs(val) == dist` (tie situation):
       - Update `res` to `max(res, val)` to ensure we keep the larger value

3. **Return Result**: After processing all numbers, return `res`

### Example Walkthrough

**Example 1**: `nums = [-4, -2, 1, 4, 8]`

| Step | val | abs(val) | dist | res | Action |
|------|-----|----------|------|-----|--------|
| Init | - | - | ∞ | ∞ | - |
| 1 | -4 | 4 | 4 | -4 | 4 < ∞, update both |
| 2 | -2 | 2 | 2 | -2 | 2 < 4, update both |
| 3 | 1 | 1 | 1 | 1 | 1 < 2, update both |
| 4 | 4 | 4 | 1 | 1 | 4 > 1, no change |
| 5 | 8 | 8 | 1 | 1 | 8 > 1, no change |

**Result**: 1

**Example 2**: `nums = [2, -1, 1]`

| Step | val | abs(val) | dist | res | Action |
|------|-----|----------|------|-----|--------|
| Init | - | - | ∞ | ∞ | - |
| 1 | 2 | 2 | 2 | 2 | 2 < ∞, update both |
| 2 | -1 | 1 | 1 | -1 | 1 < 2, update both |
| 3 | 1 | 1 | 1 | 1 | 1 == 1, res = max(-1, 1) = 1 |

**Result**: 1

### Complexity Analysis

- **Time Complexity**: O(n) where n is the length of the array
  - We iterate through the array exactly once
  - Each comparison and update operation is O(1)

- **Space Complexity**: O(1)
  - We only use two variables (`dist` and `res`) regardless of input size
  - No additional data structures are needed

### Alternative Approaches

1. **Sorting Approach**: Sort by absolute value, then by value in descending order. Return first element. O(n log n) time.

2. **Min-Heap Approach**: Use custom comparator with heap. O(n log n) time.

3. **Two Variables Approach**: Track closest positive and closest negative separately, then compare at the end. O(n) time.

The provided solution is optimal with O(n) time and O(1) space.

# Tags

`Array` `Math` `Greedy` `Single Pass`

