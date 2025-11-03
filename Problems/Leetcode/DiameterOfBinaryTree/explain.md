## Problem

https://leetcode.com/problems/diameter-of-binary-tree/

```
Given the root of a binary tree, return the length of the diameter of the tree.

The diameter of a binary tree is the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.

The length of a path between two nodes is represented by the number of edges between them.

Example 1:

Input: root = [1,2,3,4,5]
Output: 3
Explanation: 3 is the length of the path [4,2,1,3] or [5,2,1,3].

Example 2:

Input: root = [1,2]
Output: 1

Constraints:

The number of nodes in the tree is in the range [1, 104].
-100 <= Node.val <= 100
```

## Observations

1. **Understanding Diameter**: The diameter is the longest path between any two nodes in the tree, measured by the number of edges (not nodes).

2. **Path Characteristics**: The longest path can:
   - Pass through the root
   - Be entirely in the left subtree
   - Be entirely in the right subtree
   - Pass through any internal node

3. **Key Insight**: For any node, the longest path passing through it has length = `height(left_subtree) + height(right_subtree)`

4. **Height vs Diameter**: 
   - Height of a node = maximum depth from that node to any leaf
   - For a null node, height = 0
   - For a leaf node, height = 1

5. **Brute Force Approach**: Check every node as a potential "center" of the longest path and compute the diameter passing through it.

## Solution

The provided solution uses a two-pass approach with memoization:

### Algorithm Steps:

1. **First Pass - Compute Heights**: 
   - Use DFS to compute and memoize the height of every node
   - Height of null = 0
   - Height of node = 1 + max(height(left), height(right))

2. **Second Pass - Find Maximum Diameter**:
   - Use preorder traversal to visit each node
   - For each node, calculate potential diameter = height(left) + height(right)
   - Track the maximum diameter found

### Code Analysis:

```python
def height(root: Optional[TreeNode]) -> int:
    if root in self.memo:
        return self.memo[root]  # Use memoized result
    h = 0 if root == None else 1 + max(height(root.left), height(root.right))
    self.memo[root] = h  # Store result for future use
    return h
```

**Height function**: Recursively calculates height with memoization to avoid recomputation.

```python
def preorder(root: Optional[TreeNode]) -> None:
    if root == None:
        return
    self.res = max(self.res, self.memo[root.left] + self.memo[root.right])
    preorder(root.left)
    preorder(root.right)
```

**Preorder traversal**: For each node, calculates the diameter passing through it and updates the global maximum.

### Time & Space Complexity:
- **Time**: O(n) - Each node visited twice (once for height, once for diameter)
- **Space**: O(n) - Memoization storage + recursion stack

### Alternative One-Pass Solution:
A more efficient approach would compute the diameter during the height calculation:

```python
def diameterOfBinaryTree(self, root: Optional[TreeNode]) -> int:
    self.diameter = 0
    
    def height(node):
        if not node:
            return 0
        
        left_height = height(node.left)
        right_height = height(node.right)
        
        # Update diameter at current node
        self.diameter = max(self.diameter, left_height + right_height)
        
        return 1 + max(left_height, right_height)
    
    height(root)
    return self.diameter
```

This eliminates the need for memoization and reduces to a single pass.

# Tags

`Binary Tree` `DFS` `Recursion` `Tree Traversal` `Memoization` `Height Calculation`

