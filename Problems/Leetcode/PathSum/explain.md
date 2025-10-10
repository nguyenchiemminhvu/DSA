## Problem

https://leetcode.com/problems/path-sum/description/

```
Given the root of a binary tree and an integer targetSum, return true if the tree has a root-to-leaf path such that adding up all the values along the path equals targetSum.

A leaf is a node with no children.

Example 1:

Input: root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
Output: true
Explanation: The root-to-leaf path with the target sum is shown.

Example 2:

Input: root = [1,2,3], targetSum = 5
Output: false
Explanation: There are two root-to-leaf paths in the tree:
(1 --> 2): The sum is 3.
(1 --> 3): The sum is 4.
There is no root-to-leaf path with sum = 5.

Example 3:

Input: root = [], targetSum = 0
Output: false
Explanation: Since the tree is empty, there are no root-to-leaf paths.

Constraints:

The number of nodes in the tree is in the range [0, 5000].
-1000 <= Node.val <= 1000
-1000 <= targetSum <= 1000
```

## Observations

1. **Root-to-leaf path requirement**: We need to find a path from the root node to any leaf node (a node with no children), not just any path in the tree.

2. **Sum calculation**: The path sum is the total of all node values encountered from root to leaf, including both the root and leaf nodes.

3. **Empty tree edge case**: An empty tree (`root = None`) should return False, even if targetSum is `0`, because there are no paths to evaluate.

4. **Single node case**: A tree with only one node (`root`) is considered a leaf, so we check if `root.val` equals targetSum.

5. **Recursive nature**: The problem has optimal substructure - if we know the remaining sum needed after visiting the current node, we can recursively check left and right subtrees.

6. **Constraints consideration**: With node values and targetSum in range `[-1000, 1000]` and up to `5000` nodes, we need to handle negative values and potential overflow (though not a concern in Python).

## Solution

The implementation uses a **recursive depth-first search (DFS) approach with cumulative sum modification**:

### Key Strategy:
- **In-place cumulative sum**: Instead of passing the remaining target sum down the recursion, the solution modifies each node's value to store the cumulative sum from root to that node. 
- **Early termination**: The recursion stops when reaching a leaf node and checks if the cumulative sum equals the target.

### Algorithm Breakdown:

1. **Base case - Empty tree**: If `root` is None, return False (no path exists).

2. **Base case - Leaf node**: If current node has no children, check if its value (now containing cumulative sum) equals targetSum.

3. **Recursive case**: 
- Add current node's value to both children (if they exist), creating cumulative sums
- Recursively check left and right subtrees
- Return True if either subtree contains a valid path (using OR operator)

### Time Complexity: O(n)
- Each node is visited exactly once
- In worst case, we traverse all nodes in the tree

### Space Complexity: O(h) 
- Where h is the height of the tree (recursion stack depth)
- `O(log n)` for balanced trees, `O(n)` for skewed trees

### Note on Implementation:
This solution modifies the original tree structure by updating node values. If preserving the original tree is required, an alternative approach would pass the running sum as a parameter instead of modifying node values.

## Tags

binary tree