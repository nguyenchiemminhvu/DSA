## Problem

https://leetcode.com/problems/average-of-levels-in-binary-tree

```
Given the root of a binary tree, return the average value of the nodes on each level in the form of an array. Answers within 10-5 of the actual answer will be accepted.

Example 1:

Input: root = [3,9,20,null,null,15,7]
Output: [3.00000,14.50000,11.00000]
Explanation: The average value of nodes on level 0 is 3, on level 1 is 14.5, and on level 2 is 11.
Hence return [3, 14.5, 11].

Example 2:

Input: root = [3,9,20,15,7]
Output: [3.00000,14.50000,11.00000]

Constraints:

The number of nodes in the tree is in the range [1, 104].
-231 <= Node.val <= 231 - 1
```

## Observations

1. **Level-by-level traversal**: We need to process nodes level by level to calculate the average for each level separately.

2. **BFS approach**: This problem is naturally suited for Breadth-First Search (BFS) since we need to visit all nodes at the same level before moving to the next level.

3. **Queue data structure**: Using a queue (deque) allows us to process nodes in FIFO order, which is perfect for level-order traversal.

4. **Level separation**: We need to know when one level ends and the next begins. We can achieve this by capturing the queue size at the beginning of each level.

5. **Floating-point precision**: The problem asks for averages, so we need to work with floating-point numbers and handle division carefully.

6. **Edge case**: Handle the case where the root is None (empty tree).

## Solution

The solution uses **Level-Order Traversal (BFS)** with a queue:

### Algorithm Steps:

1. **Initialize**: Create an empty result list and handle the edge case of an empty tree.

2. **BFS Setup**: Use a deque and start with the root node.

3. **Level Processing**: 
   - For each level, capture the current queue size (`cur_len`)
   - Process exactly `cur_len` nodes (all nodes at current level)
   - Keep track of the sum (`row_val`) and count (`row_count`) of nodes at this level

4. **Node Processing**:
   - Dequeue a node and add its value to the level sum
   - Add the node's children (if they exist) to the queue for the next level

5. **Average Calculation**: After processing all nodes at a level, calculate the average and add it to the result.

### Key Implementation Details:

- **Queue management**: `deque` from collections provides efficient O(1) append and popleft operations
- **Level boundary**: `cur_len = len(q)` captures the number of nodes at the current level
- **Floating-point arithmetic**: Using `row_val = 0.0` ensures floating-point division
- **Children addition**: Add left and right children to queue for next level processing

### Time Complexity: O(n)
- We visit each node exactly once, where n is the number of nodes in the tree

### Space Complexity: O(w)
- Where w is the maximum width of the tree (maximum number of nodes at any level)
- In the worst case (complete binary tree), this is O(n/2) = O(n)

### Example Walkthrough:
For tree `[3,9,20,null,null,15,7]`:
- Level 0: [3] → average = 3.0
- Level 1: [9,20] → average = (9+20)/2 = 14.5  
- Level 2: [15,7] → average = (15+7)/2 = 11.0
- Result: [3.0, 14.5, 11.0]

# Tags

- Binary Tree
- Breadth-First Search (BFS)
- Level-Order Traversal
- Queue
- Tree Traversal

