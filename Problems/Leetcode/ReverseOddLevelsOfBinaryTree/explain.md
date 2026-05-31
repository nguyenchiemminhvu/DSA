## Problem

https://leetcode.com/problems/reverse-odd-levels-of-binary-tree/description/

Given the `root` of a **perfect** binary tree, reverse the node values at each **odd** level of the tree. Return the root of the reversed tree.

- Level 0 is the root. Odd levels are 1, 3, 5, …
- Only values are swapped — the tree structure stays the same.

**Examples:**
- `[2,3,5,8,13,21,34]` → `[2,5,3,8,13,21,34]` (level 1: `3,5` → `5,3`)
- `[0,1,2,0,0,0,0,1,1,1,1,2,2,2,2]` → `[0,2,1,0,0,0,0,2,2,2,2,1,1,1,1]` (levels 1 and 3 reversed)

**Constraints:** up to 2¹⁴ nodes, perfect binary tree.

---

## Observations

1. **Perfect binary tree symmetry.** Because the tree is perfect, every level is completely filled and the tree is mirror-symmetric in structure. This means every node at position `i` from the left at a given level has a unique mirror partner at position `i` from the right.

2. **Only values change, not structure.** Reversing node values at a level is equivalent to swapping the value of the `i`-th node from the left with the `i`-th node from the right, for all `i`.

3. **Symmetric traversal using two pointers.** Instead of collecting all nodes of a level and reversing the array, we can exploit the symmetry: walk a `left` pointer inward from the leftmost subtree and a `right` pointer inward from the rightmost subtree simultaneously. At an odd level, swap their values. Then recurse into their children in a mirrored fashion.

4. **DFS with mirror pairs.** Starting from `(root.left, root.right)` at level 1:
   - `left.left` mirrors `right.right` (outer children).
   - `left.right` mirrors `right.left` (inner children).
   Recursing on both pairs covers every mirror pair in the tree exactly once.

5. **Base case.** When `left` or `right` is `None`, we have reached beyond the leaves — stop.

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
    def reverseOddLevels(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        def dfs(left: Optional[TreeNode], right: Optional[TreeNode], level: int):
            if not left:
                return right
            if not right:
                return left

            if level & 1:
                left.val, right.val = right.val, left.val

            dfs(left.left, right.right, level + 1)
            dfs(left.right, right.left, level + 1)

        dfs(root.left, root.right, 1)
        return root
```

**How it works, step by step:**

1. `dfs(left, right, level)` is called with a **mirror pair** — two nodes that are reflections of each other across the vertical axis of the tree, currently at depth `level`.

2. **Odd level → swap values.** `level & 1` is `1` when `level` is odd. We swap `left.val` and `right.val` in place. Since the tree is perfect and we cover all mirror pairs, this achieves a full reversal of the level.

3. **Recurse on outer children:** `dfs(left.left, right.right, level + 1)` — the leftmost descendant of `left` mirrors the rightmost descendant of `right`.

4. **Recurse on inner children:** `dfs(left.right, right.left, level + 1)` — the inner children are each other's mirrors.

5. **Why this reverses the level:** At an odd level with `2^k` nodes, the mirror pairs are `(node[0], node[2^k - 1])`, `(node[1], node[2^k - 2])`, … Swapping each pair is exactly a reversal of the array. The DFS naturally enumerates all such pairs.

**Complexity:**
- **Time:** O(n) — every node is visited exactly once.
- **Space:** O(log n) — recursion depth equals the height of the perfect binary tree.
