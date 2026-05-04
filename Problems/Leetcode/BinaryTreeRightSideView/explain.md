## Problem

https://leetcode.com/problems/binary-tree-right-side-view/description

Given the root of a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

### Examples

**Example 1:**
```
Input: root = [1,2,3,null,5,null,4]
Output: [1,3,4]
```

**Example 2:**
```
Input: root = [1,2,3,4,null,null,null,5]
Output: [1,3,4,5]
```

**Example 3:**
```
Input: root = [1,null,3]
Output: [1,3]
```

**Example 4:**
```
Input: root = []
Output: []
```

### Constraints

- The number of nodes in the tree is in the range [0, 100]
- -100 <= Node.val <= 100

## Observations

1. **Level-Order Traversal (BFS)**: The key insight is that the rightmost visible node at each level is the last node we encounter when doing a level-order (breadth-first) traversal.

2. **Last Node Per Level**: By processing nodes level by level, we naturally see the rightmost node first (since we traverse left-to-right in the queue, but the rightmost node is the last one processed at that level).

3. **Empty Tree**: We need to handle the edge case where the tree is empty and return an empty list.

4. **No Need for Separate Tracking**: Unlike DFS approaches that might track node depth/height, BFS naturally groups nodes by level, making it easy to identify the last (rightmost) node in each level.

5. **Time Complexity**: $O(n)$ where $n$ is the number of nodes, as we visit each node exactly once.

6. **Space Complexity**: $O(w)$ where $w$ is the maximum width of the tree (maximum number of nodes at any level), for the queue storage.

## Solution

### Approach: Level-Order Traversal (BFS)

The solution uses a queue-based level-order traversal:

```python
from collections import deque

class Solution:
    def rightSideView(self, root: Optional[TreeNode]) -> List[int]:
        res = []
        if not root:
            return res

        q = deque([root])
        while q:
            size = len(q)           # Number of nodes at current level
            last_val = None
            
            # Process all nodes at this level
            for _ in range(size):
                cur = q.popleft()
                last_val = cur.val  # Keep updating to get the rightmost value
                
                # Add children to queue for next level
                if cur.left:
                    q.append(cur.left)
                if cur.right:
                    q.append(cur.right)
            
            # The last value processed at this level is the rightmost visible node
            if last_val != None:
                res.append(last_val)

        return res
```

### How It Works

1. **Initialize**: Create a queue with the root node and an empty result list.

2. **Level Processing Loop**: While the queue is not empty:
   - Store the current queue size (this represents all nodes at the current level)
   - Initialize `last_val` to track the last node value at this level
   
3. **Process Current Level**: Iterate through all nodes at the current level (exactly `size` iterations):
   - Dequeue the first node from the queue
   - Update `last_val` with the current node's value
   - Add the node's left child to the queue (if it exists)
   - Add the node's right child to the queue (if it exists)
   
4. **Collect Result**: After processing all nodes at a level, `last_val` contains the rightmost node's value, so we add it to the result.

5. **Return**: Return the list of rightmost values from top to bottom.

### Key Insight

The crucial observation is that by processing nodes level-by-level (left-to-right), the **last node processed at each level is the rightmost node** from that level. We don't need to track depth or use recursion—the natural order of BFS automatically gives us the rightmost node when we keep updating `last_val` throughout each level.

### Example Walkthrough

For `root = [1,2,3,null,5,null,4]`:

```
       1
      / \
     2   3
      \   \
       5   4
```

**Execution:**
- **Level 0**: Process node 1, `last_val = 1` → add 1 to result
- **Level 1**: Process nodes 2, 3 in order, `last_val = 3` → add 3 to result
- **Level 2**: Process nodes 5, 4 in order, `last_val = 4` → add 4 to result
- **Result**: [1, 3, 4] ✓

### Alternative Approaches

1. **DFS with Depth Tracking**: Use recursion to track depth and keep only the first node encountered at each depth (which is the rightmost when traversing right-first). Time: $O(n)$, Space: $O(h)$ for recursion stack.

2. **DFS Right-First**: Do a pre-order traversal visiting right subtree before left subtree. Add a node to result if it's the first node at its depth. This naturally captures rightmost nodes.

3. **BFS with Explicit Right-First**: Modify the queue operations to prioritize the right child, ensuring we encounter the rightmost node first at each level.

# Tags

- **Algorithms**: Breadth-First Search (BFS), Tree Traversal, Level-Order Traversal
- **Data Structures**: Binary Tree, Queue
- **Difficulty**: Medium
- **Topics**: Tree, Breadth-First Search

