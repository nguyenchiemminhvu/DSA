## Problem

https://leetcode.com/problems/maximum-difference-between-node-and-ancestor/description/

Given the root of a binary tree, find the **maximum value** `v` for which there exist **different nodes** `a` and `b` where `v = |a.val - b.val|` and `a` is an **ancestor** of `b`.

A node `a` is an ancestor of `b` if either: any child of `a` is equal to `b`, or any child of `a` is an ancestor of `b`.

**Example 1:**
```
Input: root = [8,3,10,1,6,null,14,null,null,4,7,13]
Output: 7
Explanation:
|8 - 3| = 5
|3 - 7| = 4
|8 - 1| = 7   <-- maximum
|10 - 13| = 3
```

**Example 2:**
```
Input: root = [1,null,2,null,0,3]
Output: 3
```

**Constraints:**
- The number of nodes in the tree is in the range `[2, 5000]`.
- `0 <= Node.val <= 10^5`

---

## Observations

1. **Ancestor-descendant relationship**: For any node `a` and its descendant `b`, the difference `|a.val - b.val|` is maximized when `b.val` is either the **minimum** or the **maximum** value in the subtree rooted at `a`.

2. **Bottom-up insight**: If we know the minimum and maximum values among all nodes in a subtree, we can compute the maximum difference between the subtree root (an ancestor) and any node below it in O(1). Then we propagate the min/max upward.

3. **Why track min and max per subtree?**
   - The largest `|ancestor - descendant|` difference is always achieved by comparing an ancestor against either the smallest or the largest value in its subtree.
   - So for each node, we only need to know the range `[min, max]` of its subtree to evaluate all relevant ancestor-descendant pairs.

4. **Base case**: An empty subtree (null node) returns `(+∞, -∞)` — sentinel values that are safely ignored when computing min/max or differences.

---

## Solution Explanation

We use a **post-order DFS** traversal. At each node, we:

1. **Recurse** into the left and right subtrees to get their `(min, max)` ranges.
2. **Update the global result** by comparing the current node's value against the min and max of each child subtree:
   ```
   res = max(res,
             |node.val - min_left|,
             |node.val - max_left|,
             |node.val - min_right|,
             |node.val - max_right|)
   ```
   This covers every ancestor-descendant pair where the current node is the ancestor.
3. **Propagate upward** the combined `(min, max)` of the current subtree (including the current node itself), so that higher ancestors can also use it.

### Why this is correct

- Every ancestor-descendant pair `(a, b)` will be evaluated exactly once — when `a` is the current node being processed and `b` is somewhere in its left or right subtree.
- By carrying the subtree min/max upward, we ensure no pair is missed.

### Complexity

| | |
|---|---|
| **Time** | O(n) — each node is visited once |
| **Space** | O(h) — recursion stack, where h is the tree height (O(log n) balanced, O(n) worst case) |

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
    def maxAncestorDiff(self, root: Optional[TreeNode]) -> int:
        res = 0
        def dfs(root):
            nonlocal res
            if not root:
                return (float('inf'), float('-inf'))  # min, max sentinels

            mi_left, ma_left = dfs(root.left)
            mi_right, ma_right = dfs(root.right)

            # Current node is the ancestor; compare against subtree min/max
            res = max(
                res,
                abs(root.val - mi_left)  if mi_left  != float('inf')  else 0,
                abs(root.val - ma_left)  if ma_left  != float('-inf') else 0,
                abs(root.val - mi_right) if mi_right != float('inf')  else 0,
                abs(root.val - ma_right) if ma_right != float('-inf') else 0
            )

            # Propagate the full range of this subtree upward
            mi = min(mi_left, mi_right, root.val)
            ma = max(ma_left, ma_right, root.val)
            return (mi, ma)

        dfs(root)
        return res
```

### Walkthrough on Example 1: `[8,3,10,1,6,null,14,null,null,4,7,13]`

```
         8
        / \
       3   10
      / \    \
     1   6    14
        / \   /
       4   7 13
```

- `dfs(1)` → `(1, 1)`
- `dfs(4)` → `(4, 4)`, `dfs(7)` → `(7, 7)`
- `dfs(6)`: compare `|6-4|=2`, `|6-7|=1`; returns `(4, 7)`
- `dfs(3)`: compare `|3-1|=2`, `|3-4|=1`, `|3-7|=4`; returns `(1, 7)`
- `dfs(13)` → `(13, 13)`, `dfs(14)`: compare `|14-13|=1`; returns `(13, 14)`
- `dfs(10)`: compare `|10-13|=3`, `|10-14|=4`; returns `(10, 14)`
- `dfs(8)`: compare `|8-1|=7` ✓, `|8-7|=1`, `|8-10|=2`, `|8-14|=6`; **res = 7**

Final answer: **7**
