## Problem

https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/description/
https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/description/

```
Given a binary search tree (BST), find the lowest common ancestor (LCA) node of two given nodes in the BST.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”

Example 1:

Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
Output: 6
Explanation: The LCA of nodes 2 and 8 is 6.

Example 2:

Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
Output: 2
Explanation: The LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to the LCA definition.

Example 3:

Input: root = [2,1], p = 2, q = 1
Output: 2

Constraints:

The number of nodes in the tree is in the range [2, 105].
-109 <= Node.val <= 109
All Node.val are unique.
p != q
p and q will exist in the BST.
```

## Observations

1. **Path to Target Approach**: To find the LCA, we can build the path from root to each target node (`p` and `q`), then find where these paths diverge.

2. **Common Prefix**: The LCA will be the last common node in both paths before they start to differ.

3. **Path Building Strategy**: 
- Use DFS to traverse the tree and build the path to each target
- Maintain a path list that gets modified as we traverse
- When target is found, the path contains all ancestors from root to target
- Use backtracking (pop) when a subtree doesn't contain the target

1. **Path Comparison**: Once we have both paths, we compare them element by element until we find the first difference. The node just before the difference is our LCA.

## Solution

**Approach: Path Building + Common Prefix**

1. **Path Building Function**: `build_path(root, target, path)`
- Performs DFS to find the target node
- Maintains a path list during traversal
- Returns `True` if target is found in the current subtree
- Uses backtracking: removes current node from path if target not found in subtree

1. **Main Logic**:
- Build path from root to node `p`
- Build path from root to node `q`
- Compare both paths to find the longest common prefix
- Return the last common node in the prefix

**Time Complexity**: `O(n)` where n is the number of nodes
- We may visit each node once while building each path
- Path comparison takes `O(h)` where h is the height of the tree

**Space Complexity**: `O(h)` where h is the height of the tree
- Space for the recursion stack: `O(h)`
- Space for storing paths: `O(h)` each
- Total: `O(h)`

## Tags

binary tree, DFS