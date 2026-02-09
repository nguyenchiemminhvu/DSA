## Problem

https://leetcode.com/problems/balance-a-binary-search-tree/description/

```
Given the root of a binary search tree, return a balanced binary search tree with the same node values. 
If there is more than one answer, return any of them.

A binary search tree is balanced if the depth of the two subtrees of every node never differs by more than 1.

Example 1:
Input: root = [1,null,2,null,3,null,4,null,null]
Output: [2,1,3,null,null,null,4]
Explanation: This is not the only correct answer, [3,1,4,null,2] is also correct.

Example 2:
Input: root = [2,1,3]
Output: [2,1,3]

Constraints:
- The number of nodes in the tree is in the range [1, 10^4].
- 1 <= Node.val <= 10^5
```

## Observations

1. **BST Property**: In a Binary Search Tree, an in-order traversal yields nodes in sorted order
2. **Unbalanced to Balanced**: The input BST might be skewed (like a linked list in worst case), causing O(n) operations
3. **Sorted Array to Balanced BST**: Building a balanced BST from a sorted array is a classic problem
4. **Middle Element as Root**: Choosing the middle element of a sorted array as root ensures balance
5. **Recursive Construction**: Each subtree can be built recursively using the same approach

## Solution

### Approach: In-order Traversal + Divide and Conquer

The solution consists of two main phases:

**Phase 1: Extract Sorted Values**
- Perform an in-order traversal of the BST to get all node values in sorted order
- Time: O(n), Space: O(n) for the array

**Phase 2: Build Balanced BST**
- Use the sorted array to construct a balanced BST recursively
- Always pick the middle element as root to ensure balance
- Recursively build left subtree from left half and right subtree from right half

### Algorithm Steps:

1. **In-order Traversal (DFS)**:
   ```
   traversal(root, arr):
       if root is null: return
       traversal(root.left, arr)
       arr.append(root.val)
       traversal(root.right, arr)
   ```

2. **Build Balanced Tree**:
   ```
   build_tree(left, right):
       if left > right: return null
       mid = left + (right - left) // 2
       root = TreeNode(arr[mid])
       root.left = build_tree(left, mid - 1)
       root.right = build_tree(mid + 1, right)
       return root
   ```

### Why This Works:

- **Balance Guarantee**: By always choosing the middle element, we ensure that the left and right subtrees have approximately equal number of nodes (differ by at most 1)
- **Height Balance**: For a balanced BST with n nodes, height = O(log n)
- **BST Property Maintained**: Since we use in-order traversal values and build from sorted array, BST property is preserved

### Complexity Analysis:

- **Time Complexity**: O(n)
  - In-order traversal: O(n)
  - Building tree: O(n) - each node is created exactly once
  
- **Space Complexity**: O(n)
  - Array to store values: O(n)
  - Recursion stack: O(log n) for balanced tree, O(n) for traversal in worst case
  - Overall: O(n)

### Example Walkthrough:

Input: [1,null,2,null,3,null,4] (skewed right)
```
   1
    \
     2
      \
       3
        \
         4
```

Step 1: In-order traversal → arr = [1, 2, 3, 4]

Step 2: Build balanced tree:
- Pick mid = 2 (index 1), root = 2
- Left subtree: arr[0:0] → node 1
- Right subtree: arr[2:3] → root = 3, right child = 4

Result:
```
     2
    / \
   1   3
        \
         4
```

### Python Implementation:
```python
class Solution:
    def balanceBST(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        def traversal(root: Optional[TreeNode], arr: List[int]) -> None:
            if not root:
                return
            traversal(root.left, arr)
            arr.append(root.val)
            traversal(root.right, arr)
        
        arr = []
        traversal(root, arr)

        def build_tree(left: int, right: int) -> Optional[TreeNode]:
            if left > right:
                return None
            
            mid = left + (right - left) // 2
            root = TreeNode(arr[mid])
            root.left = build_tree(left, mid - 1)
            root.right = build_tree(mid + 1, right)
            return root
        
        return build_tree(0, len(arr) - 1)
```

# Tags
`Binary Search Tree` `Tree` `Recursion` `Divide and Conquer` `In-order Traversal` `Balanced Tree` `Medium`

