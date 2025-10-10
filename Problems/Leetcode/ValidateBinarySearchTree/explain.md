## Problem

https://leetcode.com/problems/validate-binary-search-tree/description/

```
Given the root of a binary tree, determine if it is a valid binary search tree (BST).

A valid BST is defined as follows:

The left subtree of a node contains only nodes with keys strictly less than the node's key.
The right subtree of a node contains only nodes with keys strictly greater than the node's key.
Both the left and right subtrees must also be binary search trees.

Example 1:

Input: root = [2,1,3]
Output: true

Example 2:

Input: root = [5,1,4,null,null,3,6]
Output: false
Explanation: The root node's value is 5 but its right child's value is 4.

Constraints:

The number of nodes in the tree is in the range [1, 104].
-231 <= Node.val <= 231 - 1
```

## Observations

1. **BST Property**: A valid BST has a crucial property - when traversed using in-order traversal (left → root → right), the values should be in strictly increasing order.

2. **Key Insight**: Instead of checking parent-child relationships at each node, we can leverage the in-order traversal property to validate the entire tree.

3. **Edge Cases**: 
   - Empty tree or single node is considered valid
   - Duplicate values are not allowed (strictly less/greater requirement)
   - Need to handle negative numbers and edge values within the constraint range

4. **Approach Choice**: The in-order traversal approach is intuitive and straightforward, though it requires O(n) extra space for storing the traversal result.

## Solution

**Algorithm**: In-order Traversal with Validation

The solution uses a two-step approach:

1. **Step 1 - In-order Traversal**: Perform an in-order traversal of the binary tree to collect all node values in the order they would appear in a valid BST.

2. **Step 2 - Validation**: Check if the collected values are in strictly increasing order.

**How it works**:
- The `inorder` function recursively traverses the tree in left-root-right order
- All node values are collected in the `arr` list
- If the tree is a valid BST, `arr` will contain values in strictly increasing order
- The validation loop checks that each element is strictly greater than the previous one

**Time Complexity**: O(n) where n is the number of nodes
- O(n) for in-order traversal
- O(n) for validation loop

**Space Complexity**: O(n) 
- O(n) for storing the traversal result
- O(h) for recursion stack where h is the height of the tree

**Alternative Approaches**:
1. **Optimized In-order**: Keep track of the previous value during traversal (O(1) extra space)
2. **Range Validation**: Pass valid range (min, max) to each recursive call
3. **Iterative In-order**: Use a stack for iterative traversal

## Tags

binary search tree, dfs