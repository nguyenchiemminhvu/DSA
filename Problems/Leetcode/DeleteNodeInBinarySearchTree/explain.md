## Problem

https://leetcode.com/problems/delete-node-in-a-bst/description/

```
Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.

Basically, the deletion can be divided into two stages:

Search for a node to remove.
If the node is found, delete the node.

Example 1:

Input: root = [5,3,6,2,4,null,7], key = 3
Output: [5,4,6,2,null,null,7]
Explanation: Given key to delete is 3. So we find the node with value 3 and delete it.
One valid answer is [5,4,6,2,null,null,7], shown in the above BST.
Please notice that another valid answer is [5,2,6,null,4,null,7] and it's also accepted.

Example 2:

Input: root = [5,3,6,2,4,null,7], key = 0
Output: [5,3,6,2,4,null,7]
Explanation: The tree does not contain a node with value = 0.

Example 3:

Input: root = [], key = 0
Output: []

Constraints:

The number of nodes in the tree is in the range [0, 104].
-105 <= Node.val <= 105
Each node has a unique value.
root is a valid binary search tree.
-105 <= key <= 105

Follow up: Could you solve it with time complexity O(height of tree)?
```

## Observations

1. **BST Property**: In a Binary Search Tree, for any node, all values in the left subtree are smaller and all values in the right subtree are larger. This property must be maintained after deletion.

2. **Three Cases for Deletion**:
   - **Leaf node (no children)**: Simply remove the node by returning `None`
   - **Node with one child**: Replace the node with its child
   - **Node with two children**: Find the inorder successor (smallest node in right subtree) or predecessor, replace the node's value, then delete the successor/predecessor

3. **Inorder Successor**: The smallest node in the right subtree is the next larger value in the BST. It's guaranteed to have at most one child (right child only).

4. **Recursive Approach**: The problem naturally fits a recursive solution where we traverse the tree following BST properties and handle each case appropriately.

5. **Time Complexity**: O(h) where h is the height of the tree, as we traverse from root to the target node in the worst case.

## Solution

**1. Base Case**
```python
if root == None:
    return None
```
If we reach a null node, the key doesn't exist in the tree, so return `None`.

**2. Search Phase**
```python
if key < root.val:
    root.left = internal_delete(root.left, key)
elif key > root.val:
    root.right = internal_delete(root.right, key)
```
Using BST property to navigate: go left if key is smaller, right if larger.

**3. Deletion Cases (when `key == root.val`)**

- **Leaf Node**: `if root.left == None and root.right == None: return None`
  - Simply remove the node by returning `None`

- **One Child**: 
  - `if root.left == None: return root.right` (only right child)
  - `if root.right == None: return root.left` (only left child)
  - Replace the node with its only child

- **Two Children**:
  ```python
  successor = root.right
  while successor.left != None:
      successor = successor.left
  root.val = successor.val
  root.right = internal_delete(root.right, successor.val)
  ```
  - Find inorder successor (leftmost node in right subtree)
  - Replace current node's value with successor's value
  - Recursively delete the successor from right subtree

**Key Insights:**
- The inorder successor is guaranteed to have at most one child (right child only)
- By replacing the value and deleting the successor, we maintain BST properties
- The recursive calls ensure proper tree reconstruction from bottom-up

**Time Complexity**: O(h) where h is tree height
**Space Complexity**: O(h) due to recursion stack

## Tags

binary search tree, dfs