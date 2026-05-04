## Problem

https://leetcode.com/problems/longest-zigzag-path-in-a-binary-tree

# Longest ZigZag Path in a Binary Tree

## Problem

https://leetcode.com/problems/longest-zigzag-path-in-a-binary-tree

### Problem Statement

Given the root of a binary tree, find the longest ZigZag path contained in that tree.

A ZigZag path is defined as:
1. Start at any node in the binary tree and choose a direction (right or left)
2. If the current direction is **right**, move to the **right child**; otherwise, move to the **left child**
3. **Change direction** from right to left or from left to right
4. Repeat steps 2-3 until you can't move in the tree

**ZigZag length** = number of nodes visited - 1 (a single node has length 0)

### Examples

**Example 1:**
```
Input: root = [1,null,1,1,1,null,null,1,1,null,1,null,null,null,1]
Output: 3
Explanation: Longest ZigZag path (right -> left -> right) has 4 nodes, so length = 3
```

**Example 2:**
```
Input: root = [1,1,1,null,1,null,null,1,1,null,1]
Output: 4
Explanation: Longest ZigZag path (left -> right -> left -> right) has 5 nodes, so length = 4
```

**Example 3:**
```
Input: root = [1]
Output: 0
Explanation: Single node has zigzag length 0
```

### Constraints
- The number of nodes in the tree is in the range [1, 5 × 10⁴]
- 1 ≤ Node.val ≤ 100

---

## Observations

### Key Insights

1. **Direction Alternation**: A zigzag path must alternate directions. After going right, we must go left next, and vice versa.

2. **Path Independence**: A zigzag path can start at any node in the tree. We can't just find a path from root because the longest zigzag might start at an internal node.

3. **Multiple Starting Points**: We need to consider every node as a potential starting point for a zigzag path.

4. **State Tracking**: At each node, we need to track:
   - The current length of the zigzag path
   - The direction we just came from (left or right)
   - The next direction we can take

5. **DFS Traversal**: Since we need to explore all possible paths, DFS (depth-first search) is appropriate.

6. **Reset on Direction Change**: When we change direction at a node, we reset the count to 1 (counting the current node) rather than continuing the count. The exception is when we continue in the alternating direction.

---

## Solution Explanation

### Algorithm: DFS with Direction Tracking

The solution uses DFS to explore all possible zigzag paths starting from each node.

```python
class Solution:
    def longestZigZag(self, root: Optional[TreeNode]) -> int:
        longest = [0]  # Track the maximum zigzag length found
        
        def traversal(node: Optional[TreeNode], length: int, go_left: bool):
            # Base case: reached null node
            if not node:
                return
            
            # Update the longest zigzag length
            longest[0] = max(longest[0], length)
            
            # If we came from right (should go left next)
            if go_left:
                # Continue zigzag: go left and increment length
                traversal(node.left, length + 1, False)
                # Start new zigzag from right child
                traversal(node.right, 1, True)
            # If we came from left (should go right next)
            else:
                # Start new zigzag from left child
                traversal(node.left, 1, False)
                # Continue zigzag: go right and increment length
                traversal(node.right, length + 1, True)
        
        # Start from root, considering both directions
        traversal(root, 0, True)   # Imagine arriving from right, so go left first
        traversal(root, 0, False)  # Imagine arriving from left, so go right first
        
        return longest[0]
```

### How It Works

1. **Initial State**: We start with two DFS calls from the root:
   - `traversal(root, 0, True)`: Pretend we arrived from the right, so we go left first
   - `traversal(root, 0, False)`: Pretend we arrived from the left, so we go right first

2. **At Each Node**:
   - Update the global maximum with the current path length
   - If `go_left` is True (we should go left):
     - Recursively go to the left child with length + 1 and `go_left = False` (continue zigzag)
     - Recursively go to the right child with length = 1 and `go_left = True` (start new zigzag)
   - If `go_left` is False (we should go right):
     - Recursively go to the left child with length = 1 and `go_left = False` (start new zigzag)
     - Recursively go to the right child with length + 1 and `go_left = True` (continue zigzag)

3. **Length Tracking**:
   - When continuing in the zigzag direction: increment length (length + 1)
   - When switching to the opposite direction: reset length to 1

4. **Finding All Paths**: By making both calls from root and exploring all nodes, we consider every possible starting point and direction.

### Complexity Analysis

- **Time Complexity**: $O(n)$ where $n$ is the number of nodes. We visit each node multiple times (at most a constant factor) because we make two initial calls and explore each path.
- **Space Complexity**: $O(h)$ where $h$ is the height of the tree, due to the recursion stack depth in DFS.

### Example Walkthrough

For `[1,null,1,1,1,null,null,1,1,null,1]` with expected output 4:

```
Tree structure:
        1
        |
        1(right)
       / \
      1   1
        /   \
       1     1
         |
         1
```

When traversing:
- Starting from root going right (length 0)
- Right to node (length 1)
- Left to node (length 2)
- Right to node (length 3)
- Left to node (length 4)

Maximum length found = 4 ✓

# Tags
- Binary Tree
- DFS (Depth-First Search)
- Tree Traversal
- Path Problems
- Dynamic Programming


## Observations

## Solution

# Tags

