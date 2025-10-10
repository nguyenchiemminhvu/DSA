## Problem

https://leetcode.com/problems/binary-tree-level-order-traversal/

```
Given the root of a binary tree, return the level order traversal of its nodes' values. (i.e., from left to right, level by level).

Example 1:

Input: root = [3,9,20,null,null,15,7]
Output: [[3],[9,20],[15,7]]

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

### Key Insights
1. **Level-by-level processing**: The problem requires us to traverse the tree level by level, collecting all nodes at each depth before moving to the next level.

2. **BFS is the natural choice**: Breadth-First Search (BFS) is the most intuitive approach since it naturally processes nodes level by level.

3. **Queue-based approach**: Using a queue (FIFO) ensures we process nodes in the correct order - all nodes at level `i` before any nodes at level `i+1`.

### Algorithm Analysis
- **Time Complexity**: `O(n)` where n is the number of nodes in the tree. We visit each node exactly once.
- **Space Complexity**: `O(w)` where w is the maximum width of the tree. In the worst case (complete binary tree), this is `O(n/2) = O(n)`.

### Implementation Details
1. **Level separation technique**: The key insight is to process the queue in batches. At the start of each level, we record the current queue size, which represents the number of nodes at the current level.

2. **Queue operations**: 
- `Q.pop(0)` removes from the front (dequeue)
- `Q.append()` adds to the back (enqueue)
- Note: Using `collections.deque` would be more efficient than list for queue operations

1. **Edge cases handled**:
- Empty tree (root is None) returns empty list
- Single node tree returns `[[node.val]]`
- Tree with only one level works correctly

## Tags

binary tree, BFS