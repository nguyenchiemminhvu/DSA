## Problem

https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/description/

Given the root of a binary tree, return the lowest common ancestor of its deepest leaves.

**Recall that:**
- The node of a binary tree is a **leaf** if and only if it has no children
- The depth of the root of the tree is 0. If the depth of a node is d, the depth of each of its children is d + 1
- The **lowest common ancestor** of a set S of nodes, is the node A with the largest depth such that every node in S is in the subtree with root A

**Example 1:**
```
Input: root = [3,5,1,6,2,0,8,null,null,7,4]
Output: [2,7,4]
Explanation: We return the node with value 2.
The nodes 7 and 4 are the deepest leaf-nodes of the tree (depth 3).
```

**Example 2:**
```
Input: root = [1]
Output: [1]
Explanation: The root is the deepest node in the tree, and it's the lca of itself.
```

**Example 3:**
```
Input: root = [0,1,3,null,2]
Output: [2]
Explanation: The deepest leaf node in the tree is 2, the lca of one node is itself.
```

**Constraints:**
- The number of nodes in the tree will be in the range [1, 1000]
- 0 <= Node.val <= 1000
- The values of the nodes in the tree are unique

## Observations

1. **Two-Phase Problem:**
   - First, identify all the deepest leaves in the tree
   - Then, find the lowest common ancestor (LCA) of those deepest leaves

2. **Key Insights:**
   - If there's only one deepest leaf, it is its own LCA
   - If there are multiple deepest leaves, we need to find their common ancestor
   - The LCA must be at a depth less than or equal to the deepest leaves

3. **Approach Options:**
   - **BFS + Bottom-up tracking**: Use BFS to find deepest leaves, then track upward to find LCA
   - **DFS with depth tracking**: Single pass DFS that tracks depth and returns LCA information
   - **Two-pass approach**: First pass to find depth, second pass to find LCA

4. **Given Solution Analysis:**
   - Uses BFS to find all nodes at the deepest level
   - Uses DFS to propagate information upward, marking ancestors
   - Finds the deepest single node that is an ancestor of all deepest leaves

## Solution

### Approach 1: BFS + Bottom-up DFS (Given Solution - Optimizable)

The provided solution uses a two-step process:

**Step 1: BFS to find deepest nodes**
```python
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
```

**Step 2: DFS to mark ancestors**
```python
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
```

**Step 3: Find the deepest single ancestor**
```python
f = {}
for level, node in deepest_nodes:
    f[level] = f.get(level, 0) + 1
deep_single_level = sorted(f.keys(), key=lambda x: (f[x], -x))[0]
for level, node in deepest_nodes:
    if level == deep_single_level:
        return node
```

**Time Complexity:** O(n) for BFS + O(n) for DFS = O(n)  
**Space Complexity:** O(n) for storing nodes in set + O(h) for recursion stack

---

### Approach 2: Optimal DFS with Depth Tracking (Better Solution)

A more elegant solution uses a single DFS pass that returns both the depth and the LCA:

```python
class Solution:
    def lcaDeepestLeaves(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        def dfs(node):
            # Returns (depth, lca_node)
            if not node:
                return (0, None)
            
            left_depth, left_lca = dfs(node.left)
            right_depth, right_lca = dfs(node.right)
            
            # If both subtrees have same depth, current node is LCA
            if left_depth == right_depth:
                return (left_depth + 1, node)
            
            # Return the deeper subtree's LCA
            if left_depth > right_depth:
                return (left_depth + 1, left_lca)
            else:
                return (right_depth + 1, right_lca)
        
        _, lca = dfs(root)
        return lca
```

**How it works:**
1. **Base case:** Empty node returns depth 0 and no LCA
2. **Recursive case:** 
   - Get depth and LCA from left and right subtrees
   - If both depths are equal, current node is the LCA (it's the meeting point)
   - If depths differ, the deeper subtree contains all deepest leaves, so return its LCA
3. **Return:** The LCA found by the recursion

**Why this works:**
- If left_depth == right_depth: Both subtrees reach the same maximum depth, so the deepest leaves are split between both subtrees. The current node must be their LCA.
- If left_depth > right_depth: All deepest leaves are in the left subtree, so we propagate the left LCA upward.
- If right_depth > left_depth: All deepest leaves are in the right subtree, so we propagate the right LCA upward.

**Time Complexity:** O(n) - single pass through all nodes  
**Space Complexity:** O(h) - recursion stack where h is tree height

---

### Approach 3: Iterative with Parent Pointers

```python
class Solution:
    def lcaDeepestLeaves(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        # Step 1: BFS to find deepest leaves and store parents
        parent = {root: None}
        q = deque([root])
        deepest_leaves = []
        
        while q:
            deepest_leaves = list(q)  # Current level nodes
            for _ in range(len(q)):
                node = q.popleft()
                if node.left:
                    parent[node.left] = node
                    q.append(node.left)
                if node.right:
                    parent[node.right] = node
                    q.append(node.right)
        
        # Step 2: Find LCA using parent pointers
        # Get ancestors of first leaf
        ancestors = set()
        node = deepest_leaves[0]
        while node:
            ancestors.add(node)
            node = parent[node]
        
        # Find first common ancestor with other leaves
        for leaf in deepest_leaves[1:]:
            node = leaf
            while node not in ancestors:
                node = parent[node]
            # Update ancestors to only include common ones
            new_ancestors = set()
            temp = node
            while temp:
                new_ancestors.add(temp)
                temp = parent[temp]
            ancestors = new_ancestors
        
        # Return the deepest common ancestor
        return list(ancestors)[0] if len(deepest_leaves) == 1 else min(
            ancestors, 
            key=lambda x: sum(1 for _ in iter(lambda n=x: parent.get(n), None))
        )
```

**Time Complexity:** O(n)  
**Space Complexity:** O(n) for parent dictionary

---

### Comparison

| Approach | Time | Space | Clarity | Best For |
|----------|------|-------|---------|----------|
| Given (BFS+DFS) | O(n) | O(n) | Medium | Understanding the problem |
| Optimal DFS | O(n) | O(h) | High | Interviews, Clean code |
| Parent Pointers | O(n) | O(n) | Medium | When parent tracking is needed |

**Recommended:** The optimal DFS approach (Approach 2) is the best solution due to its elegance, optimal space complexity, and clear logic.

# Tags

`#binary-tree` `#tree` `#dfs` `#bfs` `#lowest-common-ancestor` `#recursion` `#depth-tracking` `#medium`

