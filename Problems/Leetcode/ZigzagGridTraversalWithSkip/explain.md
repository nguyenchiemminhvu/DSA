## Problem

https://leetcode.com/problems/zigzag-grid-traversal-with-skip/description/

```
You are given an m x n 2D array grid of positive integers.

Your task is to traverse grid in a zigzag pattern while skipping every alternate cell.

Zigzag pattern traversal is defined as following the below actions:
- Start at the top-left cell (0, 0).
- Move right within a row until the end of the row is reached.
- Drop down to the next row, then traverse left until the beginning of the row is reached.
- Continue alternating between right and left traversal until every row has been traversed.

Note that you must skip every alternate cell during the traversal.

Return an array of integers result containing, in order, the value of the cells visited during the zigzag traversal with skips.

Examples:
- grid = [[1,2],[3,4]] → Output: [1,4]
- grid = [[2,1],[2,1],[2,1]] → Output: [2,1,2]  
- grid = [[1,2,3],[4,5,6],[7,8,9]] → Output: [1,3,5,7,9]

Constraints:
- 2 <= n == grid.length <= 50
- 2 <= m == grid[i].length <= 50
- 1 <= grid[i][j] <= 2500
```

## Observations

1. **Zigzag Pattern**: We traverse rows alternately - left-to-right on even rows, right-to-left on odd rows.

2. **Skipping Pattern**: We skip every alternate cell, which means we take cells at indices 0, 2, 4, ... in the traversal order.

3. **Key Insight**: The starting offset for each row alternates between 0 and 1:
   - Row 0 (even): Start at offset 0, take indices [0, 2, 4, ...]
   - Row 1 (odd): Start at offset 1, take indices [1, 3, 5, ...], then reverse for right-to-left
   - Row 2 (even): Start at offset 0 again
   - And so on...

4. **Direction Handling**: For odd rows, we collect values normally but reverse them at the end to simulate right-to-left traversal.

## Solution

1. **Initialize**: `offset = 0` to track which starting position to use for each row.

2. **For each row**:
   - Collect values starting from `offset` with step 2 (skip alternate cells)
   - If `offset` is odd (meaning we're on an odd-numbered row), reverse the collected values to simulate right-to-left traversal
   - Add all collected values to result
   - Toggle offset between 0 and 1 for next row

3. **Time Complexity**: O(m×n) where we visit each cell once
4. **Space Complexity**: O(1) extra space (not counting output array)

The key insight is that instead of actually traversing right-to-left, we can collect values left-to-right and then reverse them when needed, which simplifies the implementation significantly.

# Tags
Array, Matrix, Simulation, Traversal

