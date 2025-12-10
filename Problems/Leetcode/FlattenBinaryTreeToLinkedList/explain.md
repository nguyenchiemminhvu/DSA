## Problem

https://leetcode.com/problems/flatten-binary-tree-to-linked-list/description/

Given the root of a binary tree, flatten the tree into a "linked list":
- The "linked list" should use the same TreeNode class where the right child pointer points to the next node in the list and the left child pointer is always null.
- The "linked list" should be in the same order as a pre-order traversal of the binary tree.

**Example 1:**
```
Input: root = [1,2,5,3,4,null,6]
       1
      / \
     2   5
    / \   \
   3   4   6

Output: [1,null,2,null,3,null,4,null,5,null,6]
        1
         \
          2
           \
            3
             \
              4
               \
                5
                 \
                  6
```

**Example 2:**
```
Input: root = []
Output: []
```

**Example 3:**
```
Input: root = [0]
Output: [0]
```

**Constraints:**
- The number of nodes in the tree is in the range [0, 2000]
- -100 <= Node.val <= 100

**Follow up:** Can you flatten the tree in-place (with O(1) extra space)?

## Observations

1. **Pre-order Traversal Pattern**: The flattened tree should follow pre-order traversal order (root → left → right)

2. **In-place Modification**: We need to modify the tree in-place without using extra space for storing nodes

3. **Key Insight - Morris Traversal Approach**: 
   - For each node with a left subtree, we need to find the rightmost node (predecessor) in that left subtree
   - Connect the predecessor's right pointer to the current node's right subtree
   - Move the left subtree to the right
   - Set left pointer to null

4. **Why This Works**:
   - In pre-order, after visiting a node, we visit its entire left subtree before the right subtree
   - By finding the rightmost node in the left subtree and connecting it to the original right subtree, we maintain the correct pre-order sequence
   - Moving left subtree to right ensures we process nodes in the correct order

5. **Space Complexity**: O(1) - only using pointers, no recursion stack or auxiliary data structures

6. **Time Complexity**: O(n) - each node is visited at most twice (once as current, once when finding predecessor)

## Solution

### Approach: Morris Traversal (In-place)

The algorithm uses a modified Morris traversal to flatten the tree:

1. **Iterate through nodes** starting from root using the right pointer
2. **For each node with a left child**:
   - Find the predecessor (rightmost node in left subtree)
   - Connect predecessor's right to current node's right subtree
   - Move left subtree to right
   - Set left pointer to null
3. **Move to next node** (which is now in the right pointer)

**Step-by-step example for tree [1,2,5,3,4,null,6]:**

```
Initial:        Step 1 (at node 1):    Step 2 (at node 2):    Final:
    1               1                      1                    1
   / \               \                      \                    \
  2   5               2                      2                    2
 / \   \             / \                      \                    \
3   4   6           3   4                      3                    3
                         \                      \                    \
                          5                      4                    4
                           \                      \                    \
                            6                      5                    5
                                                    \                    \
                                                     6                    6
```

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def flatten(self, root: Optional[TreeNode]) -> None:
        """
        Do not return anything, modify root in-place instead.
        """
        def get_predecessor(root: Optional[TreeNode]) -> Optional[TreeNode]:
            """Find the rightmost node in the left subtree"""
            if not root or not root.left:
                return root
            p = root.left
            while p and p.right:
                p = p.right
            return p
        
        cur = root
        while cur:
            # If current node has a left child
            if cur.left:
                # Find the rightmost node in left subtree
                pred = get_predecessor(cur)
                # Connect it to current's right subtree
                pred.right = cur.right
                # Move left subtree to right
                cur.right = cur.left
                # Set left to null
                cur.left = None
            # Move to next node
            cur = cur.right
```

**Complexity Analysis:**
- **Time**: O(n) - each node visited at most twice
- **Space**: O(1) - only using pointers, no extra space

**Alternative Approach (Recursive - O(n) space):**
```python
class Solution:
    def flatten(self, root: Optional[TreeNode]) -> None:
        def flatten_helper(node):
            if not node:
                return None
            
            # If leaf node, return itself
            if not node.left and not node.right:
                return node
            
            # Recursively flatten left and right subtrees
            left_tail = flatten_helper(node.left)
            right_tail = flatten_helper(node.right)
            
            # If there's a left subtree, shuffle connections
            if left_tail:
                left_tail.right = node.right
                node.right = node.left
                node.left = None
            
            # Return the tail of flattened tree
            return right_tail if right_tail else left_tail
        
        flatten_helper(root)
```

# Tags

`Binary Tree` `Depth-First Search` `Morris Traversal` `In-place Algorithm` `Pre-order Traversal` `Tree Manipulation`

