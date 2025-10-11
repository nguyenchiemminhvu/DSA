## Problem

https://leetcode.com/problems/invert-binary-tree/description/

```
Given the root of a binary tree, invert the tree, and return its root.

Example 1:

Input: root = [4,2,7,1,3,6,9]
Output: [4,7,2,9,6,3,1]

Example 2:

Input: root = [2,1,3]
Output: [2,3,1]

Example 3:

Input: root = []
Output: []

Constraints:

The number of nodes in the tree is in the range [0, 100].
-100 <= Node.val <= 100
```

## Observations

1. **Problem Understanding**: We need to invert/mirror a binary tree horizontally - every left child becomes a right child and vice versa.

2. **Visual Representation**: 
   ```
   Original:     Inverted:
       4             4
     /   \         /   \
    2     7       7     2
   / \   / \     / \   / \
  1   3 6   9   9   6 3   1
   ```

3. **Key Insight**: For each node, we need to swap its left and right subtrees recursively.

4. **Base Case**: If the current node is `None` (empty tree), return `None`.

5. **Recursive Structure**: 
   - Create a new node with the same value
   - Recursively invert the left subtree and assign it to the right
   - Recursively invert the right subtree and assign it to the left

6. **Time Complexity**: O(n) where n is the number of nodes, as we visit each node exactly once.

7. **Space Complexity**: O(h) where h is the height of the tree due to recursion stack. In the worst case (skewed tree), h = n, so O(n). In the best case (balanced tree), h = log(n), so O(log n).

## Solution

1. **Helper Function**: `build_invert_tree` creates a new inverted tree rather than modifying the original tree in-place.

2. **Base Case**: When `root` is `None`, return `None` (empty subtree).

3. **Node Creation**: Create a new `TreeNode` with the same value as the current node.

4. **Recursive Inversion**: 
   - The right child of the new node gets the inverted left subtree of the original
   - The left child of the new node gets the inverted right subtree of the original

5. **Return**: The newly created inverted node is returned.

## Tags

binary tree