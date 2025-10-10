## Problem

https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/

```
Given two integer arrays inorder and postorder where inorder is the inorder traversal of a binary tree and postorder is the postorder traversal of the same tree, construct and return the binary tree.

Example 1:

Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
Output: [3,9,20,null,null,15,7]

Example 2:

Input: inorder = [-1], postorder = [-1]
Output: [-1]

Constraints:

1 <= inorder.length <= 3000
postorder.length == inorder.length
-3000 <= inorder[i], postorder[i] <= 3000
inorder and postorder consist of unique values.
Each value of postorder also appears in inorder.
inorder is guaranteed to be the inorder traversal of the tree.
postorder is guaranteed to be the postorder traversal of the tree.
```

## Observations

1. **Understanding Tree Traversals:**
   - **Inorder traversal**: Left → Root → Right
   - **Postorder traversal**: Left → Right → Root

2. **Key Insight - Root Identification:**
   - The **last element** in postorder is always the root of the tree
   - This is because postorder visits the root last

3. **Tree Partitioning Strategy:**
   - Once we identify the root from postorder, we can find its position in inorder
   - Everything to the **left** of root in inorder belongs to the **left subtree**
   - Everything to the **right** of root in inorder belongs to the **right subtree**

4. **Array Splitting Pattern:**
   - If left subtree has `n` elements in inorder, it will also have `n` elements in postorder
   - The first `n` elements in postorder belong to left subtree
   - The remaining elements (except the root) belong to right subtree

5. **Recursive Nature:**
   - Each subtree can be constructed using the same logic
   - Base case: empty array returns `None`

## Solution

**Algorithm Overview:**
The solution uses a divide-and-conquer approach by recursively partitioning the inorder and postorder arrays.

**Step-by-step Process:**

1. **Base Case**: If postorder is empty, return `None`

2. **Identify Root**: 
   ```python
   root_value = postorder[-1]  # Last element is always root
   ```

3. **Find Root Position in Inorder**:
   ```python
   root_idx = inorder.index(root_value)
   ```

4. **Partition Inorder Array**:
   ```python
   inorder_left = inorder[:root_idx]          # Left subtree elements
   inorder_right = inorder[root_idx + 1:]     # Right subtree elements
   ```

5. **Partition Postorder Array**:
   ```python
   postorder_left = postorder[:len(inorder_left)]                    # First n elements
   postorder_right = postorder[len(inorder_left):len(postorder) - 1] # Middle elements (excluding root)
   ```

6. **Recursive Construction**:
   ```python
   root = TreeNode(root_value)
   root.left = self.buildTree(inorder_left, postorder_left)
   root.right = self.buildTree(inorder_right, postorder_right)
   ```

**Time Complexity**: O(n²) in worst case due to `inorder.index()` calls
**Space Complexity**: O(n) for recursion stack and array slicing

**Example Walkthrough** with `inorder = [9,3,15,20,7]`, `postorder = [9,15,7,20,3]`:

1. Root = 3 (last in postorder)
2. Split inorder: [9] | 3 | [15,20,7]
3. Split postorder: [9] | [15,7,20] | 3
4. Recursively build left subtree from ([9], [9]) → TreeNode(9)
5. Recursively build right subtree from ([15,20,7], [15,7,20]) → TreeNode(20) with children 15,7

## Tags

binary tree