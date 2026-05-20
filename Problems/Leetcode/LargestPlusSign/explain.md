## Problem

https://leetcode.com/problems/largest-plus-sign/description

Given an integer `n`, you have an `n x n` binary grid filled with all 1's except for some indices given in the array `mines`. For each mine at position `mines[i] = [xi, yi]`, the cell `grid[xi][yi]` is set to 0.

Return the **order** of the largest axis-aligned plus sign of 1's contained in the grid. If there is none, return 0.

An axis-aligned plus sign of 1's of order `k` has:
- A center at some position `grid[r][c] == 1`
- Four arms of length `k - 1` extending up, down, left, and right
- All cells in these four arms must be 1's

**Note:** There can be 0's or 1's beyond the arms of the plus sign; only the relevant area is checked.

### Examples

**Example 1:**
```
Input: n = 5, mines = [[4,2]]
Output: 2
```
The largest plus sign has order 2.

**Example 2:**
```
Input: n = 1, mines = [[0,0]]
Output: 0
```
No plus sign exists, so return 0.

### Constraints
- `1 <= n <= 500`
- `1 <= mines.length <= 5000`
- `0 <= xi, yi < n`
- All pairs `(xi, yi)` are unique

## Observations

1. **Order Definition:** For a plus sign of order `k` centered at `(r, c)`:
   - The center must be 1
   - All cells at distance 1, 2, ..., k-1 in all four directions must be 1
   - The limiting factor is the **minimum distance** to a mine or boundary in any of the four directions

2. **Key Insight:** For each cell `(r, c)`, we need to find:
   - Distance to the nearest mine going **left** from `(r, c)`
   - Distance to the nearest mine going **right** from `(r, c)`
   - Distance to the nearest mine going **up** from `(r, c)`
   - Distance to the nearest mine going **down** from `(r, c)`
   
   The order of the plus sign centered at `(r, c)` is the **minimum** of these four distances.

3. **Dynamic Programming Approach:** We can compute these distances efficiently by:
   - Making 4 passes through the grid (left→right, right→left, top→bottom, bottom→top)
   - Each pass counts consecutive non-mine cells
   - Storing the minimum value from all four directions in a DP table

4. **Why Minimum Matters:** A plus sign is only as large as its shortest arm. If a cell has 3 consecutive 1's in one direction but only 1 in another, the maximum plus sign order centered there is 2 (distance to the closest mine).

## Solution

### Approach: Multi-directional Dynamic Programming

The solution uses four passes through the grid to compute the maximum arm length in each direction:

```python
class Solution:
    def orderOfLargestPlusSign(self, n: int, mines: List[List[int]]) -> int:
        mine_set = set()
        for r, c in mines:
            mine_set.add((r, c))
        
        # Initialize DP table with large values
        dp = [[n] * n for _ in range(n)]

        # Pass 1: Left to Right (count consecutive 1's from left)
        for r in range(n):
            count = 0
            for c in range(n):
                if (r, c) in mine_set:
                    count = 0
                else:
                    count += 1
                dp[r][c] = min(dp[r][c], count)
            
            # Pass 2: Right to Left (count consecutive 1's from right)
            count = 0
            for c in range(n - 1, -1, -1):
                if (r, c) in mine_set:
                    count = 0
                else:
                    count += 1
                dp[r][c] = min(dp[r][c], count)
        
        # Pass 3: Top to Bottom (count consecutive 1's from top)
        for c in range(n):
            count = 0
            for r in range(n):
                if (r, c) in mine_set:
                    count = 0
                else:
                    count += 1
                dp[r][c] = min(dp[r][c], count)
            
            # Pass 4: Bottom to Top (count consecutive 1's from bottom)
            count = 0
            for r in range(n - 1, -1, -1):
                if (r, c) in mine_set:
                    count = 0
                else:
                    count += 1
                dp[r][c] = min(dp[r][c], count)
        
        # Find the maximum order among all cells
        res = 0
        for row in dp:
            res = max(res, max(row))
        return res
```

### How It Works

1. **Initialize:** Create a set of mine positions for O(1) lookup, and a DP table filled with `n` (upper bound).

2. **Four Directional Passes:**
   - **Left Pass:** For each row, count consecutive non-mine cells from left. `dp[r][c]` becomes the minimum of its current value and the count of 1's to the left.
   - **Right Pass:** For each row (right to left), count consecutive non-mine cells. Update `dp[r][c]` with the minimum.
   - **Up Pass:** For each column, count consecutive non-mine cells from top. Update `dp[r][c]`.
   - **Down Pass:** For each column (bottom to top), count consecutive non-mine cells. Update `dp[r][c]`.

3. **Result:** After all four passes, `dp[r][c]` contains the order of the largest plus sign centered at `(r, c)`. Return the maximum value in the table.

### Example Walkthrough

For `n = 5, mines = [[4,2]]`:

Initial grid (0-indexed):
```
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
1 1 0 1 1
```

After left-right passes on row 3 (no mines):
- Left count: [1, 2, 3, 4, 5]
- Right count: [5, 4, 3, 2, 1]
- Min: [1, 2, 3, 2, 1]

After up-down passes on column 2 (mine at (4,2)):
- Up count: [1, 2, 3, 4, 0]
- Down count: [4, 3, 2, 1, 0]
- Final: [1, 2, 2, 1, 0]

The maximum value is **2**, which represents a plus sign of order 2.

### Complexity Analysis

- **Time Complexity:** O(n²) - We make 4 passes through the n×n grid
- **Space Complexity:** O(n²) - For the DP table and O(m) for the mine set, where m ≤ 5000

### Key Advantages

1. **Efficient:** Linear number of passes through the grid
2. **Clear Logic:** Each pass has a single, understandable purpose
3. **Minimal Storage:** Uses only one DP table
4. **Optimal:** Achieves best possible time complexity for this problem

# Tags

Dynamic Programming, Grid, Two Pointers, Optimization

