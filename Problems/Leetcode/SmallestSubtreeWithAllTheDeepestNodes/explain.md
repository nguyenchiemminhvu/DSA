## Problem

https://leetcode.com/problems/smallest-subtree-with-all-the-deepest-nodes/description/

Given the root of a binary tree, find the smallest subtree that contains all the deepest nodes in the original tree.

**Key Definitions:**
- **Depth**: The shortest distance from a node to the root
- **Deepest nodes**: Nodes with the largest depth in the entire tree
- **Subtree**: A tree consisting of a node plus all its descendants

**Examples:**

Example 1:
```
Input: root = [3,5,1,6,2,0,8,null,null,7,4]
Output: [2,7,4]
Explanation: Nodes 7 and 4 are the deepest (depth 4).
Node 2 is their lowest common ancestor, forming the smallest subtree.
```

Example 2:
```
Input: root = [1]
Output: [1]
```

Example 3:
```
Input: root = [0,1,3,null,2]
Output: [2]
```

**Constraints:**
- 1 ≤ Number of nodes ≤ 500
- 0 ≤ Node.val ≤ 500
- All node values are unique

## Observations

1. **Key Insight**: The answer is the **Lowest Common Ancestor (LCA)** of all deepest nodes
   - If there's only one deepest node, return that node
   - If there are multiple deepest nodes, return their LCA

2. **Properties of the Solution**:
   - If left and right subtrees have the same max depth, current node is the answer
   - If one subtree is deeper, the answer lies in that subtree
   - The answer node must have all deepest nodes as descendants

3. **Depth Comparison Strategy**:
   - We need to compare depths of left and right subtrees at each node
   - Equal depths → current node is the LCA of deepest nodes
   - Unequal depths → answer is in the deeper subtree

4. **Why Bottom-up DFS Works**:
   - Process nodes from leaves to root (post-order)
   - At each node, we know the deepest nodes in both subtrees
   - Can make decision based on relative depths

## Solution

### Optimal Approach: Single DFS Pass

The key idea is to return both the **depth** and the **subtree root** for each recursive call.

**Algorithm:**
1. For each node, recursively compute:
   - Maximum depth of left subtree and its answer node
   - Maximum depth of right subtree and its answer node
   
2. Decision logic at current node:
   - If `left_depth == right_depth`: Current node contains all deepest nodes (return current node)
   - If `left_depth > right_depth`: Answer is in left subtree (return left answer)
   - If `right_depth > left_depth`: Answer is in right subtree (return right answer)

3. Return: `(current_depth, subtree_with_deepest_nodes)`

**Implementation:**

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def subtreeWithAllDeepest(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        def dfs(node: Optional[TreeNode]) -> tuple[int, Optional[TreeNode]]:
            """
            Returns: (depth, subtree_root)
            - depth: maximum depth from this node to deepest leaf
            - subtree_root: root of smallest subtree containing all deepest nodes
            """
            if not node:
                return (0, None)
            
            left_depth, left_subtree = dfs(node.left)
            right_depth, right_subtree = dfs(node.right)
            
            # If both subtrees have equal depth, current node is the LCA
            if left_depth == right_depth:
                return (left_depth + 1, node)
            
            # Otherwise, the answer is in the deeper subtree
            if left_depth > right_depth:
                return (left_depth + 1, left_subtree)
            else:
                return (right_depth + 1, right_subtree)
        
        _, result = dfs(root)
        return result
```

**Complexity Analysis:**
- **Time Complexity**: O(n) - Visit each node once
- **Space Complexity**: O(h) - Recursion stack depth (h = height of tree)

### Walkthrough Example

Example: `root = [3,5,1,6,2,0,8,null,null,7,4]`

```
        3
       / \
      5   1
     /\   /\
    6  2 0  8
      /\
     7  4
```

**DFS Execution (post-order):**
1. Node 7: `depth=1, subtree=7`
2. Node 4: `depth=1, subtree=4`
3. Node 2: `left_depth=1, right_depth=1` → **Equal!** → `return (2, Node(2))`
4. Node 6: `depth=1, subtree=6`
5. Node 5: `left_depth=1, right_depth=2` → Right deeper → `return (3, Node(2))`
6. Node 0: `depth=1, subtree=0`
7. Node 8: `depth=1, subtree=8`
8. Node 1: `left_depth=1, right_depth=1` → Equal → `return (2, Node(1))`
9. Node 3: `left_depth=3, right_depth=2` → Left deeper → `return (4, Node(2))`

**Result**: Node(2) ✓

### Alternative Solution: BFS + DFS (Less Optimal)

```python
class Solution:
    def subtreeWithAllDeepest(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        # Step 1: Find all deepest nodes using BFS
        def bfs() -> Set[TreeNode]:
            deepest_nodes = set()
            level = 0
            q = deque([root])
            while q:
                size = len(q)
                row = []
                level += 1
                for _ in range(size):
                    cur_node = q.pop()
                    row.append(cur_node)
                    if cur_node.left:
                        q.appendleft(cur_node.left)
                    if cur_node.right:
                        q.appendleft(cur_node.right)
                deepest_nodes = set([(level, node) for node in row])
            return deepest_nodes
        
        deepest_nodes = bfs()
        
        # Step 2: Build ancestor chain using DFS
        def dfs(root: Optional[TreeNode], level:int = 1):
            nonlocal deepest_nodes
            if not root:
                return
            dfs(root.left, level + 1)
            dfs(root.right, level + 1)
            if root.left and (level + 1, root.left) in deepest_nodes:
                deepest_nodes.add((level, root))
            if root.right and (level + 1, root.right) in deepest_nodes:
                deepest_nodes.add((level, root))
        
        dfs(root, 1)

        # Step 3: Find the LCA (deepest level with single node)
        f = {}
        for level, node in deepest_nodes:
            f[level] = f.get(level, 0) + 1
        deep_single_level = sorted(f.keys(), key=lambda x: (f[x], -x))[0]
        for level, node in deepest_nodes:
            if level == deep_single_level:
                return node
        return None
```

**Issues with this approach:**
- More complex: requires BFS, DFS, and frequency counting
- Higher space complexity: O(n) for storing all deepest nodes and ancestors
- Less intuitive: multiple passes through the tree

# Tags

Binary Tree, DFS, Tree Traversal, Lowest Common Ancestor (LCA), Recursion, Post-order Traversal

