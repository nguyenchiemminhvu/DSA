## Problem

https://leetcode.com/problems/best-sightseeing-pair/description/

Given an array of positive integers `values` where `values[i]` represents the beauty of the i-th sightseeing spot.

Two sightseeing spots `i` and `j` with `i < j` have a score equal to: `values[i] + values[j] + i - j`

Find the maximum score for any valid pair of sightseeing spots.

**Example:**
- Input: `values = [8,1,5,2,6]`
- Output: `16` (indices 0 and 2: 8 + 5 + 0 - 2 = 11... or indices 0 and 4: 8 + 6 + 0 - 4 = 10... wait, let me recalculate)
  - Pair (0, 4): 8 + 6 + 0 - 4 = 10
  - Pair (0, 2): 8 + 5 + 0 - 2 = 11
  - Pair (1, 2): 1 + 5 + 1 - 2 = 5
  - Pair (0, 1): 8 + 1 + 0 - 1 = 8
  - Actually maximum might be different. Maximum is 11.

## Observations

1. **Brute Force Insight**: The naive approach would be to check all pairs (i, j) where i < j and compute `values[i] + values[j] + i - j` for each. This is O(n²) time complexity.

2. **Rearranging the Formula**: The key observation is rearranging the score formula:
   - Score = `values[i] + i + values[j] - j`
   - For each index j, we want to find the index i (where i < j) that maximizes `values[i] + i`
   - Then we add `values[j] - j` to this maximum

3. **Greedy Optimization**: As we iterate through the array from left to right:
   - For each position j, we only need to know the maximum value of `values[i] + i` for all i < j
   - We maintain this maximum as we go, avoiding the need to check all previous indices
   - This reduces complexity to O(n) time and O(1) space

4. **State Transition**: At each index i:
   - If we've already processed at least one element (i > 0), we can compute the score using the best previous index
   - We then update our running maximum of `values[i] + i` for potential future use

## Solution

**Algorithm: Single Pass with Running Maximum**

```python
class Solution:
    def maxScoreSightseeingPair(self, values: List[int]) -> int:
        n = len(values)
        
        res = 0                           # Track the maximum score found
        max_val_i = 0                     # Track max(values[i] + i) for all i seen so far
        
        for i in range(n):
            if i > 0:
                # For position i (as j), calculate score using best previous index
                # score = values[i] + i + (max_val_i - i)
                # But max_val_i was values[prev_i] + prev_i
                # So: values[prev_i] + prev_i + values[i] - i
                res = max(res, max_val_i + values[i] - i)
            
            # Update the running maximum for the (values[k] + k) component
            max_val_i = max(max_val_i, values[i] + i)
        
        return res
```

**Step-by-Step Execution (values = [8,1,5,2,6]):**

| i | values[i] | values[i]+i | max_val_i (before) | res (if i>0) | max_val_i (after) |
|---|-----------|-------------|-------------------|--------------|------------------|
| 0 | 8         | 8           | 0                 | -            | 8                |
| 1 | 1         | 2           | 8                 | 8+1-1=8      | 8                |
| 2 | 5         | 7           | 8                 | 8+5-2=11     | 8                |
| 3 | 2         | 5           | 8                 | 8+2-3=7      | 8                |
| 4 | 6         | 10          | 8                 | 8+6-4=10     | 10               |

**Result: 11**

**Time Complexity:** O(n) - single pass through the array

**Space Complexity:** O(1) - only using constant extra space

## Tags

- Arrays
- Greedy
- Single Pass
- Optimization from O(n²) to O(n)

