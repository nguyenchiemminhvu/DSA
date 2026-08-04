## Problem

https://leetcode.com/problems/print-binary-tree

Given the root of a binary tree, construct a 0-indexed `m x n` string matrix that represents a formatted layout of the tree:
- `m = height + 1` rows
- `n = 2^(height+1) - 1` columns
- The root is placed at `res[0][(n-1)/2]`
- For each node at `res[r][c]`, its left child goes to `res[r+1][c - 2^(height-r-1)]` and right child to `res[r+1][c + 2^(height-r-1)]`
- Empty cells contain `""`

---

## Observations

1. **Grid dimensions are determined by tree height.**  
   If `height = h`, then `rows = h + 1` and `cols = 2^(h+1) - 1`. A tree of height 0 (single node) produces a 1×1 grid.

2. **The root always lands in the exact horizontal center.**  
   `mid_col = (cols - 1) / 2`. Because `cols` is always odd (power of 2 minus 1), this is an integer.

3. **Each level halves the horizontal gap.**  
   At row `r`, the shift between a parent and its child is `2^(h - r - 1)`. At the deepest level the shift becomes `2^0 = 1`, so adjacent leaf slots are exactly 1 column apart — no overlap, no wasted space.

4. **The placement rule is recursive by nature.**  
   Knowing a node's `(row, col)` fully determines where both children go, making DFS a natural fit.

5. **Height calculation must handle `None`.**  
   Return `-1` for a null node so a single-node tree has height 0.

---

## Solution Explanation

**Step 1 – Compute tree height**

```
height(node):
    if node is None: return -1
    return 1 + max(height(left), height(right))
```

A standard post-order recursion. `h = height(root)`.

**Step 2 – Allocate the grid**

```
rows = h + 1
cols = 2^(h+1) - 1
grid = [[''] * cols for _ in range(rows)]
```

All cells start as empty strings.

**Step 3 – DFS placement**

```
dfs(node, r, c):
    grid[r][c] = str(node.val)
    shift = 2^(h - r - 1)
    dfs(node.left,  r+1, c - shift)
    dfs(node.right, r+1, c + shift)
```

- At each call we know the exact cell `(r, c)` for the current node.
- `shift` shrinks by half at every level, maintaining the symmetric spacing.
- The root is seeded with `dfs(root, 0, (cols-1)//2)`.

**Complexity**
- Time: `O(N)` for the DFS + `O(m × n)` to initialise the grid = `O(2^h)` dominated by grid size.
- Space: `O(2^h)` for the grid; `O(h)` recursion stack.

---

## Code

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def printTree(self, root: Optional[TreeNode]) -> List[List[str]]:
        def height(root):
            if not root:
                return -1
            return 1 + max(height(root.left), height(root.right))
        
        h = height(root)
        row = h + 1
        col = 2 ** (h + 1) - 1
        grid = [[''] * col for _ in range(row)]

        mid_col = (col - 1) // 2

        def dfs(root, r, c):
            if not root:
                return
            
            grid[r][c] = str(root.val)
            shift = 2 ** (h - r - 1)

            dfs(root.left,  r + 1, c - shift)
            dfs(root.right, r + 1, c + shift)
        
        dfs(root, 0, mid_col)

        return grid
```
