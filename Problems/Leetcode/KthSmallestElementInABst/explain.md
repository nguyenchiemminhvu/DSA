## Problem

https://leetcode.com/problems/kth-smallest-element-in-a-bst/description/

Given the root of a binary search tree and an integer `k`, return the kth smallest value (1-indexed) of all the values of the nodes in the tree.

**Example 1:**
```
Input: root = [3,1,4,null,2], k = 1
Output: 1
```

**Example 2:**
```
Input: root = [5,3,6,2,4,null,null,1], k = 3
Output: 3
```

**Constraints:**
- The number of nodes in the tree is n
- 1 <= k <= n <= 10^4
- 0 <= Node.val <= 10^4

**Follow-up:** If the BST is modified often (i.e., we can do insert and delete operations) and you need to find the kth smallest frequently, how would you optimize?

## Observations

1. **BST Property**: In a binary search tree, the left subtree contains all values smaller than the node, and the right subtree contains all values larger than the node.

2. **In-order Traversal**: An in-order traversal of a BST (left → node → right) produces values in ascending order. The kth value in this sequence is our answer.

3. **Subtree Counting Approach**: Instead of traversing the entire tree, we can use the count of nodes in the left subtree to determine which side the kth smallest element lies on:
   - If `count(left) == k - 1`, the current node is the kth smallest
   - If `count(left) > k - 1`, the answer is in the left subtree
   - If `count(left) < k - 1`, the answer is in the right subtree, and we adjust k accordingly

4. **Time Complexity Trade-offs**:
   - **In-order traversal**: O(n) time, O(h) space (where h is height)
   - **Subtree counting**: O(n) in worst case (unbalanced tree), but can be optimized with preprocessing

## Solution

### Approach 1: Subtree Counting (Given Solution)

**Algorithm:**
1. Count the number of nodes in the left subtree
2. Based on the count:
   - If `count == k - 1`: Current node is the answer
   - If `count >= k`: Recursively search left subtree with same k
   - Otherwise: Recursively search right subtree with adjusted k = `k - count - 1`

**Code:**
```python
class Solution:
    def kthSmallest(self, root: Optional[TreeNode], k: int) -> int:
        def count(root: Optional[TreeNode]) -> int:
            if not root:
                return 0
            return 1 + count(root.left) + count(root.right)
        
        nleft = count(root.left)
        if nleft == k - 1:
            return root.val
        if nleft > k - 1:
            return self.kthSmallest(root.left, k)
        return self.kthSmallest(root.right, k - nleft - 1)
```

**Time Complexity:** O(n) in worst case (counting all nodes in unbalanced tree)
**Space Complexity:** O(h) for recursion stack

**Example Walkthrough:**
```
Tree: [5,3,6,2,4,null,null,1], k = 3

        5
       / \
      3   6
     / \
    2   4
   /
  1

Step 1: At node 5, count left subtree = 3 (nodes: 1,2,3)
        Since count(3) > k-1(2), go left with k=3

Step 2: At node 3, count left subtree = 2 (nodes: 1,2)
        Since count(2) == k-1(2), return 3
```

### Approach 2: In-Order Traversal (Alternative)

**Algorithm:**
1. Perform in-order traversal (Left → Node → Right)
2. Count nodes as we visit them
3. Return the node when count reaches k

**Code:**
```python
class Solution:
    def kthSmallest(self, root: Optional[TreeNode], k: int) -> int:
        self.count = 0
        self.result = 0
        
        def inorder(node):
            if not node:
                return
            
            inorder(node.left)
            
            self.count += 1
            if self.count == k:
                self.result = node.val
                return
            
            inorder(node.right)
        
        inorder(root)
        return self.result
```

**Time Complexity:** O(k) in best case (balanced tree), O(n) worst case
**Space Complexity:** O(h) for recursion stack

### Approach 3: Iterator-based In-Order (Most Efficient)

**Algorithm:**
1. Use a stack to simulate in-order traversal
2. Pop k times to get the kth smallest element

**Code:**
```python
class Solution:
    def kthSmallest(self, root: Optional[TreeNode], k: int) -> int:
        stack = []
        current = root
        
        while True:
            # Go to leftmost node
            while current:
                stack.append(current)
                current = current.left
            
            # Current is None, pop from stack
            current = stack.pop()
            k -= 1
            
            if k == 0:
                return current.val
            
            # Visit right subtree
            current = current.right
```

**Time Complexity:** O(k) average case, O(n) worst case
**Space Complexity:** O(h) for stack

## Follow-up Solution: Frequent Queries with Modifications

For the follow-up where the BST is modified frequently and kth smallest is queried many times, the optimal approach is to **augment the BST nodes with rank/size information**:

**Enhanced Node Structure:**
```python
class AugmentedTreeNode:
    def __init__(self, val=0):
        self.val = val
        self.left = None
        self.right = None
        self.size = 1  # Number of nodes in subtree (including itself)
```

**kthSmallest Query:** O(h) - Navigate using size information
```python
def kthSmallest(self, root: AugmentedTreeNode, k: int) -> int:
    while root:
        left_size = root.left.size if root.left else 0
        if left_size == k - 1:
            return root.val
        elif left_size >= k:
            root = root.left
        else:
            k -= left_size + 1
            root = root.right
```

**Insert Operation:** O(h) - Update sizes along the path
```python
def insert(self, root: AugmentedTreeNode, val: int) -> AugmentedTreeNode:
    if not root:
        return AugmentedTreeNode(val)
    
    root.size += 1
    if val < root.val:
        root.left = self.insert(root.left, val)
    else:
        root.right = self.insert(root.right, val)
    
    return root
```

**Benefits:**
- Query time: O(h) instead of O(n)
- Insert/Delete time: O(h) with size updates
- Overall optimal for frequent operations on balanced BST

# Tags
- Binary Search Tree
- In-order Traversal
- Tree Recursion
- Count-based Navigation
- Subtree Size Counting

