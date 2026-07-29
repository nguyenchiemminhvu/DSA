# Check Completeness of a Binary Tree

## Problem

https://leetcode.com/problems/check-completeness-of-a-binary-tree/description/

Given the `root` of a binary tree, determine if it is a **complete binary tree**.

In a complete binary tree, every level, except possibly the last, is completely filled, and all nodes in the last level are **as far left as possible**. It can have between `1` and `2^h` nodes inclusive at the last level `h`.

### Examples

**Example 1:**
- Input: `root = [1,2,3,4,5,6]`
- Output: `true`
- Explanation: Every level before the last is full (levels `{1}` and `{2,3}`), and all nodes in the last level (`{4,5,6}`) are as far left as possible.

**Example 2:**
- Input: `root = [1,2,3,4,5,null,7]`
- Output: `false`
- Explanation: The node with value `7` isn't as far left as possible.

### Constraints
- The number of nodes in the tree is in the range `[1, 100]`
- `1 <= Node.val <= 1000`

---

## Observations

### 1. **Definition of Complete Binary Tree**
- All levels except the last must be **completely filled**
- The last level must have all nodes **packed to the left**
- This means once we encounter a `null` child during a level-order traversal, **no more non-null nodes should appear** after it

### 2. **BFS / Level-Order Traversal is a Natural Fit**
- A BFS traversal visits nodes level by level, left to right — exactly the order in which a complete binary tree is filled
- If we enqueue **both left and right children** (including `null` pointers), the first `null` we dequeue marks the point where the complete binary tree "should end"
- Any non-null node dequeued after the first `null` proves incompleteness

### 3. **The "Null Flag" Trick**
- Traverse the tree with BFS, adding both children (even `null` ones) to the queue
- Track a boolean flag `found_null = False`
- When we dequeue a `null`, set `found_null = True`
- If we later dequeue a non-null node while `found_null` is `True` → return `False`
- If traversal completes without violation → return `True`

### 4. **Index-Based Approach (Alternative)**
- In a complete binary tree stored as a 1-indexed array, for a node at index `i`:
  - Left child is at `2*i`, right child is at `2*i + 1`
- The total count of nodes `n` must equal the maximum index reached
- If `max_index == n`, the tree is complete; otherwise it is not
- This requires a DFS to count nodes and find the maximum index simultaneously

---

## Solution

### Algorithm 1: BFS with Null Flag

**Time Complexity**: O(n) — each node is visited once  
**Space Complexity**: O(n) — queue holds at most one full level of nodes

#### Key Steps

1. Start BFS from `root`, enqueue the root node
2. Dequeue node one by one:
   - If the node is `null`, set `found_null = True` and continue
   - If the node is non-null and `found_null` is already `True`, return `False`
   - Otherwise, enqueue left and right children (even if `null`)
3. If the loop finishes cleanly, return `True`

```python
from collections import deque
from typing import Optional

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def isCompleteTree(self, root: Optional[TreeNode]) -> bool:
        queue = deque([root])
        found_null = False

        while queue:
            node = queue.popleft()

            if node is None:
                found_null = True
            else:
                if found_null:
                    return False  # non-null node appears after a null gap
                queue.append(node.left)
                queue.append(node.right)

        return True
```

#### Execution Flow Example

**Input**: `root = [1,2,3,4,5,null,7]`

```
Queue:  [1]
Dequeue 1  → found_null=False, enqueue 2, 3
Queue:  [2, 3]
Dequeue 2  → found_null=False, enqueue 4, 5
Queue:  [3, 4, 5]
Dequeue 3  → found_null=False, enqueue null, 7
Queue:  [4, 5, null, 7]
Dequeue 4  → found_null=False, enqueue null, null
Queue:  [5, null, 7, null, null]
Dequeue 5  → found_null=False, enqueue null, null
Queue:  [null, 7, null, null, null, null]
Dequeue null → found_null=True
Dequeue 7  → found_null is True → return False ✗
```

---

### Algorithm 2: Index-Based DFS

**Time Complexity**: O(n)  
**Space Complexity**: O(h) — recursion stack depth (h = tree height)

Assign each node an index as if stored in a 1-indexed array. The tree is complete if and only if `max_index == total_node_count`.

```python
class Solution:
    def isCompleteTree(self, root: Optional[TreeNode]) -> bool:
        def dfs(node, index):
            if node is None:
                return (0, 0)  # (count, max_index)
            left_count, left_max = dfs(node.left, 2 * index)
            right_count, right_max = dfs(node.right, 2 * index + 1)
            total_count = left_count + right_count + 1
            max_index = max(index, left_max, right_max)
            return (total_count, max_index)

        count, max_idx = dfs(root, 1)
        return count == max_idx
```

---

## Tags

- **Tree**: Binary tree structure and traversal
- **BFS**: Level-order traversal with null-gap detection
- **DFS**: Index-based completeness verification
- **Binary Tree**: Complete binary tree properties

