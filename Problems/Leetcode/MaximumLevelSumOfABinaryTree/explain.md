## Problem

https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/description/

Given the root of a binary tree, the level of its root is 1, the level of its children is 2, and so on.

Return the **smallest level x** such that the sum of all the values of nodes at level x is maximal.

### Examples

**Example 1:**
```
Input: root = [1,7,0,7,-8,null,null]
Output: 2

Tree structure:
        1           (Level 1: sum = 1)
       / \
      7   0         (Level 2: sum = 7 + 0 = 7)
     / \
    7  -8           (Level 3: sum = 7 + (-8) = -1)

Explanation: 
Level 1 sum = 1
Level 2 sum = 7 + 0 = 7 (maximum)
Level 3 sum = 7 + (-8) = -1
Return level 2 as it has the maximum sum.
```

**Example 2:**
```
Input: root = [989,null,10250,98693,-89388,null,null,null,-32127]
Output: 2

Tree structure:
        989                    (Level 1: sum = 989)
          \
          10250                (Level 2: sum = 10250) [maximum]
          /    \
      98693   -89388           (Level 3: sum = 9305)
                 \
               -32127           (Level 4: sum = -32127)
```

### Constraints

- The number of nodes in the tree is in the range `[1, 10^4]`
- `-10^5 <= Node.val <= 10^5`

---

## Observations

1. **Level-Order Traversal Required**: We need to process the tree level by level, which suggests using BFS (Breadth-First Search).

2. **Track Multiple Values**: We need to keep track of:
   - Current level number
   - Sum of values at each level
   - Maximum sum encountered so far
   - The level with maximum sum

3. **Negative Values Matter**: Since nodes can have negative values, we must:
   - Initialize `max_sum` to negative infinity (`float('-inf')`) rather than 0
   - This ensures even if all levels have negative sums, we still find the correct answer

4. **Return Smallest Level**: If multiple levels have the same maximum sum, we return the smallest level number. This is naturally handled by only updating when `cur_sum > max_sum` (not `>=`).

5. **Complete Level Processing**: At each level, we must process all nodes before moving to the next level. This is achieved by:
   - Recording the queue size at the start of each level
   - Processing exactly that many nodes

---

## Solution

### Algorithm: BFS with Level Tracking

**Step-by-step approach:**

1. **Initialize tracking variables:**
   - `max_level = 0`: stores the level with maximum sum
   - `cur_level = 0`: tracks current level (starts at 0, incremented before processing)
   - `max_sum = float('-inf')`: stores the maximum sum found
   - `q = deque([root])`: queue for BFS, initialized with root

2. **Process each level:**
   ```
   While queue is not empty:
       - Increment current level
       - Initialize current level sum to 0
       - Record number of nodes at this level (queue size)
       
       For each node at current level:
           - Remove node from queue
           - Add its value to current level sum
           - Add its children to queue (for next level)
       
       If current level sum > maximum sum:
           - Update maximum sum
           - Update maximum level
   ```

3. **Return the level with maximum sum**

### Implementation

```python
from collections import deque

class Solution:
    def maxLevelSum(self, root: Optional[TreeNode]) -> int:
        def bfs() -> int:
            max_level = 0
            cur_level = 0
            max_sum = float('-inf')  # Handle negative values correctly
            q = deque([root])
            
            while q:
                cur_level += 1  # Increment level (1-indexed)
                cur_sum = 0
                size = len(q)  # Number of nodes at current level
                
                # Process all nodes at current level
                for _ in range(size):
                    cur_node = q.pop()  # Remove from right (FIFO)
                    cur_sum += cur_node.val
                    
                    # Add children for next level
                    if cur_node.left:
                        q.appendleft(cur_node.left)  # Add to left
                    if cur_node.right:
                        q.appendleft(cur_node.right)  # Add to left
                
                # Update max if current level has larger sum
                if cur_sum > max_sum:  # Use > not >= to get smallest level
                    max_sum = cur_sum
                    max_level = cur_level
            
            return max_level
        
        return bfs()
```

### Key Implementation Details

1. **Queue Operations:**
   - `q.pop()`: Remove from right (dequeue)
   - `q.appendleft()`: Add to left (enqueue)
   - This maintains FIFO order: append left, pop right

2. **Level Boundary:**
   - `size = len(q)` captures the exact number of nodes at current level
   - Processing exactly `size` nodes ensures we don't mix levels

3. **Comparison Logic:**
   - Using `>` instead of `>=` ensures we return the **smallest** level when there are ties

4. **Initialization:**
   - `max_sum = float('-inf')` handles cases where all sums are negative
   - `cur_level = 0` then incremented to 1 immediately (1-indexed levels)

### Complexity Analysis

**Time Complexity: O(n)**
- We visit each node exactly once
- Where n is the number of nodes in the tree

**Space Complexity: O(w)**
- Where w is the maximum width of the tree (maximum number of nodes at any level)
- In the worst case (complete binary tree), this is O(n/2) = O(n)
- The queue stores at most one complete level at a time

---

### Alternative Approaches

**1. Recursive DFS with Level Tracking**
```python
def maxLevelSum(self, root: Optional[TreeNode]) -> int:
    level_sums = []
    
    def dfs(node, level):
        if not node:
            return
        if level == len(level_sums):
            level_sums.append(0)
        level_sums[level] += node.val
        dfs(node.left, level + 1)
        dfs(node.right, level + 1)
    
    dfs(root, 0)
    max_sum = max(level_sums)
    return level_sums.index(max_sum) + 1  # +1 for 1-indexed
```

**Pros:** Cleaner code, easier to understand  
**Cons:** Uses O(h) recursive call stack, where h is tree height

**2. BFS with Dictionary**
```python
def maxLevelSum(self, root: Optional[TreeNode]) -> int:
    level_sums = {}
    q = deque([(root, 1)])
    
    while q:
        node, level = q.popleft()
        level_sums[level] = level_sums.get(level, 0) + node.val
        if node.left:
            q.append((node.left, level + 1))
        if node.right:
            q.append((node.right, level + 1))
    
    return max(level_sums, key=level_sums.get)
```

**Pros:** No need to track level boundaries explicitly  
**Cons:** Extra space for storing all level sums

---

### Common Pitfalls

1. **Initializing max_sum to 0**: Fails when all node values are negative
2. **Using >= instead of >**: Returns larger level number in case of ties
3. **Not processing complete levels**: Mixing nodes from different levels
4. **Wrong queue operations**: Using wrong end for enqueue/dequeue operations
5. **0-indexed vs 1-indexed**: Problem specifies levels start at 1, not 0

---

# Tags

`Binary Tree` `BFS` `Level-Order Traversal` `Queue` `Tree Traversal`
