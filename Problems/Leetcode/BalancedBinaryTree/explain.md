## Problem

https://leetcode.com/problems/balanced-binary-tree/

```
Given a binary tree, determine if it is height-balanced.

Example 1:

Input: root = [3,9,20,null,null,15,7]
Output: true
Example 2:

Input: root = [1,2,2,3,3,null,null,4,4]
Output: false
Example 3:

Input: root = []
Output: true

Constraints:

The number of nodes in the tree is in the range [0, 5000].
-104 <= Node.val <= 104
```

## Observations

1. **Height-Balanced Definition**: A binary tree is height-balanced if the depth of the two subtrees of every node never differs by more than 1.

2. **Key Properties**:
   - An empty tree is considered balanced
   - For any node, the absolute difference between left and right subtree heights must be ≤ 1
   - This property must hold for ALL nodes in the tree, not just the root

3. **Recursive Nature**: To check if a tree is balanced, we need to:
   - Check if the current node satisfies the balance condition
   - Recursively check if both left and right subtrees are balanced

4. **Height Calculation**: We need a helper function to calculate the height of any subtree efficiently.

## Solution

### Approach: Recursive Height Checking

The solution uses a top-down recursive approach:

1. **Base Case**: If the root is `None` (empty tree), return `True` as it's balanced by definition.

2. **Height Helper Function**: 
   ```python
   def height(root: Optional[TreeNode]) -> int:
       if root == None:
           return 0
       return 1 + max(height(root.left), height(root.right))
   ```
   - Calculates the height of a subtree rooted at `root`
   - Returns 0 for empty nodes, otherwise 1 + maximum height of children

3. **Balance Check for Current Node**:
   ```python
   if abs(height(root.left) - height(root.right)) > 1:
       return False
   ```
   - Calculate heights of left and right subtrees
   - If absolute difference > 1, the tree is not balanced

4. **Recursive Check for Subtrees**:
   ```python
   check_left = self.isBalanced(root.left)
   check_right = self.isBalanced(root.right)
   return check_left and check_right
   ```
   - Recursively check if both left and right subtrees are balanced
   - Return `True` only if both subtrees are balanced

### Time Complexity: O(n²)
- For each node, we calculate the height of its subtrees (O(n) in worst case)
- We do this for all n nodes, resulting in O(n²)

### Space Complexity: O(h)
- Where h is the height of the tree due to recursion stack
- In worst case (skewed tree): O(n)
- In best case (balanced tree): O(log n)

### Example Walkthrough:
For tree `[3,9,20,null,null,15,7]`:
```
    3
   / \
  9  20
     / \
    15  7
```
1. Check root (3): |height(left=1) - height(right=2)| = 1 ≤ 1 ✓
2. Recursively check left subtree (9): leaf node, balanced ✓
3. Recursively check right subtree (20): |height(15) - height(7)| = 0 ≤ 1 ✓
4. Result: `True`

## Tags

binary tree, dfs