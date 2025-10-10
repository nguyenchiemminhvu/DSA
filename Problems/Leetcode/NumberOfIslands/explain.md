## Problem

https://leetcode.com/problems/number-of-islands/description/

```
Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.

An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example 1:

Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1

Example 2:

Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 300
grid[i][j] is '0' or '1'.
```

## Observations

1. **Problem Nature**: This is a classic connected components problem in a 2D grid graph where each cell is a node and adjacent '1' cells are connected.

2. **Island Definition**: An island consists of connected '1' cells (land) that are adjacent horizontally or vertically. Diagonal connections don't count.

3. **Graph Traversal**: We need to traverse each connected component of '1' cells exactly once to count islands. Both BFS and DFS work well for this.

4. **Visited Tracking**: We need to track visited cells to avoid counting the same island multiple times and prevent infinite loops.

5. **Boundary Conditions**: All edges are considered water, so we only need to check 4-directional neighbors (up, down, left, right).

6. **Time Complexity**: O(m × n) where m and n are grid dimensions, as we visit each cell at most twice (once in main loop, once in BFS).

7. **Space Complexity**: O(m × n) for the visited array, plus O(min(m,n)) for the BFS queue in worst case.

## Solution

### Approach: BFS (Breadth-First Search)

The solution uses BFS to explore each island completely before moving to the next one.

1. **Initialize**: Create a `visited` matrix to track processed cells and get grid dimensions.

2. **BFS Function**: 
   - Takes starting coordinates `(r, c)` of an unvisited land cell
   - Uses a `queue` to explore all connected land cells level by level
   - Marks each cell as visited before adding to queue to prevent revisits
   - Checks all 4 neighbors (`up`, `down`, `left`, `right`) for valid land cells

3. **Main Loop**: 
   - Iterate through every `cell` in the `grid`
   - When finding an unvisited land cell (`'1'`), start `BFS` from that cell
   - `BFS` will mark all cells belonging to this island as visited
   - Increment island counter after each `BFS` call

4. **Boundary Checking**: Ensures neighbors are within grid bounds before processing.

### Key Implementation Details:

- **Queue Operations**: `Q.pop(0)` removes from front (`FIFO`), `Q.append()` adds to back
- **Visited Strategy**: Mark cells as visited when adding to queue, not when processing
- **Direction Array**: Uses explicit neighbor coordinates for cleaner `4-directional` movement
- **Early Termination**: `BFS` stops when queue is empty (all connected land found)

### Time & Space Complexity:
- **Time**: `O(m × n)` - each cell visited at most twice
- **Space**: `O(m × n)` - visited array + `O(min(m,n))` queue space

## Tags

array, graph, bfs