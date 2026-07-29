## Problem

https://leetcode.com/problems/find-largest-value-in-each-tree-row/description/

```
Given the root of a binary tree, return an array of the largest value in each row of the tree (0-indexed).

Example 1:

Input: root = [1,3,2,5,3,null,9]
Output: [1,3,9]

Example 2:

Input: root = [1,2,3]
Output: [1,3]

Constraints:

The number of nodes in the tree will be in the range [0, 10^4].
-2^31 <= Node.val <= 2^31 - 1
```

## Observations

### Key Insights
1. **Row = Level**: Each "row" in the problem is simply a level of the binary tree. We need to find the maximum value among all nodes at each level.

2. **BFS is the natural fit**: Level-order traversal (BFS) groups nodes by their depth, making it straightforward to track the maximum value per level.

3. **DFS also works**: A depth-first traversal can be used by passing the current depth as a parameter. When visiting a node at depth `d`, we update `result[d]` with the maximum value seen so far.

### Algorithm Analysis

#### Approach 1: BFS (Level-order Traversal)
- Use a queue to process nodes level by level.
- At the start of each level, snapshot the queue size to know how many nodes belong to that level.
- Track the running maximum across all nodes in the current level.
- **Time Complexity**: `O(n)` — every node is visited exactly once.
- **Space Complexity**: `O(w)` — where `w` is the maximum width of the tree (queue holds at most one full level at a time). Worst case `O(n)` for a complete binary tree.

#### Approach 2: DFS (Pre-order / any order)
- Recursively traverse the tree, carrying the current `depth`.
- Extend the result list when visiting a new depth for the first time.
- Update `result[depth] = max(result[depth], node.val)` at each visit.
- **Time Complexity**: `O(n)`.
- **Space Complexity**: `O(h)` — where `h` is the height of the tree (call stack). `O(log n)` for balanced trees, `O(n)` worst case for skewed trees.

### Implementation Details
1. **BFS batch processing**: Record `level_size = len(queue)` before the inner loop so we only process nodes belonging to the current level, then enqueue their children for the next iteration.

2. **DFS depth tracking**:
   - Use `len(result) == depth` as the condition to append a new entry before comparing.
   - Ensure both left and right subtrees are visited.

3. **Edge cases handled**:
   - Empty tree (`root is None`) → return `[]`.
   - Single-node tree → return `[node.val]`.
   - Negative values are handled correctly because `max()` works on any integers.

## Tags

binary tree, BFS, DFS, level-order traversal

