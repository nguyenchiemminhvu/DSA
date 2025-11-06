## Problem

https://leetcode.com/problems/leaf-similar-trees/

```
Consider all the leaves of a binary tree, from left to right order, the values of those leaves form a leaf value sequence.

For example, in the given tree above, the leaf value sequence is (6, 7, 4, 9, 8).

Two binary trees are considered leaf-similar if their leaf value sequence is the same.

Return true if and only if the two given trees with head nodes root1 and root2 are leaf-similar.

Example 1:

Input: root1 = [3,5,1,6,2,9,8,null,null,7,4], root2 = [3,5,1,6,7,4,2,null,null,null,null,null,null,9,8]
Output: true

Example 2:

Input: root1 = [1,2,3], root2 = [1,3,2]
Output: false

Constraints:

The number of nodes in each tree will be in the range [1, 200].
Both of the given trees will have values in the range [0, 200].
```

## Observations

1. **Problem Understanding**: We need to determine if two binary trees have the same leaf value sequence when traversed from left to right.

2. **Key Insights**:
   - A leaf node is a node with no left and right children
   - We need to collect leaf values in left-to-right order (which corresponds to the order they appear in a depth-first traversal)
   - Two trees are leaf-similar if their leaf sequences are identical

3. **Approach Analysis**:
   - We can use any tree traversal method (preorder, inorder, postorder) as long as we only collect leaf nodes
   - The order of visiting leaves will be the same regardless of traversal method (left-to-right)
   - Post-order traversal is used here: visit left subtree → right subtree → process current node

4. **Edge Cases**:
   - Single node trees (root is a leaf)
   - Trees with different structures but same leaf sequence
   - Empty trees (though constraints say at least 1 node)

## Solution

### Algorithm Explanation

The solution uses a **post-order depth-first search (DFS)** approach:

1. **Helper Function**: `postorder(root, arr)`
   - Recursively traverses the tree in post-order
   - Only adds values to the array when encountering leaf nodes
   - A leaf node is identified by having both `left` and `right` children as `None`

2. **Main Logic**:
   - Create two separate arrays to store leaf sequences
   - Traverse both trees independently using the helper function
   - Compare the resulting arrays for equality

### Step-by-Step Walkthrough

For Example 1:
- `root1 = [3,5,1,6,2,9,8,null,null,7,4]`
- `root2 = [3,5,1,6,7,4,2,null,null,null,null,null,null,9,8]`

**Tree 1 Traversal**:
```
       3
      / \
     5   1
    / \ / \
   6 2 9  8
    / \
   7   4
```
- Visit leaves in order: 6, 7, 4, 9, 8
- `arr1 = [6, 7, 4, 9, 8]`

**Tree 2 Traversal**:
```
       3
      / \
     5   1
    / \ / \
   6 7 4  2
         / \
        9   8
```
- Visit leaves in order: 6, 7, 4, 9, 8  
- `arr2 = [6, 7, 4, 9, 8]`

**Result**: `arr1 == arr2` → `True`

### Time & Space Complexity

- **Time Complexity**: O(N + M) where N and M are the number of nodes in the two trees
  - We visit each node exactly once in both trees
  
- **Space Complexity**: O(H₁ + H₂ + L₁ + L₂) where:
  - H₁, H₂ are the heights of the trees (recursion stack space)
  - L₁, L₂ are the number of leaves in each tree (storage arrays)
  - In the worst case: O(N + M) for skewed trees with many leaves

### Alternative Approaches

1. **Generator/Iterator Approach**: Use generators to produce leaves on-demand and compare them one by one, potentially saving space
2. **Iterative with Stack**: Convert the recursive solution to iterative using explicit stacks
3. **Early Termination**: Stop as soon as a mismatch is found (though this requires more complex logic)

### Why This Solution Works

- The post-order traversal ensures we visit leaves in the correct left-to-right order
- By collecting all leaves first, we can easily compare the entire sequences
- The recursive approach naturally handles trees of any shape and size
- Simple and readable implementation that correctly identifies leaf nodes

# Tags

`Binary Tree` `Depth-First Search` `Tree Traversal` `Recursion` `Post-order Traversal`

