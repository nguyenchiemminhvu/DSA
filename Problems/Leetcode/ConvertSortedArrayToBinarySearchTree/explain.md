## Problem

https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/

```
Given an integer array nums where the elements are sorted in ascending order, convert it to a height-balanced binary search tree.

Example 1:

Input: nums = [-10,-3,0,5,9]
Output: [0,-3,9,-10,null,5]
Explanation: [0,-10,5,null,-3,null,9] is also accepted:

Example 2:

Input: nums = [1,3]
Output: [3,1]
Explanation: [1,null,3] and [3,1] are both height-balanced BSTs.

Constraints:

1 <= nums.length <= 104
-104 <= nums[i] <= 104
nums is sorted in a strictly increasing order.
```

## Observations

1. **Height-balanced BST requirement**: The tree must be height-balanced, meaning the depth of any two leaf nodes differs by at most 1.

2. **Sorted array advantage**: Since the input array is already sorted in ascending order, we can leverage this property to build a balanced BST efficiently.

3. **Middle element as root**: To ensure balance, we should choose the middle element of any subarray as the root. This guarantees that roughly equal numbers of elements go to the left and right subtrees.

4. **Recursive structure**: The problem has a natural recursive structure - after choosing the middle element as root, we recursively build left and right subtrees from the left and right subarrays respectively.

5. **Multiple valid solutions**: Due to the way we handle even-length arrays (choosing left-middle vs right-middle), there can be multiple valid height-balanced BSTs for the same input.

## Solution

**Approach: Recursive Divide and Conquer**

The key insight is to use the middle element of the current array segment as the root, then recursively build left and right subtrees.

**Algorithm:**
1. Use a helper function `converting(left, right)` that works with array indices
2. **Base case**: If `left > right`, return `None` (empty subtree)
3. **Choose middle**: Calculate `mid = left + (right - left) // 2` to avoid integer overflow
4. **Create root**: Make a new TreeNode with `nums[mid]` as the value
5. **Recursive calls**: 
   - Left subtree: `converting(left, mid - 1)`
   - Right subtree: `converting(mid + 1, right)`
6. Return the constructed root

**Why this works:**
- By always choosing the middle element, we ensure the tree remains balanced
- The recursive nature ensures every subtree is also balanced
- Since we're working with a sorted array, the BST property is automatically maintained (left < root < right)

**Time Complexity:** O(n) - we visit each element exactly once
**Space Complexity:** O(log n) - recursion stack depth for a balanced tree

**Example walkthrough with `nums = [-10, -3, 0, 5, 9]`:**
1. Initial call: `converting(0, 4)`, mid = 2, root = TreeNode(0)
2. Left subtree: `converting(0, 1)`, mid = 0, root = TreeNode(-10)
   - Right child: `converting(1, 1)`, mid = 1, root = TreeNode(-3)
3. Right subtree: `converting(3, 4)`, mid = 3, root = TreeNode(5)
   - Right child: `converting(4, 4)`, mid = 4, root = TreeNode(9)

This produces a height-balanced BST with root 0, satisfying all requirements.

## Tags

array, binary search tree