## Problem

https://leetcode.com/problems/univalued-binary-tree/description/

```
A binary tree is uni-valued if every node in the tree has the same value.

Given the root of a binary tree, return true if the given tree is uni-valued, or false otherwise.

Example 1:

Input: root = [1,1,1,1,1,null,1]
Output: true

Example 2:

Input: root = [2,2,2,5,2]
Output: false

Constraints:

The number of nodes in the tree is in the range [1, 100].
0 <= Node.val < 100
```

## Observations

The definition of a uni-valued binary tree means that all nodes must have exactly the same val. If even one node differs, the result should be false.

The input is given as a binary tree, so traversal methods like DFS (depth-first search) or BFS (breadth-first search) can be used to check all nodes.

Since the number of nodes is small (maximum 100), performance is not a major concern — a simple recursive or iterative traversal will be efficient enough.

The root node’s value can be used as the reference value to compare against all other nodes in the tree.

Null children should be skipped during traversal; they do not affect the uni-valued property.

Edge case: If the tree has only one node, it is trivially uni-valued.

# Tags

binary tree