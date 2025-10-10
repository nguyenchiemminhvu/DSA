## Problem

https://leetcode.com/problems/n-ary-tree-level-order-traversal/

```
Given an n-ary tree, return the level order traversal of its nodes' values.

Nary-Tree input serialization is represented in their level order traversal, each group of children is separated by the null value (See examples).

Example 1:

Input: root = [1,null,3,2,4,null,5,6]
Output: [[1],[3,2,4],[5,6]]

Example 2:

Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
Output: [[1],[2,3,4,5],[6,7,8,9,10],[11,12,13],[14]]

Constraints:

The height of the n-ary tree is less than or equal to 1000
The total number of nodes is between [0, 104]
```

## Observations

1. **N-ary Tree Structure**: Unlike binary trees, each node can have any number of children stored in a list.

2. **Level Order Traversal**: We need to visit nodes level by level, collecting all nodes at each depth before moving to the next level.

3. **BFS Pattern**: This is a classic Breadth-First Search (BFS) problem where we process nodes level by level using a queue.

4. **Queue-based Approach**: We use a queue to maintain the order of nodes to visit, processing all nodes at the current level before adding their children to the queue.

5. **Level Grouping**: The key insight is to process nodes in batches - all nodes currently in the queue belong to the same level.

6. **Edge Case**: Handle the case where the root is `None` (empty tree).

## Solution

### Step-by-Step Process:

1. **Initialize**: Start with an empty result array and check if root exists
2. **Queue Setup**: Add the root node to a deque (double-ended queue)
3. **Level Processing**: 
   - Record the current queue length (number of nodes at this level)
   - Create an empty row for current level values
   - Process exactly that many nodes (ensuring we only handle current level)
4. **Node Processing**:
   - Pop node from front of queue
   - Add its value to current level's row
   - Add all its children to the back of queue (for next level)
5. **Complete Level**: Add the completed row to result array
6. **Repeat**: Continue until queue is empty

### Key Implementation Details:

- **Level Boundary**: `cur_len = len(q)` captures the exact number of nodes at current level before adding children
- **Child Handling**: The `for child in cur_node.children` loop safely handles nodes with varying numbers of children
- **Queue Operations**: Using `popleft()` and `append()` maintains FIFO order for proper level-order traversal

### Example Walkthrough:
For tree `[1,null,3,2,4,null,5,6]`:
- Level 0: Process node 1, add children [3,2,4] → Result: [[1]]
- Level 1: Process nodes 3,2,4, add children [5,6] → Result: [[1],[3,2,4]]  
- Level 2: Process nodes 5,6, no children → Result: [[1],[3,2,4],[5,6]]

**Time Complexity**: O(N) where N is the total number of nodes in the tree
**Space Complexity**: O(W) where W is the maximum width of the tree (maximum number of nodes at any level)

## Tags

n-ary tree, bfs