## Problem

https://leetcode.com/problems/construct-quad-tree/description/

Given an **n × n matrix grid** of 0's and 1's only, we need to represent the grid with a **Quad-Tree** data structure.

### Quad-Tree Definition
- **val**: True if the node represents a grid of all 1's, False if all 0's
- **isLeaf**: True if the node is a leaf node (uniform grid), False if it has four children

### Construction Rules
1. If all values in the current grid are the same (all 0's or all 1's):
   - Set `isLeaf = True`
   - Set `val` to the grid value
   - Set all four children to `None`
   
2. If the grid has different values:
   - Set `isLeaf = False`
   - Divide the grid into 4 equal sub-grids (top-left, top-right, bottom-left, bottom-right)
   - Recursively construct Quad-Tree for each sub-grid

### Constraints
- n == grid.length == grid[i].length
- n == 2^x where 0 ≤ x ≤ 6 (grid size is always a power of 2)

### Examples

**Example 1:**
```
Input: grid = [[0,1],[1,0]]
Output: [[0,1],[1,0],[1,1],[1,1],[1,0]]
Explanation: All values are different, so the root is not a leaf.
The root divides into 4 sub-grids, each containing a single uniform value (leaf nodes).
```

**Example 2:**
```
Input: grid = [[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,1,1,1,1],[1,1,1,1,1,1,1,1],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0]]
Output: [[0,1],[1,1],[0,1],[1,1],[1,0],null,null,null,null,[1,0],[1,0],[1,1],[1,1]]
```

## Observations

1. **Uniform Grid Check**: The key to solving this problem is efficiently checking if all elements in a sub-grid are the same value.

2. **Divide and Conquer**: This is a classic divide-and-conquer problem where we recursively divide the grid into 4 quadrants until we find uniform sub-grids.

3. **Power of 2 Guarantee**: Since n is always a power of 2, we can always divide grids evenly into 4 equal sub-grids without any remainder.

4. **Recursive Structure**: The Quad-Tree structure naturally maps to recursion:
   - Base case: All elements are the same → create a leaf node
   - Recursive case: Elements are different → divide and recurse on 4 quadrants

5. **Space Optimization**: For larger uniform regions, the Quad-Tree can significantly compress the representation compared to storing the full grid. For example, a 1024×1024 grid of all 1's becomes a single leaf node.

## Solution

### Approach: Recursive Divide-and-Conquer

**Time Complexity**: O(n² × log n) in the worst case
- For each possible sub-grid (at all recursion levels), we check if all elements are the same: O(n²)
- There are O(log n) levels of recursion for an n×n grid

**Space Complexity**: O(n²) for the recursion call stack (maximum depth O(log n), but at each level we might process all n² elements)

### Implementation

```python
# Definition for a QuadTree node.
class Node:
    def __init__(self, val, isLeaf, topLeft, topRight, bottomLeft, bottomRight):
        self.val = val
        self.isLeaf = isLeaf
        self.topLeft = topLeft
        self.topRight = topRight
        self.bottomLeft = bottomLeft
        self.bottomRight = bottomRight

class Solution:
    def construct(self, grid: List[List[int]]) -> 'Node':
        def solve(r, c, n):
            """
            Recursively construct Quad-Tree for a sub-grid.
            
            Args:
                r: starting row index
                c: starting column index
                n: size of the current sub-grid (n x n)
            
            Returns:
                Root node of the Quad-Tree for this sub-grid
            """
            # Check if all elements in the current square are the same
            is_same = True
            first_val = grid[r][c]
            for i in range(r, r + n):
                for j in range(c, c + n):
                    if grid[i][j] != first_val:
                        is_same = False
                        break
                if not is_same:
                    break
            
            if is_same:
                # Base case: all elements are the same
                # Create a leaf node with val = (1 if first_val == 1 else 0)
                return Node(first_val == 1, True, None, None, None, None)
            
            # Recursive case: elements are different
            # Divide into 4 equal quadrants
            half = n // 2
            top_left = solve(r, c, half)
            top_right = solve(r, c + half, half)
            bottom_left = solve(r + half, c, half)
            bottom_right = solve(r + half, c + half, half)
            
            # Create an internal node (not a leaf)
            # val can be any value (True or False) when isLeaf is False
            return Node(True, False, top_left, top_right, bottom_left, bottom_right)
        
        return solve(0, 0, len(grid))
```

### Step-by-Step Example

For `grid = [[0,1],[1,0]]`:

1. **Call `solve(0, 0, 2)`**
   - Check if all 4 elements are the same
   - grid[0][0]=0, grid[0][1]=1 → different values
   - `is_same = False`

2. **Divide into 4 quadrants** (each 1×1):
   - **Top-left `solve(0, 0, 1)`**: grid[0][0] = 0 → leaf node with val=False, isLeaf=True
   - **Top-right `solve(0, 1, 1)`**: grid[0][1] = 1 → leaf node with val=True, isLeaf=True
   - **Bottom-left `solve(1, 0, 1)`**: grid[1][0] = 1 → leaf node with val=True, isLeaf=True
   - **Bottom-right `solve(1, 1, 1)`**: grid[1][1] = 0 → leaf node with val=False, isLeaf=True

3. **Create root node**
   - isLeaf = False
   - Connect 4 child leaf nodes

### Key Points

- **Uniform Check Optimization**: We iterate through the sub-grid once to verify all elements are the same
- **Early Termination**: Once we find a mismatch (`is_same = False`), we break out of the loops
- **Leaf Node Creation**: Only when all elements match do we create a leaf node
- **Internal Node Creation**: When elements differ, we create an internal node and recursively process 4 sub-grids
- **Indexing**: Be careful with row/column indices when dividing:
  - Top-left: `(r, c)`
  - Top-right: `(r, c + half)`
  - Bottom-left: `(r + half, c)`
  - Bottom-right: `(r + half, c + half)`

# Tags

#divide-and-conquer #tree #quadtree #recursion #matrix

