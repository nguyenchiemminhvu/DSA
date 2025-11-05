## Problem

https://leetcode.com/problems/increasing-order-search-tree/

```
Given the root of a binary search tree, rearrange the tree in in-order so that the leftmost node in the tree is now the root of the tree, and every node has no left child and only one right child.

Example 1:

Input: root = [5,3,6,2,4,null,8,1,null,null,null,7,9]
Output: [1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]

Example 2:

Input: root = [5,1,7]
Output: [1,null,5,null,7]

Constraints:

The number of nodes in the given tree will be in the range [1, 100].
0 <= Node.val <= 1000
```

## Observations

1. **Problem Understanding**: We need to rearrange a binary search tree so that:
   - The leftmost node becomes the new root
   - Every node has no left child and only one right child
   - The result maintains the in-order traversal order (which is sorted for BST)

2. **Key Insight**: Since we want nodes in increasing order and BST in-order traversal gives us sorted values, we can:
   - Perform in-order traversal to get sorted values
   - Build a new tree where each node only has a right child

3. **Input/Output Pattern**:
   - Input: A valid BST with any structure
   - Output: A "right-skewed" tree maintaining the sorted order
   - The transformation essentially "flattens" the BST into a linked list-like structure

4. **Edge Cases**:
   - Single node tree → returns the same node
   - Already right-skewed tree → structure remains the same
   - Empty tree → returns null

## Solution

### Approach: In-order Traversal + Reconstruction

**Algorithm**:
1. **Extract Values**: Use in-order traversal to collect all node values in sorted order
2. **Build New Tree**: Create a new tree structure where each node only has a right child

**Complexity Analysis**:
- **Time Complexity**: O(n) where n is the number of nodes
  - O(n) for in-order traversal
  - O(n) for tree reconstruction
- **Space Complexity**: O(n)
  - O(n) for the array to store values
  - O(h) for recursion stack where h is tree height (O(n) in worst case)

**Alternative Approach**: In-place transformation using threading technique (more space-efficient but complex)

# Tags

Binary Search Tree, Tree Traversal, In-order Traversal, Tree Reconstruction

