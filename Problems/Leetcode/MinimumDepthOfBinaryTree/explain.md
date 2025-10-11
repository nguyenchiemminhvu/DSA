## Problem

https://leetcode.com/problems/minimum-depth-of-binary-tree/

```
Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.

Note: A leaf is a node with no children.

Example 1:

Input: root = [3,9,20,null,null,15,7]
Output: 2

Example 2:

Input: root = [2,null,3,null,4,null,5,null,6]
Output: 5

Constraints:

The number of nodes in the tree is in the range [0, 105].
-1000 <= Node.val <= 1000
```

## Observations

1. **Problem Definition**: We need to find the minimum depth, which is the shortest path from root to any leaf node.

2. **Key Insight**: A leaf node is defined as a node with NO children (both left and right are None). This is crucial - a node with only one child is NOT a leaf.

3. **BFS vs DFS**: 
   - BFS is optimal here because it explores level by level, guaranteeing we find the first leaf at the minimum depth
   - DFS would need to explore all paths to find the minimum, making it less efficient

4. **Edge Cases**:
   - Empty tree (root is None) → return 0
   - Single node tree → return 1
   - Skewed tree (like Example 2) → need to traverse to the actual leaf

5. **Level Tracking**: We process nodes level by level and increment depth only after processing all nodes at current level.

## Solution

**Algorithm**: Breadth-First Search (BFS)

**Approach**:
1. Handle edge case: if root is None, return 0
2. Initialize a queue with the root node and set level = 1
3. For each level:
   - Process all nodes at current level
   - For each node, check if it's a leaf (no children)
   - If leaf found, return current level (this is guaranteed to be minimum)
   - Otherwise, add children to queue for next level
4. Increment level after processing all nodes at current level

**Time Complexity**: O(n) where n is the number of nodes
- In worst case, we might visit all nodes (when minimum depth leaf is the last node we check)

**Space Complexity**: O(w) where w is maximum width of the tree
- Queue stores at most all nodes at the widest level
- In worst case (complete binary tree), this is O(n/2) = O(n)

**Why BFS is optimal**:
- BFS guarantees we find the first leaf at minimum depth
- We can return immediately when we find any leaf, no need to check deeper levels
- Level-order traversal naturally tracks depth

## Tags

binary tree, bfs