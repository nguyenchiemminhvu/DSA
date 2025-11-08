## Problem

https://leetcode.com/problems/merge-two-binary-trees/description/

```
You are given two binary trees root1 and root2.

Imagine that when you put one of them to cover the other, some nodes of the two trees are overlapped while the others are not. You need to merge the two trees into a new binary tree. The merge rule is that if two nodes overlap, then sum node values up as the new value of the merged node. Otherwise, the NOT null node will be used as the node of the new tree.

Return the merged tree.

Note: The merging process must start from the root nodes of both trees.

Example 1:

Input: root1 = [1,3,2,5], root2 = [2,1,3,null,4,null,7]
Output: [3,4,5,5,4,null,7]

Example 2:

Input: root1 = [1], root2 = [1,2]
Output: [2,2]

Constraints:

The number of nodes in both trees is in the range [0, 2000].
-104 <= Node.val <= 104
```

## Observations

1. **Problem Understanding**: We need to merge two binary trees by overlapping them and summing the values of overlapping nodes.

2. **Base Cases**: 
   - If both nodes are null, return null
   - If one node is null and the other isn't, use the non-null node's value

3. **Recursive Nature**: The problem has a natural recursive structure - we can solve it by merging the left subtrees and right subtrees separately.

4. **Tree Construction**: We need to create a new tree rather than modifying existing trees.

5. **Traversal Pattern**: We traverse both trees simultaneously using a preorder approach (process current node, then left, then right).

## Solution

The solution uses a recursive approach to merge the two binary trees:

### Algorithm:
1. **Base Case**: If both root1 and root2 are null, return null (no nodes to merge)

2. **Create New Node**: Create a new TreeNode for the merged result

3. **Calculate Value**: Sum the values of both nodes, treating null nodes as having value 0:
   - `(root1.val if root1 else 0) + (root2.val if root2 else 0)`

4. **Recursive Calls**: Recursively merge the left and right subtrees:
   - Left subtree: `mergeTrees(root1.left if root1 else None, root2.left if root2 else None)`
   - Right subtree: `mergeTrees(root1.right if root1 else None, root2.right if root2 else None)`

### Time Complexity: O(min(m, n))
- Where m and n are the number of nodes in root1 and root2 respectively
- We traverse until we reach the end of the smaller tree

### Space Complexity: O(min(m, n))
- Due to the recursive call stack depth
- In the worst case (balanced trees), this would be O(log(min(m, n)))
- In the worst case (skewed trees), this would be O(min(m, n))

### Example Walkthrough:
```
Tree1:     Tree2:     Result:
   1          2          3
  / \        / \        / \
 3   2      1   3      4   5
/          /     \    /     \
5         4       7  5       7
```

The algorithm processes each position and sums the values where both trees have nodes, or uses the single value where only one tree has a node.

# Tags

- Binary Tree
- Recursion
- Tree Traversal
- Depth-First Search (DFS)

