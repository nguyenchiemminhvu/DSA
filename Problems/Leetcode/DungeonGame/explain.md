## Problem

https://leetcode.com/problems/dungeon-game/description/

The demons had captured the princess and imprisoned her in the bottom-right corner of a dungeon. The dungeon consists of m x n rooms laid out in a 2D grid. Our valiant knight was initially positioned in the top-left room and must fight his way through the dungeon to rescue the princess.

The knight has an initial health point represented by a positive integer. If at any point his health point drops to 0 or below, he dies immediately.

Some of the rooms are guarded by demons (represented by negative integers), so the knight loses health upon entering these rooms; other rooms are either empty (represented as 0) or contain magic orbs that increase the knight's health (represented by positive integers).

To reach the princess as quickly as possible, the knight decides to move only rightward or downward in each step.

**Return the knight's minimum initial health so that he can rescue the princess.**

Note that any room can contain threats or power-ups, even the first room the knight enters and the bottom-right room where the princess is imprisoned.

### Examples

**Example 1:**
```
Input: dungeon = [[-2,-3,3],[-5,-10,1],[10,30,-5]]
Output: 7
Explanation: The initial health of the knight must be at least 7 if he follows the optimal path: RIGHT → RIGHT → DOWN → DOWN.
```

**Example 2:**
```
Input: dungeon = [[0]]
Output: 1
```

### Constraints
- m == dungeon.length
- n == dungeon[i].length
- 1 <= m, n <= 200
- -1000 <= dungeon[i][j] <= 1000

## Observations

1. **Backward Thinking Requirement**: This problem requires working backwards from the destination to the start. We cannot simply calculate forward health, because we need to know what minimum health is required at each future position to determine the current requirement.

2. **Health Constraint**: The knight's health must always remain > 0. After entering a room with dungeon value `d`, if current health is `h`, the new health is `h + d`. We need `h + d > 0`, so `h > -d`.

3. **Minimum Health at Each Cell**: At any cell (r, c), the minimum health needed is determined by:
   - The dungeon value at that cell
   - The minimum health required to safely traverse from the next positions (down or right)
   - Choose the path that requires less health (min of down/right)

4. **Base Case**: At the princess's location (m-1, n-1), if the dungeon value is `d`, the knight needs at least `max(1, 1 - d)` health to survive that room and rescue the princess.

5. **Recurrence**: For cell (r, c) with dungeon value `d`, if `need` is the minimum health required after leaving this cell, then the health needed **before** entering is: `max(1, need - d)`. This ensures:
   - Health stays at least 1
   - After taking damage/healing `d`, health is at least `need`

6. **Out of Bounds**: If we try to go beyond grid boundaries, we return infinity (impossible) to force the knight to take valid paths.

## Solution

### Approach: Dynamic Programming (Memoization, Backward Traversal)

The key insight is to work **backwards** from the bottom-right corner to the top-left corner.

**State Definition**: `F(r, c)` = minimum health needed **before** entering cell (r, c) to survive and reach the princess.

**Recurrence**:
```
F(r, c) = max(1, need - dungeon[r][c])
where need = min(F(r+1, c), F(r, c+1))
```

**Base Cases**:
- If out of bounds: return infinity (invalid path)
- At destination (m-1, n-1): return `max(1, 1 - dungeon[r][c])`

**Why this works**:
- We choose the minimum of the two possible next positions
- At each cell, we calculate the minimum health required **before** entering
- The answer is `F(0, 0)`, the health needed at the starting position

### Code Walkthrough

```python
class Solution:
    def calculateMinimumHP(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        INF = float('inf')

        mem = {}
        def F(r: int, c: int) -> int:
            # Out of bounds - invalid path
            if r >= m or c >= n:
                return INF
            
            # Destination: need at least 1 health, minus any healing at this room
            if r == m - 1 and c == n - 1:
                return max(1, 1 - grid[r][c])
            
            # Memoization check
            if (r, c) in mem:
                return mem[(r, c)]
            
            # Get minimum health needed from next positions (down or right)
            need = min(F(r + 1, c), F(r, c + 1))
            
            # Calculate health needed before entering this cell
            # Must be at least 1, and after taking dungeon[r][c] damage/healing,
            # health should be >= need
            res = max(1, need - grid[r][c])

            mem[(r, c)] = res
            return res
        
        return F(0, 0)
```

**Example Trace** (dungeon = [[-2,-3,3],[-5,-10,1],[10,30,-5]]):
```
Starting from (2, 2) = -5:
  F(2, 2) = max(1, 1 - (-5)) = 6 (need 6 before entering, gain 5, end with 1)

For (2, 1) = 30:
  need = F(2, 2) = 6
  F(2, 1) = max(1, 6 - 30) = max(1, -24) = 1

For (2, 0) = 10:
  need = F(2, 1) = 1
  F(2, 0) = max(1, 1 - 10) = max(1, -9) = 1

For (1, 2) = 1:
  need = min(F(2, 2), INF) = 6
  F(1, 2) = max(1, 6 - 1) = 5

For (1, 1) = -10:
  need = min(F(2, 1), F(1, 2)) = min(1, 5) = 1
  F(1, 1) = max(1, 1 - (-10)) = 11

For (1, 0) = -5:
  need = min(F(2, 0), F(1, 1)) = min(1, 11) = 1
  F(1, 0) = max(1, 1 - (-5)) = 6

For (0, 2) = 3:
  need = F(1, 2) = 5
  F(0, 2) = max(1, 5 - 3) = 2

For (0, 1) = -3:
  need = min(F(1, 1), F(0, 2)) = min(11, 2) = 2
  F(0, 1) = max(1, 2 - (-3)) = 5

For (0, 0) = -2:
  need = min(F(1, 0), F(0, 1)) = min(6, 5) = 5
  F(0, 0) = max(1, 5 - (-2)) = 7
```

**Answer: 7** ✓

### Complexity Analysis

- **Time Complexity**: O(m × n) — Each cell is computed once, memoization prevents recomputation
- **Space Complexity**: O(m × n) — Memoization table stores results for all cells

# Tags

