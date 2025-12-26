# Maximum Binary Tree

## Problem

https://leetcode.com/problems/maximum-binary-tree/description/

You are given an integer array `nums` with no duplicates. A **maximum binary tree** can be built recursively from `nums` using the following algorithm:

1. Create a root node whose value is the maximum value in `nums`.
2. Recursively build the left subtree on the subarray prefix to the left of the maximum value.
3. Recursively build the right subtree on the subarray suffix to the right of the maximum value.

Return the maximum binary tree built from `nums`.

### Example 1:
```
Input: nums = [3,2,1,6,0,5]
Output: [6,3,5,null,2,0,null,null,1]

Explanation: The recursive calls are as follow:
- The largest value in [3,2,1,6,0,5] is 6. Left prefix is [3,2,1] and right suffix is [0,5].
    - The largest value in [3,2,1] is 3. Left prefix is [] and right suffix is [2,1].
        - Empty array, so no child.
        - The largest value in [2,1] is 2. Left prefix is [] and right suffix is [1].
            - Empty array, so no child.
            - Only one element, so child is a node with value 1.
    - The largest value in [0,5] is 5. Left prefix is [0] and right suffix is [].
        - Only one element, so child is a node with value 0.
        - Empty array, so no child.
```

### Example 2:
```
Input: nums = [3,2,1]
Output: [3,null,2,null,1]
```

### Constraints:
- `1 <= nums.length <= 1000`
- `0 <= nums[i] <= 1000`
- All integers in `nums` are unique.

---

## Observations

1. **Recursive Structure**: The problem naturally lends itself to a recursive solution since we need to build subtrees using the same algorithm.

2. **Maximum Element as Root**: At each step, the maximum element in the current subarray becomes the root node, which guarantees the "maximum binary tree" property.

3. **Array Partitioning**: Once we find the maximum element at index `i`, the array is naturally divided into:
   - Left subarray: `[left, i-1]` → becomes the left subtree
   - Right subarray: `[i+1, right]` → becomes the right subtree

4. **Base Case**: When `left > right`, the subarray is empty, so we return `None` (null).

5. **Time Complexity Consideration**: 
   - Finding the maximum in each recursive call takes O(n)
   - In the worst case (sorted array), we have O(n) recursive calls
   - Overall: **O(n²)** time complexity
   - Can be optimized to O(n) using a monotonic stack approach

6. **Space Complexity**: 
   - Recursion depth can be O(n) in the worst case
   - Overall: **O(n)** space complexity

---

## Solution

### Approach: Divide and Conquer with Recursion

The solution uses a recursive helper function `build_tree(left, right)` that constructs a maximum binary tree from the subarray `nums[left:right+1]`.

**Algorithm Steps:**

1. **Base Case**: If `left > right`, the subarray is empty, return `None`.

2. **Find Maximum**: Iterate through the subarray `[left, right]` to find the index and value of the maximum element.

3. **Create Root**: Create a new `TreeNode` with the maximum value.

4. **Recursively Build Subtrees**:
   - **Left subtree**: Build from subarray `[left, max_idx - 1]`
   - **Right subtree**: Build from subarray `[max_idx + 1, right]`

5. **Return Root**: Return the constructed node.

### Code Implementation

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def constructMaximumBinaryTree(self, nums: List[int]) -> Optional[TreeNode]:
        def build_tree(left: int, right: int) -> Optional[TreeNode]:
            # Base case: empty subarray
            if left > right:
                return None
            
            # Find the maximum element and its index
            max_idx = -1
            max_val = -1
            for i in range(left, right + 1):
                if max_val < nums[i]:
                    max_val = nums[i]
                    max_idx = i
            
            # Create root node with maximum value
            root = TreeNode(nums[max_idx])
            
            # Recursively build left and right subtrees
            root.left = build_tree(left, max_idx - 1)
            root.right = build_tree(max_idx + 1, right)
            
            return root
        
        # Start building from the entire array
        return build_tree(0, len(nums) - 1)
```

### Example Trace: `nums = [3,2,1,6,0,5]`

```
build_tree(0, 5) -> nums[0:6] = [3,2,1,6,0,5]
    max_idx = 3, max_val = 6
    root = TreeNode(6)
    
    root.left = build_tree(0, 2) -> nums[0:3] = [3,2,1]
        max_idx = 0, max_val = 3
        root = TreeNode(3)
        
        root.left = build_tree(0, -1) -> None
        
        root.right = build_tree(1, 2) -> nums[1:3] = [2,1]
            max_idx = 1, max_val = 2
            root = TreeNode(2)
            
            root.left = build_tree(1, 0) -> None
            
            root.right = build_tree(2, 2) -> nums[2:3] = [1]
                max_idx = 2, max_val = 1
                root = TreeNode(1)
                root.left = build_tree(2, 1) -> None
                root.right = build_tree(3, 2) -> None
                return TreeNode(1)
    
    root.right = build_tree(4, 5) -> nums[4:6] = [0,5]
        max_idx = 5, max_val = 5
        root = TreeNode(5)
        
        root.left = build_tree(4, 4) -> nums[4:5] = [0]
            max_idx = 4, max_val = 0
            root = TreeNode(0)
            root.left = build_tree(4, 3) -> None
            root.right = build_tree(5, 4) -> None
            return TreeNode(0)
        
        root.right = build_tree(6, 5) -> None
        
        return TreeNode(5)
```

**Final Tree Structure:**
```
        6
       / \
      3   5
       \ /
       2 0
        \
         1
```

---

## Complexity Analysis

### Time Complexity: **O(n²)**
- In each recursive call, we scan the subarray to find the maximum element: O(n)
- In the worst case (e.g., sorted array), the tree is completely unbalanced, leading to O(n) levels
- Total: O(n) × O(n) = **O(n²)**

### Space Complexity: **O(n)**
- Recursion stack depth: O(n) in the worst case (unbalanced tree)
- Tree storage: O(n)
- Total: **O(n)**

---

## Alternative Approach: Monotonic Stack (O(n))

For an optimized O(n) solution, you can use a monotonic decreasing stack to build the tree in one pass, which avoids repeatedly scanning for the maximum element.

```python
def constructMaximumBinaryTree(self, nums: List[int]) -> Optional[TreeNode]:
    stack = []
    for num in nums:
        node = TreeNode(num)
        # Pop smaller elements and make them left children
        while stack and stack[-1].val < num:
            node.left = stack.pop()
        # Current top of stack is larger, so current node becomes its right child
        if stack:
            stack[-1].right = node
        stack.append(node)
    # The bottom of the stack is the root
    return stack[0] if stack else None
```

**How it works:**
- Maintain a stack of nodes in decreasing order of values
- When a new larger value comes, all smaller values become its left subtree
- The stack maintains the property that each node's right child is added later

---

# Tags

`Binary Tree` `Divide and Conquer` `Recursion` `Stack` `Array` `Monotonic Stack`

