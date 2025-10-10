## Problem

https://leetcode.com/problems/populating-next-right-pointers-in-each-node/description/
https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/description/

```
You are given a perfect binary tree where all leaves are on the same level, and every parent has two children. The binary tree has the following definition:

struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

Example 1:

Input: root = [1,2,3,4,5,6,7]
Output: [1,#,2,3,#,4,5,6,7,#]
Explanation: Given the above perfect binary tree (Figure A), your function should populate each next pointer to point to its next right node, just like in Figure B. The serialized output is in level order as connected by the next pointers, with '#' signifying the end of each level.

Example 2:

Input: root = []
Output: []

Constraints:

The number of nodes in the tree is in the range [0, 212 - 1].
-1000 <= Node.val <= 1000

Follow-up:

You may only use constant extra space.
The recursive approach is fine. You may assume implicit stack space does not count as extra space for this problem.
```

## Observations

**What are we trying to achieve?**
- We need to connect each node to its next right node at the same level
- If there's no next right node, the `next` pointer should be `NULL`
- We're working with a perfect binary tree (all leaves at same level, every parent has 2 children)

**Key Insights:**
1. **Level-by-level processing**: Since we need to connect nodes at the same level, we need to process the tree level by level
2. **BFS naturally groups nodes by level**: Breadth-First Search (BFS) processes nodes level by level, which is exactly what we need
3. **Within each level, connect adjacent nodes**: Once we have all nodes at a level, we can easily connect them from left to right

**Visual Example:**
```
Original tree:        After connecting:
      1                     1 -> NULL
    /   \                 /   \
   2     3               2 --> 3 -> NULL
  / \   / \             / \   / \
 4   5 6   7           4-->5 6-->7 -> NULL
```

**Why BFS works:**
- BFS uses a queue to process nodes level by level
- When we process a level, we know exactly how many nodes are in that level
- We can collect all nodes in the current level and then connect them sequentially

## Solution

**Algorithm Steps:**

1. **Handle Edge Case**: If root is `None`, return `None`

2. **Level-by-Level BFS**:
- Use a queue to store nodes to be processed
- For each level:
  - Count how many nodes are currently in the queue (this is the size of current level)
  - Process exactly that many nodes to get all nodes in the current level
  - Add children of processed nodes to queue for next level

1. **Collect Nodes by Level**:
- Store all nodes of each level in a list
- This gives us easy access to connect adjacent nodes

1. **Connect Adjacent Nodes**:
- For each level, iterate through nodes and connect `node[i].next = node[i+1]`
- The last node in each level automatically gets `next = None` (default)

**Example Execution:**

For tree `[1,2,3,4,5,6,7]`:

1. **Level 0**: `rows = [[1]]`
2. **Level 1**: `rows = [[1], [2,3]]`
3. **Level 2**: `rows = [[1], [2,3], [4,5,6,7]]`

**Connecting:**
- Level 0: Only 1 node, nothing to connect
- Level 1: Connect `2.next = 3`
- Level 2: Connect `4.next = 5`, `5.next = 6`, `6.next = 7`

**Time Complexity**: O(n) - Visit each node exactly once
**Space Complexity**: O(n) - Store all nodes in the `rows` list + queue space

**Alternative Approaches:**
- **Optimized BFS**: Process and connect nodes level by level without storing them
- **Using existing connections**: Use previously established `next` pointers to traverse levels
- **Recursive**: Use the tree structure to connect nodes recursively

## Tags

binary tree, bfs