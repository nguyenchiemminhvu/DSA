## Problem

https://leetcode.com/problems/minimum-absolute-difference-in-bst/description/

```
Given the root of a Binary Search Tree (BST), return the minimum absolute difference between the values of any two different nodes in the tree.

Example 1:

Input: root = [4,2,6,1,3]
Output: 1

Example 2:

Input: root = [1,0,48,null,null,12,49]
Output: 1

Constraints:

The number of nodes in the tree is in the range [2, 104].
0 <= Node.val <= 105

Note: This question is the same as 783: https://leetcode.com/problems/minimum-distance-between-bst-nodes/
```

## Observations

1. **BST Property**: In a Binary Search Tree, an in-order traversal visits nodes in sorted (ascending) order.

2. **Minimum Difference**: Since we need the minimum absolute difference between any two nodes, and in-order traversal gives us sorted values, the minimum difference must occur between adjacent elements in this sorted sequence.

3. **Why Adjacent Elements**: In a sorted array, the minimum difference between any two elements will always be between consecutive elements. This is because if we have three elements a < b < c, then |c - a| ≥ |b - a| and |c - a| ≥ |c - b|.

4. **Time Complexity**: O(n) for traversal + O(n) for finding minimum = O(n) overall.

5. **Space Complexity**: O(n) for storing all node values + O(h) for recursion stack where h is tree height.



## Solution

### Approach: In-Order Traversal + Linear Scan

The solution uses a two-step approach:

1. **In-Order Traversal**: Perform in-order traversal to get all node values in sorted order
2. **Find Minimum Difference**: Scan through the sorted array to find the minimum difference between consecutive elements

### Code Walkthrough:

```python
def getMinimumDifference(self, root: Optional[TreeNode]) -> int:
    def inorder(root: Optional[TreeNode], arr: List[int]) -> None:
        if root == None:
            return
        inorder(root.left, arr)    # Visit left subtree
        arr.append(root.val)       # Process current node
        inorder(root.right, arr)   # Visit right subtree
    
    arr = []
    inorder(root, arr)             # Get sorted array of all values
    res = float('inf')
    for i in range(1, len(arr)):   # Compare consecutive elements
        res = min(res, arr[i] - arr[i - 1])
    return res
```

### Step-by-Step Execution:

For BST `[4,2,6,1,3]`:
```
     4
   /   \
  2     6
 / \
1   3
```

1. In-order traversal: `1 → 2 → 3 → 4 → 6`
2. Array: `[1, 2, 3, 4, 6]`
3. Differences: `2-1=1, 3-2=1, 4-3=1, 6-4=2`
4. Minimum: `1`

### Alternative Optimized Approach:

We can optimize space complexity by tracking the minimum difference during traversal:

```python
def getMinimumDifference(self, root: Optional[TreeNode]) -> int:
    self.min_diff = float('inf')
    self.prev = None
    
    def inorder(node):
        if not node:
            return
        
        inorder(node.left)
        
        if self.prev is not None:
            self.min_diff = min(self.min_diff, node.val - self.prev)
        self.prev = node.val
        
        inorder(node.right)
    
    inorder(root)
    return self.min_diff
```

This reduces space complexity from O(n) to O(h) where h is the height of the tree.

### Complexity Analysis:

**Given Solution:**
- Time: O(n) - visit each node once + linear scan
- Space: O(n) - store all values + O(h) recursion stack

**Optimized Solution:**
- Time: O(n) - visit each node once
- Space: O(h) - only recursion stack space needed

# Tags

- Binary Search Tree
- Tree Traversal  
- In-Order Traversal
- Two Pointers
- Array Processing

