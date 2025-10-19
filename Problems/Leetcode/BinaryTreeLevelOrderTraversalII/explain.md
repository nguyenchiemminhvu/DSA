## Problem

https://leetcode.com/problems/binary-tree-level-order-traversal-ii/description/

```
Given the root of a binary tree, return the bottom-up level order traversal of its nodes' values. (i.e., from left to right, level by level from leaf to root).

Example 1:

Input: root = [3,9,20,null,null,15,7]
Output: [[15,7],[9,20],[3]]

Example 2:

Input: root = [1]
Output: [[1]]

Example 3:

Input: root = []
Output: []

Constraints:

The number of nodes in the tree is in the range [0, 2000].
-1000 <= Node.val <= 1000
```

## Observations

1. **Bottom-up Level Order**: Unlike regular level order traversal, we need to return results from the bottom level to the top level.

2. **BFS vs Reverse**: Two main approaches:
   - Perform normal BFS and reverse the final result (what the solution does)
   - Use BFS with stack/deque to build bottom-up directly

3. **Edge Cases**:
   - Empty tree (root is None) → return empty list
   - Single node tree → return `[[node.val]]`

4. **Level-by-level Processing**: Need to process nodes level by level, collecting all nodes at the same level together.

5. **Queue for BFS**: Use deque for efficient append/pop operations from both ends.

## Solution

The solution uses **Breadth-First Search (BFS)** with a queue to traverse the tree level by level, then reverses the result to get bottom-up order.

### Algorithm Steps:

1. **Base Case**: If root is None, return empty list
2. **Initialize**: Create empty result list and queue with root node
3. **Level-by-level BFS**:
   - For each level, record current queue length
   - Process exactly that many nodes (all nodes at current level)
   - For each node: add value to current level array, add children to queue
   - Add completed level to results
4. **Reverse**: Return reversed result list to get bottom-up order

### Complexity Analysis:

- **Time Complexity**: O(n) where n is the number of nodes
  - Visit each node exactly once
- **Space Complexity**: O(w) where w is the maximum width of the tree
  - Queue stores at most one level of nodes
  - In worst case (complete binary tree), last level has n/2 nodes

### Example Trace:

For tree `[3,9,20,null,null,15,7]`:
```
Level 0: [3]        → rows = [[3]]
Level 1: [9,20]     → rows = [[3], [9,20]]  
Level 2: [15,7]     → rows = [[3], [9,20], [15,7]]
Reverse: [[15,7], [9,20], [3]]
```

## Tags

binary tree, bfs