## Problem

https://leetcode.com/problems/sum-root-to-leaf-numbers/description

You are given the root of a binary tree containing digits from 0 to 9 only.

Each root-to-leaf path in the tree represents a number. For example, the root-to-leaf path `1 -> 2 -> 3` represents the number `123`.

**Return the total sum of all root-to-leaf numbers.** Test cases are generated so that the answer will fit in a 32-bit integer.

A leaf node is a node with no children.

### Examples

**Example 1:**
```
Input: root = [1,2,3]
Output: 25
Explanation:
The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.
Therefore, sum = 12 + 13 = 25.
```

**Example 2:**
```
Input: root = [4,9,0,5,1]
Output: 1026
Explanation:
The root-to-leaf path 4->9->5 represents the number 495.
The root-to-leaf path 4->9->1 represents the number 491.
The root-to-leaf path 4->0 represents the number 40.
Therefore, sum = 495 + 491 + 40 = 1026.
```

### Constraints

- The number of nodes in the tree is in the range `[1, 1000]`.
- `0 <= Node.val <= 9`
- The depth of the tree will not exceed `10`.

## Observations

1. **Path Construction:** We need to traverse from root to each leaf node, accumulating digits to form complete numbers.

2. **Root-to-Leaf Requirement:** Only paths that reach a leaf (node with no children) are valid. We cannot stop at internal nodes.

3. **Digit Accumulation:** As we traverse down the tree, each new digit is appended to form the number. For example, if the current path value is "12" and we visit a node with value 3, the new path value becomes "123".

4. **DFS is Natural:** This is a perfect use case for depth-first search (DFS) because:
   - We need to explore all paths from root to leaves
   - We naturally traverse down a single path, then backtrack
   - We can accumulate the path string as a parameter

5. **Base Cases:**
   - If we reach a `None` node, return (invalid path)
   - If we reach a leaf node (both children are `None`), add the complete number to our result

6. **Number Accumulation:** We can either:
   - Build numbers as strings and convert to int at the leaf (the given solution)
   - Build numbers as integers using arithmetic: `current_num * 10 + node.val`

## Solution

### Approach: DFS with String Path Building

The solution uses **Depth-First Search (DFS)** to traverse all root-to-leaf paths in the tree.

**Key Idea:**
- Maintain a string `s` that represents the path from root to the current node
- When we reach a leaf node, convert the complete path string to an integer and add it to the result
- Use a mutable list `res = [0]` to store the result (allows modification in nested function scope)

**Algorithm:**
1. Initialize `res = [0]` to accumulate the sum
2. Define a DFS helper function that takes:
   - `root`: current node
   - `s`: string representation of the path from root to current node
3. Base cases:
   - If `root` is `None`, return (no node to process)
   - If `root` is a leaf (no left and right children), add `int(s + str(root.val))` to `res[0]`
4. Recursive cases:
   - Recursively visit left child with updated path string
   - Recursively visit right child with updated path string
5. Start DFS from root with empty string `''`

### Code Implementation

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def sumNumbers(self, root: Optional[TreeNode]) -> int:
        res = [0]
        
        def dfs(root: Optional[TreeNode], s: str):
            if not root:
                return
            
            # Check if we reached a leaf node
            if not root.left and not root.right:
                res[0] += int(s + str(root.val))
                return
            
            # Recursively traverse left and right subtrees
            dfs(root.left, s + str(root.val))
            dfs(root.right, s + str(root.val))
        
        dfs(root, '')
        return res[0]
```

### Complexity Analysis

- **Time Complexity:** $O(n)$
  - We visit each node exactly once
  - At each node, we perform string concatenation which is $O(\text{depth})$ in worst case
  - Total: $O(n \times \text{depth})$, but since depth ≤ 10 (given constraint), effectively $O(n)$

- **Space Complexity:** $O(h)$
  - Recursion call stack depth is at most the height `h` of the tree
  - Given constraint: depth ≤ 10, so $O(h) = O(10) = O(1)$ practically
  - We create new strings during recursion with $O(h)$ characters per string

### Alternative Solution: Numeric Path Building

A more efficient approach avoids string concatenation:

```python
class Solution:
    def sumNumbers(self, root: Optional[TreeNode]) -> int:
        res = [0]
        
        def dfs(root: Optional[TreeNode], num: int):
            if not root:
                return
            
            # Update number by appending current digit
            num = num * 10 + root.val
            
            # Check if we reached a leaf node
            if not root.left and not root.right:
                res[0] += num
                return
            
            # Recursively traverse left and right subtrees
            dfs(root.left, num)
            dfs(root.right, num)
        
        dfs(root, 0)
        return res[0]
```

**Advantages of numeric approach:**
- Avoids string concatenation overhead
- More intuitive mathematically: $\text{num} = \text{num} \times 10 + \text{digit}$
- Slightly better space complexity (no string objects created)

### Examples Walkthrough

**Example 1:** `root = [1,2,3]`
```
       1
      / \
     2   3

Path 1→2 (leaf): "12" → 12
Path 1→3 (leaf): "13" → 13
Sum: 12 + 13 = 25
```

**Example 2:** `root = [4,9,0,5,1]`
```
         4
        / \
       9   0
      / \
     5   1

Path 4→9→5 (leaf): "495" → 495
Path 4→9→1 (leaf): "491" → 491
Path 4→0 (leaf):   "40"  → 40
Sum: 495 + 491 + 40 = 1026
```

# Tags

- Binary Tree
- Depth-First Search (DFS)
- Tree Traversal
- Path Sum

