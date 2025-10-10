## Problem

https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

```
Given two integer arrays preorder and inorder where preorder is the preorder traversal of a binary tree and inorder is the inorder traversal of the same tree, construct and return the binary tree.

Example 1:

Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
Output: [3,9,20,null,null,15,7]

Example 2:

Input: preorder = [-1], inorder = [-1]
Output: [-1]

Constraints:

1 <= preorder.length <= 3000
inorder.length == preorder.length
-3000 <= preorder[i], inorder[i] <= 3000
preorder and inorder consist of unique values.
Each value of inorder also appears in preorder.
preorder is guaranteed to be the preorder traversal of the tree.
inorder is guaranteed to be the inorder traversal of the tree.
```

## Observations

1. **Preorder traversal pattern**: Root → Left → Right
   - The first element in preorder is always the root of the current subtree
   
2. **Inorder traversal pattern**: Left → Root → Right
   - Elements to the left of root in inorder array belong to left subtree
   - Elements to the right of root in inorder array belong to right subtree
   
3. **Key insight**: We can use preorder to identify the root, and inorder to determine which elements belong to left vs right subtrees

4. **Recursive structure**: Once we split the arrays correctly, we can recursively build left and right subtrees

5. **Array splitting logic**:
   - Find root position in inorder array
   - Left subtree has `root_idx` elements  
   - Right subtree has `len(inorder) - root_idx - 1` elements
   - Split preorder accordingly: skip root, take next `left_size` elements for left subtree, remaining for right subtree

## Solution

### Approach: Divide and Conquer with Recursive Array Splitting

The solution uses a divide-and-conquer approach that leverages the properties of preorder and inorder traversals:

**Algorithm Steps:**
1. **Base case**: If preorder is empty, return None
2. **Identify root**: First element in preorder is the current subtree's root
3. **Find root position**: Locate root value in inorder array to determine subtree boundaries
4. **Split inorder**: Elements before root index → left subtree, elements after → right subtree  
5. **Split preorder**: Skip root, take `len(left_inorder)` elements for left subtree, remaining for right subtree
6. **Recurse**: Build left and right subtrees using respective subarrays
7. **Construct**: Create TreeNode with root value and attach left/right subtrees

**Example walkthrough** with `preorder = [3,9,20,15,7]`, `inorder = [9,3,15,20,7]`:

```
Step 1: root = 3 (preorder[0])
        root_idx = 1 (position of 3 in inorder)
        
Step 2: Split arrays:
        inorder_left = [9]           inorder_right = [15,20,7]
        preorder_left = [9]          preorder_right = [20,15,7]
        
Step 3: Recursively build:
        left subtree from ([9], [9]) → TreeNode(9)
        right subtree from ([20,15,7], [15,20,7]) → TreeNode(20) with children
```

**Time Complexity**: O(n²) due to `inorder.index()` in each recursive call  
**Space Complexity**: O(n) for recursion stack and array slicing

**Optimization potential**: Use a hashmap to store inorder indices for O(n) time complexity.

## Tags

binary tree