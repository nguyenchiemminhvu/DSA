## Problem

https://leetcode.com/problems/construct-binary-tree-from-preorder-and-postorder-traversal/description/

Given two integer arrays `preorder` and `postorder` representing the preorder and postorder traversals of a binary tree of distinct values, reconstruct and return the binary tree. If multiple answers exist, return any valid one.

---

## Observations

1. **Root identification**: In a preorder traversal, the **first element** is always the root. In a postorder traversal, the **last element** is always the root.

2. **Left subtree root**: In preorder, the element immediately after the root (`preorder[pre_left + 1]`) is the root of the **left subtree** (if it exists).

3. **Subtree size from postorder**: Since all values are distinct, we can find the left subtree root value in the `postorder` array. Its position in `postorder` tells us how many nodes are in the left subtree. If the left subtree root is at index `next_post_left` in `postorder`, then the left subtree contains `next_post_left - post_left + 1` nodes.

4. **Recursive decomposition**: Once we know the size of the left subtree, we can precisely split both `preorder` and `postorder` into left and right subtree segments, and recurse.

5. **Base cases**:
   - If the range is empty (`pre_left > pre_right`), return `None`.
   - If the range has exactly one element, return a leaf node with that value.

---

## Solution Explanation

The algorithm uses a recursive helper `build_tree(pre_left, pre_right, post_left, post_right)` that operates on index ranges of both arrays simultaneously.

**Step-by-step for each recursive call:**

```
preorder:  [root | left subtree | right subtree]
postorder: [left subtree | right subtree | root]
```

1. **Create root** from `preorder[pre_left]`.
2. **Identify left subtree root** as `preorder[pre_left + 1]` (the very next element in preorder).
3. **Locate it in postorder** to find `next_post_left` — its index in `postorder`.
4. **Compute left subtree size**: `size_left = next_post_left - post_left + 1`.
5. **Recurse left**: preorder range `[pre_left+1, pre_left+size_left]`, postorder range `[post_left, next_post_left]`.
6. **Recurse right**: preorder range `[pre_left+size_left+1, pre_right]`, postorder range `[next_post_left+1, post_right-1]`.

**Example walkthrough** with `preorder = [1,2,4,5,3,6,7]`, `postorder = [4,5,2,6,7,3,1]`:

```
call: pre=[1,2,4,5,3,6,7], post=[4,5,2,6,7,3,1]
  root = 1
  left subtree root = 2  →  found at index 2 in postorder
  left subtree size = 2 - 0 + 1 = 3
  left:  pre=[2,4,5],   post=[4,5,2]
  right: pre=[3,6,7],   post=[6,7,3]

  call: pre=[2,4,5], post=[4,5,2]
    root = 2
    left subtree root = 4  →  found at index 0 in postorder
    left subtree size = 0 - 0 + 1 = 1
    left:  pre=[4], post=[4]   →  leaf 4
    right: pre=[5], post=[5]   →  leaf 5

  call: pre=[3,6,7], post=[6,7,3]
    root = 3
    left subtree root = 6  →  found at index 0 in postorder segment
    left subtree size = 1
    left:  pre=[6], post=[6]   →  leaf 6
    right: pre=[7], post=[7]   →  leaf 7

Final tree:
        1
       / \
      2   3
     / \ / \
    4  5 6  7
```

**Result level-order**: `[1, 2, 3, 4, 5, 6, 7]` ✓

---

## Complexity

| | |
|---|---|
| **Time** | $O(n^2)$ — due to `list.index()` scan inside each recursive call. Can be reduced to $O(n)$ with a precomputed hashmap. |
| **Space** | $O(n)$ — recursion stack depth is $O(n)$ in the worst case (skewed tree). |

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
    def constructFromPrePost(self, preorder: List[int], postorder: List[int]) -> Optional[TreeNode]:
        def build_tree(pre_left, pre_right, post_left, post_right):
            if pre_left > pre_right or post_left > post_right:
                return None
            if pre_left == pre_right:
                return TreeNode(preorder[pre_left])
            
            root = TreeNode(preorder[pre_left])
            next_pre_left = pre_left + 1
            next_post_left = postorder.index(preorder[next_pre_left])

            size_next_post_left = next_post_left - post_left + 1
            size_next_post_right = post_right - 1 - next_post_left

            root.left = build_tree(next_pre_left, next_pre_left + size_next_post_left - 1, post_left, next_post_left)
            root.right = build_tree(next_pre_left + size_next_post_left, pre_right, next_post_left + 1, post_right - 1)

            return root
        
        return build_tree(0, len(preorder) - 1, 0, len(postorder) - 1)
```
