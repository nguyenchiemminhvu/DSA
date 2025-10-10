## Problem

https://leetcode.com/problems/insert-into-a-binary-search-tree/

```
You are given the root node of a binary search tree (BST) and a value to insert into the tree. Return the root node of the BST after the insertion. It is guaranteed that the new value does not exist in the original BST.

Notice that there may exist multiple valid ways for the insertion, as long as the tree remains a BST after insertion. You can return any of them.

Example 1:

Input: root = [4,2,7,1,3], val = 5
Output: [4,2,7,1,3,5]
Explanation: Another accepted tree is:

Example 2:

Input: root = [40,20,60,10,30,50,70], val = 25
Output: [40,20,60,10,30,50,70,null,null,25]
Example 3:

Input: root = [4,2,7,1,3,null,null,null,null,null,null], val = 5
Output: [4,2,7,1,3,5]

Constraints:

The number of nodes in the tree will be in the range [0, 104].
-108 <= Node.val <= 108
All the values Node.val are unique.
-108 <= val <= 108
It's guaranteed that val does not exist in the original BST.
```

## Observations

1. **BST Property**: In a binary search tree, for any node:
   - All values in the left subtree are smaller than the node's value
   - All values in the right subtree are greater than the node's value

2. **Insertion Location**: Since the problem guarantees that the value to insert doesn't already exist, we need to find the correct position where the BST property is maintained.

3. **Recursive Nature**: The insertion can be done recursively by comparing the value with current node and deciding whether to go left or right.

4. **Base Cases**: 
   - If we reach a null node, that's where we insert the new node
   - If the value equals the current node's value (though guaranteed not to happen), we can return the node as-is

5. **Multiple Valid Solutions**: The problem states there can be multiple valid ways to insert, as long as BST property is maintained.

## Solution

**Approach: Recursive Insertion**

The solution uses a recursive approach that follows the BST property to find the insertion point:

```python
def insertIntoBST(self, root: Optional[TreeNode], val: int) -> Optional[TreeNode]:
    if root == None:
        return TreeNode(val)
    if val == root.val:
        return root
    if val < root.val:
        root.left = self.insertIntoBST(root.left, val)
    else:
        root.right = self.insertIntoBST(root.right, val)
    return root
```

**Algorithm Explanation:**

1. **Base Case - Empty Tree**: If `root` is `None`, we've found the insertion point. Create and return a new `TreeNode` with the given value.

2. **Duplicate Value Check**: If `val == root.val`, return the current root (though this case won't occur per problem constraints).

3. **Left Subtree**: If `val < root.val`, the value should be inserted in the left subtree. Recursively call `insertIntoBST` on `root.left` and assign the result back to `root.left`.

4. **Right Subtree**: If `val > root.val`, the value should be inserted in the right subtree. Recursively call `insertIntoBST` on `root.right` and assign the result back to `root.right`.

5. **Return Root**: After insertion, return the root to maintain the tree structure.

**Time Complexity**: O(h) where h is the height of the tree
- Best case (balanced tree): O(log n)
- Worst case (skewed tree): O(n)

**Space Complexity**: O(h) due to recursion stack
- Best case: O(log n)  
- Worst case: O(n)

**Key Insights:**
- The algorithm maintains BST property by following the comparison-based navigation
- The recursive structure naturally handles the tree reconstruction after insertion
- No additional tree balancing is required as per problem requirements

## Tags

binary search tree, recursion, dfs