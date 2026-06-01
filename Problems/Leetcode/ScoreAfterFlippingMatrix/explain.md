```markdown
## Problem

https://leetcode.com/problems/score-after-flipping-matrix/description/

You are given an `m x n` binary matrix `grid`.

A **move** consists of choosing any row or column and **toggling** each value in that row or column (changing all `0`s to `1`s, and all `1`s to `0`s).

Every row of the matrix is interpreted as a **binary number**, and the **score** of the matrix is the sum of these numbers.

Return the **highest possible score** after making any number of moves (including zero moves).

**Example 1:**
```
Input: grid = [[0,0,1,1],[1,0,1,0],[1,1,0,0]]
Output: 39
Explanation: 0b1111 + 0b1001 + 0b1111 = 15 + 9 + 15 = 39
```

**Example 2:**
```
Input: grid = [[0]]
Output: 1
```

**Constraints:**
- `m == grid.length`
- `n == grid[i].length`
- `1 <= m, n <= 20`
- `grid[i][j]` is either `0` or `1`

---

## Observations

1. **The most significant bit dominates.**  
   In an `n`-bit binary number, the leftmost bit (bit `n-1`) has value `2^(n-1)`, which is greater than the sum of all remaining bits combined (`2^(n-1) - 1`). Therefore, having the first column all `1`s is **always** optimal, no matter what it costs to the other columns.

2. **Row flips should be applied first.**  
   If `grid[r][0] == 0`, flip the entire row `r`. This guarantees every row starts with `1` (MSB = 1). Since we are free to flip any row independently, we can always achieve this without conflicting with other rows.

3. **Column flips should be applied after row fixes.**  
   Once all first-column values are `1`, we examine each remaining column `c` (from index `1` to `n-1`). For column `c`, if the number of `0`s is greater than the number of `1`s (i.e., `count_0 > m / 2`), flipping that column increases the total score. We apply the flip only when it helps.

4. **Order matters: rows before columns.**  
   Row flips affect all bits in a row uniformly, while column flips affect all rows for a given bit position. Fixing rows first (to set MSB = 1) and then greedily optimizing columns is the correct order. Doing it in reverse would not guarantee the MSB is maximized.

5. **No conflict between column decisions.**  
   Each column flip decision is independent — flipping column `c` does not affect the `1`-count in any other column. So we can decide each column greedily in isolation.

---

## Solution Explanation

```python
class Solution:
    def matrixScore(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])

        # Step 1: Flip all rows where the first element is 0.
        # This ensures every row's MSB = 1, which maximizes the contribution
        # of the most significant bit for every row.
        for r in range(m):
            if grid[r][0] == 0:
                for j in range(n):
                    grid[r][j] = (grid[r][j] + 1) % 2

        # Step 2: Build running bitmasks for each row starting from MSB = 1.
        masks = [0] * m
        for i in range(m):
            if grid[i][0] == 1:
                masks[i] = 1  # All rows now start with 1

        # Step 3: For each remaining column, decide whether to flip it.
        # Flip if doing so results in more 1s than 0s in that column.
        for c in range(1, n):
            count_0 = 0
            orig = []
            flip = []
            for r in range(m):
                if grid[r][c] == 0:
                    count_0 += 1
                orig.append(grid[r][c])
                flip.append((grid[r][c] + 1) % 2)

            # Use the flipped version only if it gives more 1s
            update = orig
            if count_0 > (m // 2):
                update = flip

            # Shift each row's bitmask left and append the chosen bit
            for i in range(m):
                masks[i] = (masks[i] << 1) | update[i]

        # Step 4: Sum all row values (each mask now encodes the full row as an integer)
        return sum(masks)
```

**Walkthrough on Example 1:** `grid = [[0,0,1,1],[1,0,1,0],[1,1,0,0]]`

- **Row flips:** Row 0 starts with `0` → flip → `[1,1,0,0]`  
  Grid becomes: `[[1,1,0,0],[1,0,1,0],[1,1,0,0]]`

- **Column 1:** values = `[1,0,1]` → `count_0 = 1`, not majority → keep as-is  
- **Column 2:** values = `[0,1,0]` → `count_0 = 2 > 3//2 = 1` → flip → `[1,0,1]`  
- **Column 3:** values = `[0,0,0]` → `count_0 = 3 > 1` → flip → `[1,1,1]`

- **Final rows:** `[1,1,1,1]`, `[1,0,0,1]`, `[1,1,1,1]` = `15 + 9 + 15 = 39` ✓

**Time Complexity:** $O(m \times n)$ — each cell is visited a constant number of times.  
**Space Complexity:** $O(m)$ — for the `masks` array storing one integer per row.
```
