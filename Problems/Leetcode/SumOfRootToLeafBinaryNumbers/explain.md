## Problem

https://leetcode.com/problems/sum-of-root-to-leaf-binary-numbers/description/

```
You are given the root of a binary tree where each node has a value 0 or 1. Each root-to-leaf path represents a binary number starting with the most significant bit.

For example, if the path is 0 -> 1 -> 1 -> 0 -> 1, then this could represent 01101 in binary, which is 13.
For all leaves in the tree, consider the numbers represented by the path from the root to that leaf. Return the sum of these numbers.

The test cases are generated so that the answer fits in a 32-bits integer.

Example 1:

Input: root = [1,0,1,0,1,0,1]
Output: 22
Explanation: (100) + (101) + (110) + (111) = 4 + 5 + 6 + 7 = 22

Example 2:

Input: root = [0]
Output: 0

Constraints:

The number of nodes in the tree is in the range [1, 1000].
Node.val is 0 or 1.
```

## Observations

1. **Binary Tree Traversal**: Each root-to-leaf path represents a binary number where each node's value (0 or 1) contributes to building the binary representation.

2. **Path Building**: As we traverse from root to leaf, we build the binary string by concatenating node values. The most significant bit is at the root.

3. **Leaf Detection**: A node is a leaf when both `left` and `right` children are `None`. Only at leaves do we convert the accumulated binary string to decimal and add to the sum.

4. **Depth-First Search (DFS)**: The problem naturally fits a DFS approach since we need to explore all root-to-leaf paths completely.

5. **String vs Integer Approach**: The current solution builds binary strings and converts them to integers. An alternative approach would be to build the decimal value directly during traversal using bit manipulation.

## Solution

### Approach: DFS with String Building

**Algorithm:**
1. Use a recursive preorder traversal to visit all nodes
2. Build the binary string path from root to current node
3. When reaching a leaf node, convert the complete binary path to decimal
4. Add the decimal value to the running sum
5. Continue exploring all paths until all leaves are visited

**Key Components:**
- `bin_to_dec(s)`: Helper function to convert binary string to decimal using Python's `int(s, 2)`
- `preorder(root, temp)`: Recursive DFS function that builds path string `temp` 
- Base case: Return when `root` is `None`
- Leaf detection: Check if both children are `None`, then process the complete path
- Recursive calls: Continue DFS on both children with updated path string

**Time Complexity:** O(N) where N is the number of nodes, as we visit each node exactly once

**Space Complexity:** O(H) where H is the height of the tree due to:
- Recursion stack depth: O(H)
- String building: O(H) for the path string at each recursive call

**Example Walkthrough:**
For tree `[1,0,1,0,1,0,1]`:
- Path 1→0→0: Binary "100" = Decimal 4
- Path 1→0→1: Binary "101" = Decimal 5  
- Path 1→1→0: Binary "110" = Decimal 6
- Path 1→1→1: Binary "111" = Decimal 7
- Total sum: 4 + 5 + 6 + 7 = 22

### Alternative Optimized Approach:
Instead of building strings, we could calculate decimal values directly:
```python
def sumRootToLeaf(self, root):
    def dfs(node, val):
        if not node: return 0
        val = val * 2 + node.val  # Shift left and add current bit
        if not node.left and not node.right:  # Leaf
            return val
        return dfs(node.left, val) + dfs(node.right, val)
    
    return dfs(root, 0)
```

# Tags

- Binary Tree
- Depth-First Search (DFS)
- Tree Traversal
- Binary Numbers
- Recursion
- String Manipulation

