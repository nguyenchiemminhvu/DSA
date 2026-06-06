## Problem

https://leetcode.com/problems/recover-a-tree-from-preorder-traversal/description/

We run a preorder depth-first search (DFS) on the `root` of a binary tree.

At each node in the traversal, we output `D` dashes (where `D` is the depth of that node), then we output the value of the node. The depth of the root is `0`, and the depth of each immediate child is `D + 1`.

If a node has only one child, that child is guaranteed to be the **left child**.

Given the output string `traversal`, recover the tree and return its root.

**Example 1:**
```
Input:  "1-2--3--4-5--6--7"
Output: [1,2,5,3,4,6,7]
```

**Example 2:**
```
Input:  "1-2--3---4-5--6---7"
Output: [1,2,5,3,null,6,null,4,null,7]
```

**Example 3:**
```
Input:  "1-401--349---90--88"
Output: [1,401,null,349,88,90]
```

**Constraints:**
- Number of nodes in `[1, 1000]`
- Node values in `[1, 10^9]`

---

## Solution

### Intuition

The traversal string encodes a preorder DFS where each node is prefixed by a number of dashes equal to its depth. To reconstruct the tree we need to answer one question for each parsed node: *who is its parent?*

Because it is a preorder traversal, a node at depth `D` must be the child of the **most recently seen node at depth `D - 1`**. A stack naturally tracks exactly this: after processing a node at depth `D`, the stack holds the ancestor chain from the root down to that node.

### Algorithm

1. **Parse** dashes to get the depth `D`, then parse digits to get the value `val`.
2. **Trim the stack** to length `D` so `st[-1]` is the parent at depth `D - 1`.
3. **Attach** the new node as the left child of the parent if the left slot is empty, otherwise as the right child.
4. **Push** the new node onto the stack and repeat.

### Walkthrough — `"1-2--3--4-5--6--7"`

| Step | Parsed  | Stack after trim | Attach as       | Stack after push        |
|------|---------|------------------|-----------------|-------------------------|
| 1    | D=0, 1  | []               | root            | [1]                     |
| 2    | D=1, 2  | [1]              | 1.left          | [1, 2]                  |
| 3    | D=2, 3  | [1, 2]           | 2.left          | [1, 2, 3]               |
| 4    | D=2, 4  | [1, 2]           | 2.right         | [1, 2, 4]               |
| 5    | D=1, 5  | [1]              | 1.right         | [1, 5]                  |
| 6    | D=2, 6  | [1, 5]           | 5.left          | [1, 5, 6]               |
| 7    | D=2, 7  | [1, 5]           | 5.right         | [1, 5, 7]               |

Result tree: `[1, 2, 5, 3, 4, 6, 7]` ✓

### Code

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def recoverFromPreorder(self, traversal: str) -> Optional[TreeNode]:
        n = len(traversal)
        i = 0

        root = None
        st = []
        while i < n:
            # Count dashes → depth
            depth = 0
            while i < n and traversal[i] == '-':
                depth += 1
                i += 1

            # Parse the node value (may be multi-digit)
            val = 0
            while i < n and traversal[i].isdigit():
                val = val * 10 + int(traversal[i])
                i += 1

            node = TreeNode(val)

            if depth == 0:
                root = node  # this is the root

            # Pop nodes deeper than current depth so st[-1] is the parent
            while len(st) > depth:
                st.pop()

            # Attach to parent
            if st:
                parent = st[-1]
                if not parent.left:
                    parent.left = node
                else:
                    parent.right = node

            st.append(node)

        return root
```

### Complexity

| | |
|---|---|
| **Time** | $O(n)$ — single left-to-right pass over the string; each node is pushed and popped at most once |
| **Space** | $O(h)$ — stack depth equals the tree height $h$; worst case $O(n)$ for a skewed tree |
