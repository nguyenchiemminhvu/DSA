## Problem

https://leetcode.com/problems/cousins-in-binary-tree/description/

```
Given the root of a binary tree with unique values and the values of two different nodes of the tree x and y, return true if the nodes corresponding to the values x and y in the tree are cousins, or false otherwise.

Two nodes of a binary tree are cousins if they have the same depth with different parents.

Note that in a binary tree, the root node is at the depth 0, and children of each depth k node are at the depth k + 1.

Example 1:

Input: root = [1,2,3,4], x = 4, y = 3
Output: false

Example 2:

Input: root = [1,2,3,null,4,null,5], x = 5, y = 4
Output: true

Example 3:

Input: root = [1,2,3,null,4], x = 2, y = 3
Output: false

Constraints:

The number of nodes in the tree is in the range [2, 100].
1 <= Node.val <= 100
Each node has a unique value.
x != y
x and y are exist in the tree.
```

## Observations

1. **Definition of Cousins**: Two nodes are cousins if they:
   - Have the same depth (distance from root)
   - Have different parents (not siblings)

2. **Key Requirements**: 
   - Need to track both depth and parent for each target node
   - Root is at depth 0, but the solution uses depth 1 for root (which works consistently)
   - Must find both nodes x and y to compare their properties

3. **Approach Analysis**:
   - The solution uses inorder traversal, but any traversal would work since we need to visit all nodes
   - Uses class variables (self.depth, self.parent) to store node information
   - Tracks depth by incrementing as we go deeper
   - Tracks parent by passing the current node as parent to children

4. **Edge Cases**:
   - If nodes are siblings (same parent) → not cousins
   - If nodes are at different depths → not cousins
   - Root node cannot be a cousin (has no parent)

## Solution

1. **Initialization**: Create dictionaries to store depth and parent information for nodes x and y

2. **Traversal**: Use inorder traversal (though any traversal works) to visit all nodes:
   - Pass current node as parent to its children
   - Increment depth for children
   - When we find target nodes x or y, store their depth and parent

3. **Comparison**: After traversal, check if:
   - Nodes have same depth: `self.depth[x] == self.depth[y]`
   - Nodes have different parents: `self.parent[x] != self.parent[y]`

### Time Complexity: O(n)
- We visit each node at most once during traversal
- Dictionary operations are O(1)

### Space Complexity: O(h) 
- Recursion stack depth equals tree height h
- Additional O(1) for the dictionaries (only store 2 entries each)
- In worst case (skewed tree): O(n)
- In best case (balanced tree): O(log n)

### Alternative Approaches:
1. **BFS with level tracking**: Process nodes level by level, easier to track depths
2. **Single DFS with early termination**: Stop when both nodes are found
3. **Iterative approaches**: Use explicit stack instead of recursion

# Tags

`Binary Tree` `Tree Traversal` `DFS` `Depth Tracking` `Parent-Child Relationship`

