## Problem

https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/description

Given the root of a binary tree, return the zigzag level order traversal of its nodes' values. The traversal alternates direction at each level: left to right, then right to left, and so on.

**Examples:**

1. Input: `root = [3,9,20,null,null,15,7]`
   Output: `[[3],[20,9],[15,7]]`

2. Input: `root = [1]`
   Output: `[[1]]`

3. Input: `root = []`
   Output: `[]`

**Constraints:**
- The number of nodes in the tree is in the range `[0, 2000]`
- `-100 <= Node.val <= 100`

## Observations

1. **Level Order Traversal**: This is a variant of BFS where we need to process nodes level by level, not just visit them in BFS order.

2. **Alternating Direction**: At even levels (0, 2, 4...), we add values left-to-right. At odd levels (1, 3, 5...), we add values right-to-left. This can be achieved by reversing every other level.

3. **Level Grouping**: We need to group nodes by their level, so we can reverse specific levels. This requires tracking the number of nodes at each level before processing them.

4. **Queue-Based Approach**: A deque (double-ended queue) is ideal for level-order traversal. We can keep a flag to track whether we should reverse the current level.

5. **Time Complexity**: $O(n)$ where $n$ is the number of nodes - we visit each node exactly once.

6. **Space Complexity**: $O(w)$ where $w$ is the maximum width of the tree - the queue holds at most one level of nodes.

## Solution

```python
from collections import deque
from typing import Optional, List

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def zigzagLevelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        if not root:
            return []
        
        def bfs() -> List[List[int]]:
            rows = []
            rev = False
            q = deque([root])
            
            while q:
                size = len(q)  # Number of nodes at current level
                row = []
                
                # Process all nodes at current level
                for _ in range(size):
                    cur = q.popleft()
                    row.append(cur.val)
                    
                    # Add children to queue for next level
                    if cur.left:
                        q.append(cur.left)
                    if cur.right:
                        q.append(cur.right)
                
                # Reverse the row if we're at an odd level
                if rev:
                    row.reverse()
                
                rows.append(row)
                rev = not rev  # Toggle direction for next level
            
            return rows
        
        return bfs()
```

### Algorithm Explanation

**Step 1: Initialize**
- Create an empty `rows` list to store all levels
- Initialize `rev` flag to `False` (process first level left-to-right)
- Create a deque with the root node

**Step 2: Process Each Level**
- While the queue is not empty:
  - Get the current queue size (number of nodes at this level)
  - Create an empty `row` list for the current level
  - Process exactly `size` nodes from the queue

**Step 3: Collect Node Values**
- For each node at the current level:
  - Remove it from the front of the queue
  - Add its value to the current row
  - Enqueue its left child (if exists)
  - Enqueue its right child (if exists)

**Step 4: Handle Direction**
- If `rev` is `True`, reverse the current row (for odd levels)
- Append the row to results
- Toggle the `rev` flag for the next level

**Step 5: Return**
- Return the list of all level rows

### Walkthrough with Example

Tree: `[3,9,20,null,null,15,7]`
```
      3
     / \
    9   20
       / \
      15  7
```

- **Level 0**: Process [3], rev=False → [3] → append [3], toggle rev
- **Level 1**: Process [9, 20], rev=True → [9, 20] → reverse to [20, 9] → append [20, 9], toggle rev
- **Level 2**: Process [15, 7], rev=False → [15, 7] → no reverse → append [15, 7]

Result: `[[3], [20, 9], [15, 7]]` ✓

### Key Insights

- **Why reverse instead of deque operations**: Reversing a list is $O(n)$ where $n$ is the level size. Using deque's appendleft/popleft for alternating directions would be equally efficient but less intuitive.
  
- **Size snapshot**: By capturing `size = len(q)` at the start of each iteration, we ensure we only process nodes from the current level, not any children added during this iteration.

- **Binary flip pattern**: The `rev = not rev` toggle elegantly handles the zigzag pattern without needing a level counter.

# Tags

- Binary Tree
- Level Order Traversal (BFS)
- Deque
- Graph Traversal

