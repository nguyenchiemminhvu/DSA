## Problem

https://leetcode.com/problems/same-tree/

```
Given the roots of two binary trees p and q, write a function to check if they are the same or not.

Two binary trees are considered the same if they are structurally identical, and the nodes have the same value.

Example 1:

Input: p = [1,2,3], q = [1,2,3]
Output: true

Example 2:

Input: p = [1,2], q = [1,null,2]
Output: false

Example 3:

Input: p = [1,2,1], q = [1,1,2]
Output: false

Constraints:

The number of nodes in both trees is in the range [0, 100].
-104 <= Node.val <= 104
```

## Observations

1. **Base Cases**: Two trees are the same if:
   - Both are empty (None)
   - Both have the same structure and same values at corresponding positions

2. **Termination Conditions**: Two trees are different if:
   - One is empty while the other is not
   - They have different values at corresponding nodes
   - Their left or right subtrees are different

3. **Recursive Nature**: The problem has optimal substructure - if two trees are the same, then their left subtrees must be the same AND their right subtrees must be the same.

4. **Time Complexity**: O(min(m, n)) where m and n are the number of nodes in the two trees. In the worst case, we need to visit all nodes of the smaller tree.

5. **Space Complexity**: O(min(m, n)) due to the recursive call stack depth, which in the worst case (skewed tree) equals the height of the smaller tree.

## Solution

1. **Base Case - Both Empty**: If both nodes are None, the trees are identical at this position.

2. **Mismatch Cases**: If one node is None while the other isn't, the trees have different structures.

3. **Value Comparison**: If both nodes exist but have different values, the trees are different.

4. **Recursive Check**: If the current nodes are valid and have the same value, recursively check:
   - Left subtrees of both nodes
   - Right subtrees of both nodes
   - Both conditions must be true (AND operation)

**Key Insights:**
- The recursive structure naturally handles the tree traversal
- Early termination when differences are found improves efficiency
- The AND operation ensures both subtrees must match for the trees to be identical

## Tags

binary tree