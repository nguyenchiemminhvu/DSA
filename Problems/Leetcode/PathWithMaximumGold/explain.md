## Problem

https://leetcode.com/problems/path-with-maximum-gold/description/

In a gold mine grid of size `m x n`, each cell contains an integer representing the amount of gold in that cell, or 0 if it is empty.

Return the maximum amount of gold you can collect under the following conditions:

1. Every time you are located in a cell, you will collect all the gold in that cell.
2. From your position, you can walk one step to the left, right, up, or down.
3. You can't visit the same cell more than once.
4. Never visit a cell with 0 gold.
5. You can start and stop collecting gold from any position in the grid that has some gold.

### Examples

**Example 1:**
```
Input: grid = [[0,6,0],[5,8,7],[0,9,0]]
Output: 24
Explanation:
[[0,6,0],
 [5,8,7],
 [0,9,0]]
Path to get the maximum gold: 9 -> 8 -> 7
```

**Example 2:**
```
Input: grid = [[1,0,7],[2,0,6],[3,4,5],[0,3,0],[9,0,20]]
Output: 28
Explanation:
[[1,0,7],
 [2,0,6],
 [3,4,5],
 [0,3,0],
 [9,0,20]]
Path to get the maximum gold: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7
```

### Constraints

- `m == grid.length`
- `n == grid[i].length`
- `1 <= m, n <= 15`
- `0 <= grid[i][j] <= 100`
- There are at most 25 cells containing gold

## Observations

1. **Pathfinding Problem**: This is a pathfinding problem where we need to explore all possible paths starting from each non-zero cell.

2. **No Dynamic Programming**: Unlike typical pathfinding problems, we cannot use dynamic programming because:
   - The optimal path through a cell depends on which cells we've already visited
   - The same cell can be part of different optimal paths with different visiting histories

3. **Backtracking Required**: We need to explore all possible paths and backtrack when we reach a dead end, keeping track of visited cells.

4. **Small Grid Size**: The constraint `1 <= m, n <= 15` and at most 25 cells with gold makes an exhaustive search feasible.

5. **Multiple Starting Points**: We must try starting from every cell that contains gold, as the optimal path could start from any position.

6. **Path Termination**: A path ends when:
   - We go out of bounds
   - We encounter a cell with 0 gold
   - All adjacent cells have been visited

## Solution

### Algorithm: Depth-First Search (DFS) with Backtracking

The solution uses DFS with backtracking to explore all possible paths from each starting position.

**Key Components:**

1. **Visited Set**: Tracks cells in the current path to prevent revisiting
2. **DFS Function**: Recursively explores all four directions from current cell
3. **Path Options**: Collects gold amounts from all complete paths
4. **Try All Starts**: Iterates through every cell as a potential starting point

### Step-by-Step Process

1. **Initialize Variables**:
   - `max_gold`: Stores the maximum gold collected across all paths
   - `m, n`: Grid dimensions
   - `visited`: Set to track visited cells in current path
   - `opts`: List to store gold amounts from completed paths

2. **DFS Function**:
   ```python
   def dfs(r: int, c: int, cur_gold: int) -> None:
   ```
   - **Parameters**:
     - `r, c`: Current row and column position
     - `cur_gold`: Gold collected so far in this path
   
   - **Base Cases**:
     - Out of bounds → record current gold and return
     - Cell has 0 gold → record current gold and return
   
   - **Recursive Case**:
     - For each of 4 directions (up, down, left, right):
       - If not visited, mark as visited
       - Recursively explore with updated gold count
       - Backtrack by removing from visited set

3. **Main Loop**:
   - Try starting from each cell `(i, j)`
   - Reset `visited` and `opts` for each starting position
   - Mark starting cell as visited
   - Run DFS from that position
   - Update `max_gold` with the best result from this start

### Code Walkthrough

```python
class Solution:
    def getMaximumGold(self, grid: List[List[int]]) -> int:
        max_gold = 0
        m = len(grid)
        n = len(grid[0])
        visited = set()
        opts = []
        
        def dfs(r: int, c: int, cur_gold: int) -> None:
            # Base case 1: Out of bounds
            if r < 0 or r >= m or c < 0 or c >= n:
                opts.append(cur_gold)
                return
            
            # Base case 2: Cell has no gold
            if grid[r][c] == 0:
                opts.append(cur_gold)
                return
            
            # Explore all 4 directions
            for nr, nc in [(r+1, c), (r-1, c), (r, c+1), (r, c-1)]:
                # Convert 2D coordinates to 1D index for visited set
                cell_id = nr * n + nc
                if cell_id not in visited:
                    visited.add(cell_id)
                    # Add current cell's gold before moving
                    dfs(nr, nc, cur_gold + grid[r][c])
                    visited.remove(cell_id)  # Backtrack

        # Try starting from each cell
        for i in range(m):
            for j in range(n):
                visited = set()
                opts = []
                visited.add(i * n + j)  # Mark starting cell as visited
                dfs(i, j, 0)
                if opts:
                    max_gold = max(max_gold, max(opts))
        
        return max_gold
```

### Important Implementation Details

1. **Cell ID Encoding**: Uses `row * n + col` to convert 2D coordinates to unique 1D identifier
   - Efficient for visited set operations
   - Avoids storing tuples

2. **Backtracking**: After exploring a direction, removes the cell from visited set
   - Allows the cell to be part of different paths from different starting points

3. **Gold Collection Timing**: Adds `grid[r][c]` when moving TO the next cell
   - This is why we start DFS with `cur_gold = 0`
   - Accumulates gold as we build the path

4. **Options List**: Collects all path results to find maximum
   - Alternative: Could track max during DFS (more efficient)

### Complexity Analysis

**Time Complexity**: O(m × n × 4^k) where k is the maximum path length
- We try m × n starting positions
- From each position, we explore up to 4 directions
- Maximum path length is at most 25 (cells with gold)
- **Practical**: Much better due to pruning (0 cells, visited cells, boundaries)

**Space Complexity**: O(k) where k is the maximum path length
- Recursion stack depth: O(k)
- Visited set size: O(k)
- Options list: O(number of complete paths from a start)

### Alternative Optimizations

1. **Track Max During DFS**: Instead of collecting all options, update max directly:
   ```python
   nonlocal max_gold
   max_gold = max(max_gold, cur_gold)
   ```

2. **Skip Zero Cells as Starting Points**: Only start DFS from cells with gold > 0

3. **Early Termination**: If we find a path with all 25 gold cells, we can stop

## Key Takeaways

- **Backtracking** is essential for exploring all possible paths
- **Exhaustive search** is feasible with small input constraints
- **State management** (visited set) prevents cycles
- **Multiple starting points** required because optimal path location is unknown

# Tags

`Backtracking` `Depth-First Search` `Matrix` `Grid` `Pathfinding`

