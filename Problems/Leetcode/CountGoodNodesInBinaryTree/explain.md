## Problem

https://leetcode.com/problems/count-good-nodes-in-binary-tree/description/

Given a binary tree `root`, a node X in the tree is named **good** if in the path from root to X there are **no nodes with a value greater than X**.

Return the number of good nodes in the binary tree.

**Constraints:**
- The number of nodes in the binary tree is in the range `[1, 10^5]`
- Each node's value is between `[-10^4, 10^4]`

**Examples:**

1. **Example 1:** 
   - Input: `root = [3,1,4,3,null,1,5]`
   - Output: `4`
   - Explanation: Nodes in blue are good.
     - Root Node (3) is always a good node
     - Node 4 → path (3,4) is the maximum value in the path starting from the root
     - Node 5 → path (3,4,5) is the maximum value in the path
     - Node 3 → path (3,1,3) is the maximum value in the path

2. **Example 2:**
   - Input: `root = [3,3,null,4,2]`
   - Output: `3`
   - Explanation: Node 2 → path (3, 3, 2) is not good, because "3" is higher than it

3. **Example 3:**
   - Input: `root = [1]`
   - Output: `1`
   - Explanation: Root is considered as good

## Observations

1. **Key Insight**: A node is "good" if its value is **greater than or equal to** the maximum value seen so far on the path from root to that node.

2. **Root is Always Good**: The root node is always good because there are no nodes before it on any path.

3. **Path Tracking Required**: To determine if a node is good, we need to track the maximum value encountered on the path from the root to the current node.

4. **DFS Approach**: This problem naturally lends itself to a depth-first search (DFS) traversal where we:
   - Pass down the maximum value seen so far
   - At each node, check if the current node's value is >= the previous maximum
   - Update the maximum for children nodes

5. **No Greedy Optimization Needed**: We must visit all nodes in the tree since we need to count all good nodes (unlike shortest path problems where we could prune).

6. **Comparison Operator**: Use `>=` instead of `>` because a node with the same value as the maximum on the path is still considered "good".

## Solution

```python
class Solution:
    def goodNodes(self, root: TreeNode) -> int:
        count = [0]
        
        def traversal(root: Optional[TreeNode], prev_max: float):
            if not root:
                return
            
            # Current node is good if its value >= maximum on path so far
            if root.val >= prev_max:
                count[0] += 1
            
            # Update maximum for children
            cur_max = max(root.val, prev_max)
            
            # Traverse left and right subtrees with updated maximum
            traversal(root.left, cur_max)
            traversal(root.right, cur_max)
        
        # Start traversal with negative infinity as initial max
        traversal(root, float('-inf'))
        return count[0]
```

### Algorithm Explanation

**Time Complexity**: $O(n)$ where $n$ is the number of nodes in the tree. We visit each node exactly once.

**Space Complexity**: $O(h)$ where $h$ is the height of the tree. This is the recursion stack depth. In the worst case (skewed tree), this could be $O(n)$.

### Step-by-Step Walkthrough (Example 1: `[3,1,4,3,null,1,5]`)

```
Tree structure:
        3
       / \
      1   4
     /   / \
    3   1   5
```

| Node | Path from Root | Max on Path | Is Good? | Reason |
|------|----------------|-------------|----------|--------|
| 3    | (3)            | 3           | ✓ Yes    | 3 >= -∞ |
| 1    | (3,1)          | 3           | ✗ No     | 1 < 3 |
| 4    | (3,4)          | 4           | ✓ Yes    | 4 >= 3 |
| 3    | (3,1,3)        | 3           | ✓ Yes    | 3 >= 3 |
| 1    | (3,4,1)        | 4           | ✗ No     | 1 < 4 |
| 5    | (3,4,5)        | 5           | ✓ Yes    | 5 >= 4 |

**Total Good Nodes: 4**

### Key Implementation Details

1. **Count Array**: Using `count = [0]` allows us to modify the counter in the nested function (avoiding nonlocal keyword).

2. **Initial Maximum**: Starting with `float('-inf')` ensures the root node is always considered good.

3. **Maximum Update**: `cur_max = max(root.val, prev_max)` ensures we track the maximum value on the path.

4. **Base Case**: Check `if not root` first to handle `None` nodes.

### Alternative Approach (Using Nonlocal)

```python
class Solution:
    def goodNodes(self, root: TreeNode) -> int:
        self.count = 0
        
        def traversal(node: Optional[TreeNode], max_val: float):
            if not node:
                return
            
            if node.val >= max_val:
                self.count += 1
            
            max_val = max(node.val, max_val)
            traversal(node.left, max_val)
            traversal(node.right, max_val)
        
        traversal(root, float('-inf'))
        return self.count
```

# Tags

- Binary Tree
- Depth-First Search (DFS)
- Tree Traversal
- Path Tracking
- LeetCode Medium

