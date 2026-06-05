## Problem

https://leetcode.com/problems/cousins-in-binary-tree-ii/description/

Given the root of a binary tree, replace the value of each node with the **sum of all its cousins' values**.

Two nodes are **cousins** if they are at the same depth but have **different parents**.

Return the root of the modified tree.

---

## Observations

1. **Cousin sum formula**: For a node `X` at depth `d`, its cousins are every node at depth `d` *except* its own siblings (nodes sharing the same parent).  
   Therefore:
   $$\text{cousin\_sum}(X) = \text{total\_sum}(\text{depth } d) - \text{sibling\_sum}(X) - X.\text{val}$$
   Which simplifies to:
   $$\text{cousin\_sum}(X) = \text{total\_sum}(\text{depth } d) - \text{sum of all children of } X\text{'s parent}$$

2. **Root always becomes 0**: The root has no cousins (no other node at depth 0), so its new value is 0.

3. **Depth-1 nodes always become 0**: All children of the root are siblings of each other. Since cousins must have *different* parents, depth-1 nodes can only have siblings — never cousins. Their new value is 0.

4. **A parent controls its children's cousin sum**: When processing a parent node, we already know:
   - The total sum at the next depth level (precomputed).
   - The sum of this parent's own children (siblings of each other).
   
   So we can assign `total_sum_at_next_depth - sum_of_own_children` to each child in a single pass.

5. **Two-pass strategy**: A BFS pass first collects `sum[depth]` for every level. A DFS (or second BFS) pass then updates each node's children using the formula above.

---

## Solution Explanation

### Step 1 — BFS: collect level sums

Traverse the tree level by level. For each depth `d`, sum all node values at that depth and store them in `info[d]`.

```
info[0] = root.val
info[1] = sum of root's children
info[2] = sum of all grandchildren
...
```

### Step 2 — DFS: update children values

For each node `cur` at depth `d`, we know:
- `info[d+1]` = total sum of all nodes at depth `d+1`
- `sibling_sum` = `cur.left.val + cur.right.val` (children of the same parent are siblings)

Both children receive the same new value:
```
new_val = info[d+1] - sibling_sum
```

This is correct because cousins of `cur.left` (or `cur.right`) are every node at depth `d+1` **except** the children of `cur`.

### Step 3 — Fix the root

After the DFS, set `root.val = 0` (root has no cousins).

---

### Walkthrough — Example 1: `[5, 4, 9, 1, 10, null, 7]`

```
        5          depth 0  →  info[0] = 5
       / \
      4   9        depth 1  →  info[1] = 4 + 9 = 13
     / \    \
    1  10    7     depth 2  →  info[2] = 1 + 10 + 7 = 18
```

**DFS from root (depth 0):**
- `sibling_sum` = 4 + 9 = 13
- New value for node 4 and node 9: `info[1] - 13 = 13 - 13 = 0` ✓

**DFS from node 4 (depth 1):**
- `sibling_sum` = 1 + 10 = 11
- New value for node 1 and node 10: `info[2] - 11 = 18 - 11 = 7` ✓

**DFS from node 9 (depth 1):**
- `sibling_sum` = 7 (only right child)
- New value for node 7: `info[2] - 7 = 18 - 7 = 11` ✓

**Set root to 0.** Final tree: `[0, 0, 0, 7, 7, null, 11]` ✓

---

### Complexity

| | Complexity |
|---|---|
| **Time** | $O(N)$ — each node visited exactly twice (once in BFS, once in DFS) |
| **Space** | $O(N)$ — BFS queue + DFS call stack + `info` dictionary |

---

## Solution

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def replaceValueInTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        if not root:
            return None
        
        info = defaultdict(int)  # info[depth] -> sum of all nodes at that depth

        def bfs():
            q = deque([root])
            depth = -1
            while q:
                z = len(q)
                sum_row = 0
                depth += 1
                for _ in range(z):
                    cur = q.popleft()
                    sum_row += cur.val
                    if cur.left:
                        q.append(cur.left)
                    if cur.right:
                        q.append(cur.right)
                info[depth] = sum_row
        
        def dfs(root, depth):
            if not root:
                return
            
            if depth + 1 in info:
                sum_next_depth = info[depth + 1]
                # Sum of siblings (children of this parent)
                sum_this_parent = 0
                if root.left:
                    sum_this_parent += root.left.val
                if root.right:
                    sum_this_parent += root.right.val
                
                # Cousin sum = total at next depth - own siblings
                if root.left:
                    root.left.val = sum_next_depth - sum_this_parent
                if root.right:
                    root.right.val = sum_next_depth - sum_this_parent

            dfs(root.left, depth + 1)
            dfs(root.right, depth + 1)
        
        bfs()
        dfs(root, 0)
        root.val = 0  # root has no cousins
        return root
```
