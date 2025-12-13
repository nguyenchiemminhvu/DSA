## Problem

https://leetcode.com/problems/path-sum-ii/description/

```
Given the root of a binary tree and an integer targetSum, return all root-to-leaf paths 
where the sum of the node values in the path equals targetSum. Each path should be returned 
as a list of the node values, not node references.

A root-to-leaf path is a path starting from the root and ending at any leaf node. 
A leaf is a node with no children.

Example 1:
Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
Output: [[5,4,11,2],[5,8,4,5]]
Explanation: There are two paths whose sum equals targetSum:
5 + 4 + 11 + 2 = 22
5 + 8 + 4 + 5 = 22

Example 2:
Input: root = [1,2,3], targetSum = 5
Output: []

Example 3:
Input: root = [1,2], targetSum = 0
Output: []

Constraints:
- The number of nodes in the tree is in the range [0, 5000].
- -1000 <= Node.val <= 1000
- -1000 <= targetSum <= 1000
```

## Observations

1. **Path Definition**: We need to find paths from root to leaf nodes (not just any node)
   - A leaf node is defined as a node with no children (both left and right are None)
   - This is crucial: we can't stop at an internal node even if the sum matches

2. **Search Strategy**: Since we need to explore all possible paths, DFS (Depth-First Search) is ideal
   - We need to explore every root-to-leaf path to check if it matches the target sum
   - Backtracking approach is natural for this problem

3. **State Tracking**: As we traverse, we need to track:
   - Current path (list of node values)
   - Current sum (sum of node values in the current path)
   - Both need to be updated as we go deeper and restored when backtracking

4. **Edge Cases**:
   - Empty tree (root is None): return empty list
   - Single node: check if its value equals targetSum
   - Negative node values are allowed, so we can't do early pruning based on sum

5. **Important**: We need to return all valid paths, not just count them or return a boolean

## Solution

### Approach: DFS with Backtracking

The solution uses recursive DFS traversal with the following strategy:

**Key Idea**: 
- Traverse the tree from root to leaf
- Maintain the current path and running sum
- When we reach a leaf, check if the total sum equals target
- Use backtracking to explore all possible paths

**Algorithm Steps**:

1. **Base Case - Null Node**: If current node is None, return immediately
   
2. **Leaf Node Check**: If we reach a leaf node (no left and no right children):
   - Check if `cur_sum + root.val == target`
   - If yes, add the complete path to results
   - Return (backtrack)

3. **Recursive Exploration**: For internal nodes:
   - Add current node's value to the running sum
   - Add current node's value to the current path
   - Recursively explore left subtree
   - Recursively explore right subtree

4. **Implicit Backtracking**: By passing `tmp + [root.val]` instead of modifying `tmp` in-place, we create a new list for each recursive call, which achieves backtracking automatically

**Complexity Analysis**:

- **Time Complexity**: O(N²) where N is the number of nodes
  - We visit each node once: O(N)
  - At each leaf node, we might copy the path which takes O(H) where H is height
  - In worst case (skewed tree), this becomes O(N²)
  - For balanced tree: O(N * log N)

- **Space Complexity**: O(H) where H is the height of the tree
  - Recursion stack: O(H)
  - Path storage: O(H)
  - Result storage not counted as it's the output
  - For balanced tree: O(log N)
  - For skewed tree: O(N)

**Alternative Approach (Explicit Backtracking)**:

```python
class Solution:
    def pathSum(self, root: Optional[TreeNode], target: int) -> List[List[int]]:
        res = []
        path = []
        
        def dfs(node, cur_sum):
            if not node:
                return
            
            # Add current node to path
            path.append(node.val)
            cur_sum += node.val
            
            # Check if leaf and sum matches
            if not node.left and not node.right:
                if cur_sum == target:
                    res.append(path[:])  # Make a copy
            else:
                # Explore children
                dfs(node.left, cur_sum)
                dfs(node.right, cur_sum)
            
            # Backtrack: remove current node from path
            path.pop()
        
        dfs(root, 0)
        return res
```

This version explicitly backtracks by removing nodes from the path after exploring subtrees. Note the `path[:]` copy when adding to results - this is crucial because we're reusing the same path list.

# Tags
Binary Tree, DFS, Backtracking, Tree Traversal, Recursion

