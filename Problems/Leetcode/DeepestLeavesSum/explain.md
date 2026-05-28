## Problem

https://leetcode.com/problems/deepest-leaves-sum/description/

Given the `root` of a binary tree, return the sum of values of its deepest leaves.

**Example 1:**
```
Input: root = [1,2,3,4,5,null,6,7,null,null,null,null,8]
Output: 15
```

**Example 2:**
```
Input: root = [6,7,8,2,7,1,3,9,null,1,4,null,null,null,5]
Output: 19
```

**Constraints:**
- The number of nodes in the tree is in the range `[1, 10^4]`.
- `1 <= Node.val <= 100`

---

## Observations

- We need the sum of **only** the leaf nodes at the **maximum depth**.
- A leaf node is a node with no children.
- The deepest leaves all live on the same level (the last level of the tree).
- BFS (level-order traversal) naturally processes nodes level by level, so the last full batch of nodes we process is exactly the deepest level.
- We don't need to track depth explicitly — just keep overwriting the current level's values; whatever remains after the loop is the deepest level.

---

## Solution Explanation

**Approach: BFS (Level-Order Traversal)**

Use a queue to traverse the tree level by level. For each level, collect all node values into `row`. After processing a level, replace `last_row` with `row`. When the queue is empty, `last_row` holds the values of the deepest level (which are all leaves by definition, since no node at the last level has children). Return their sum.

```python
from collections import deque
from typing import Optional

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def deepestLeavesSum(self, root: Optional[TreeNode]) -> int:
        if not root:
            return 0

        last_row = []
        q = deque([root])
        while q:
            n = len(q)
            row = []
            for _ in range(n):
                cur = q.popleft()
                row.append(cur.val)
                if cur.left:
                    q.append(cur.left)
                if cur.right:
                    q.append(cur.right)
            last_row = row   # overwrite; after the loop this is the deepest level

        return sum(last_row)
```

**Step-by-step walkthrough (Example 1):**
```
Tree:          1
              / \
             2   3
            / \    \
           4   5    6
          /          \
         7             8

Level 0: [1]
Level 1: [2, 3]
Level 2: [4, 5, 6]
Level 3: [7, 8]   ← deepest level, last_row = [7, 8]

sum([7, 8]) = 15  ✓
```

**Complexity:**
| | |
|---|---|
| Time | $O(n)$ — every node is visited exactly once |
| Space | $O(w)$ — where $w$ is the maximum width of the tree (queue size at any level) |
