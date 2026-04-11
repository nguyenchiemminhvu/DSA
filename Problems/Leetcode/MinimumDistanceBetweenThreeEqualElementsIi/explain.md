## Problem

https://leetcode.com/problems/minimum-distance-between-three-equal-elements-ii/description/

Given an integer array `nums`, find 3 distinct indices (i, j, k) where `nums[i] == nums[j] == nums[k]` (a "good tuple").

The distance of a good tuple is: `abs(i - j) + abs(j - k) + abs(k - i)`

**Return the minimum possible distance of a good tuple, or -1 if no good tuples exist.**

**Constraints:**
- 1 <= n == nums.length <= 10^5
- 1 <= nums[i] <= n

**Examples:**
- Input: [1,2,1,1,3] → Output: 6 (tuple (0,2,3), distance = 2+1+3 = 6)
- Input: [1,1,2,3,2,1,2] → Output: 8 (tuple (2,4,6), distance = 2+2+4 = 8)
- Input: [1] → Output: -1 (no good tuples)

## Observations

1. **Distance Formula Simplification**: When we have three sorted indices a < b < c, the distance simplifies:
   - `abs(a - b) + abs(b - c) + abs(c - a) = (b - a) + (c - b) + (c - a) = 2(c - a)`
   - So we need to minimize (c - a), the gap between the leftmost and rightmost index

2. **Grouping by Value**: Group all indices by their values. Only values appearing at least 3 times can form good tuples.

3. **Optimal Window**: To minimize (c - a), we should check consecutive indices in the sorted array of indices for each value. Any non-consecutive selection would have a larger gap.

4. **Key Insight**: For each value with at least 3 indices, we iterate through all consecutive 3-index windows [arr[i-2], arr[i-1], arr[i]] and calculate the distance as `(arr[i] - arr[i-2]) * 2`.

5. **Time Complexity**: O(n) to group indices + O(n) to check all windows = O(n)
   **Space Complexity**: O(n) for the hashmap

## Solution

### Approach

1. Create a hashmap where each key is a value from `nums` and each value is an array of all indices where that value appears.

2. For each value that appears at least 3 times:
   - Iterate through windows of 3 consecutive indices
   - Calculate the distance as `(arr[i] - arr[i-2]) * 2` (where arr[i-2] and arr[i] are the leftmost and rightmost indices)
   - Track the minimum distance

3. Return the minimum distance found, or -1 if no good tuples exist.

### Code

```python
class Solution:
    def minimumDistance(self, nums: List[int]) -> int:
        # Group all indices by their values
        map_idx = {}  # val -> array of indices
        for i, val in enumerate(nums):
            if val not in map_idx:
                map_idx[val] = []
            map_idx[val].append(i)
        
        res = float('inf')
        
        # For each value with at least 3 occurrences
        for val, arr in map_idx.items():
            n = len(arr)
            if n < 3:
                continue
            
            # Check all consecutive 3-index windows
            # Distance formula: 2 * (rightmost - leftmost)
            for i in range(2, n):
                res = min(res, (arr[i] - arr[i - 2]) * 2)
        
        return -1 if res == float('inf') else res
```

### Example Walkthrough

**Example 1: nums = [1,2,1,1,3]**
- map_idx = {1: [0, 2, 3], 2: [1], 3: [4]}
- For value 1 with indices [0, 2, 3]:
  - Window at i=2: distance = (3 - 0) * 2 = 6 ✓
- Result: 6

**Example 2: nums = [1,1,2,3,2,1,2]**
- map_idx = {1: [0, 1, 5], 2: [2, 4, 6], 3: [3]}
- For value 1 with indices [0, 1, 5]:
  - Window at i=2: distance = (5 - 0) * 2 = 10
- For value 2 with indices [2, 4, 6]:
  - Window at i=2: distance = (6 - 2) * 2 = 8 ✓
- Result: 8

# Tags

- Hashmap / Dictionary
- Enumeration
- Math (Distance Optimization)
- Greedy (Consecutive Selection)
- Array

