## Problem

https://leetcode.com/problems/max-increase-to-keep-city-skyline/description/

There is a city composed of `n x n` blocks, where each block contains a single building shaped like a vertical square prism. You are given a 0-indexed `n x n` integer matrix `grid` where `grid[r][c]` represents the height of the building at row `r` and column `c`.

A city's **skyline** is the outer contour formed by all the buildings when viewing the city from a distance. The skyline from each cardinal direction (north, east, south, and west) may be different.

You are allowed to increase the height of any number of buildings by any amount. However, **increasing the height of a building must not affect the city's skyline from any cardinal direction**.

Return the **maximum total sum** that the heights of the buildings can be increased by without changing the skyline from any direction.

**Example 1:**
```
Input: grid = [[3,0,8,4],[2,4,5,7],[9,2,6,3],[0,3,1,0]]
Output: 35
```
The grid after optimal increases:
```
gridNew = [[8,4,8,7],
           [7,4,7,7],
           [9,4,8,7],
           [3,3,3,3]]
```

**Example 2:**
```
Input: grid = [[0,0,0],[0,0,0],[0,0,0]]
Output: 0
```
Increasing any building height will change the skyline.

**Constraints:**
- `n == grid.length == grid[r].length`
- `2 <= n <= 50`
- `0 <= grid[r][c] <= 100`

---

## Observations

1. **Skyline definition:** The skyline from the **north or south** (looking along columns) is determined by the **maximum height in each column**. The skyline from the **east or west** (looking along rows) is determined by the **maximum height in each row**.

2. **What constrains a building's height?** Building at `(r, c)` contributes to both the skyline of row `r` and column `c`. To preserve both skylines, the new height of `grid[r][c]` cannot exceed:
   - `max_rows[r]`: the current maximum height in row `r`
   - `max_cols[c]`: the current maximum height in column `c`

   Therefore, the maximum allowed height for building `(r, c)` is:
   $$\text{new\_height}(r, c) = \min(\text{max\_rows}[r],\ \text{max\_cols}[c])$$

3. **Greedy insight:** Since we want to maximize the total increase, we should raise every building as high as possible — up to `min(max_rows[r], max_cols[c])`. This is always safe because:
   - It never exceeds the row maximum, so the east/west skyline is unchanged.
   - It never exceeds the column maximum, so the north/south skyline is unchanged.

4. **Increase per building:** The gain for building `(r, c)` is:
   $$\min(\text{max\_rows}[r],\ \text{max\_cols}[c]) - \text{grid}[r][c]$$
   This is always `>= 0` because the current height can never exceed either maximum.

---

## Solution

```python
class Solution:
    def maxIncreaseKeepingSkyline(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])

        # Step 1: Compute the skyline for each row and each column
        max_rows = [0] * m
        max_cols = [0] * n
        for r in range(m):
            for c in range(n):
                max_rows[r] = max(max_rows[r], grid[r][c])
                max_cols[c] = max(max_cols[c], grid[r][c])

        # Step 2: For each building, increase height to the maximum allowed
        # without violating either the row or column skyline
        res = 0
        for r in range(m):
            for c in range(n):
                res += min(max_rows[r], max_cols[c]) - grid[r][c]

        return res
```

**Step-by-step walkthrough (Example 1):**

```
grid = [[3,0,8,4],
        [2,4,5,7],
        [9,2,6,3],
        [0,3,1,0]]

max_rows = [8, 7, 9, 3]   (max of each row)
max_cols = [9, 4, 8, 7]   (max of each column)

For each cell, gain = min(max_rows[r], max_cols[c]) - grid[r][c]:

Row 0: min(8,9)-3 + min(8,4)-0 + min(8,8)-8 + min(8,7)-4 = 5+4+0+3 = 12
Row 1: min(7,9)-2 + min(7,4)-4 + min(7,8)-5 + min(7,7)-7 = 5+0+2+0 = 7
Row 2: min(9,9)-9 + min(9,4)-2 + min(9,8)-6 + min(9,7)-3 = 0+2+2+4 = 8
Row 3: min(3,9)-0 + min(3,4)-3 + min(3,8)-1 + min(3,7)-0 = 3+0+2+3 = 8

Total = 12 + 7 + 8 + 8 = 35 ✓
```

**Complexity:**
- **Time:** $O(n^2)$ — two passes over the grid
- **Space:** $O(n)$ — for `max_rows` and `max_cols` arrays
