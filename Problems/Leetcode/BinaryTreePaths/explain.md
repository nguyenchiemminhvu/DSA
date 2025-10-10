## Problem

```
Given the root of a binary tree, return all root-to-leaf paths in any order.

A leaf is a node with no children.

Example 1:

Input: root = [1,2,3,null,5]
Output: ["1->2->5","1->3"]

Example 2:

Input: root = [1]
Output: ["1"]

Constraints:

The number of nodes in the tree is in the range [1, 100].
-100 <= Node.val <= 100
```

## Observations

1. **Problem Nature**: This is a classic tree traversal problem where we need to find all paths from root to leaf nodes.

2. **Path Definition**: A root-to-leaf path is a sequence of nodes from the root node to any leaf node (a node with no children).

3. **Output Format**: Each path should be represented as a string with node values separated by `"->"` arrows.

4. **Tree Structure**: Since we need to visit all possible paths, we need to explore both left and right subtrees recursively.

5. **Backtracking Pattern**: We need to maintain the current path and backtrack when we finish exploring a subtree to explore other branches.

6. **Base Cases**:
   - If current node is null, return immediately
   - If current node is a leaf (no left or right child), add current path to results

## Solution

The solution uses **Depth-First Search (DFS)** with **Backtracking**:

### Algorithm Steps:

1. **Recursive Function**: `traversal(root, path, paths)`
   - `root`: current node being visited
   - `path`: current path from root to current node
   - `paths`: list to store all complete root-to-leaf paths

2. **Base Case**: If `root` is `None`, return immediately (handles null nodes)

3. **Add Current Node**: Add current node's value to the path

4. **Leaf Node Check**: If current node has no children, it's a leaf:
   - Make a copy of current path and add to results
   - Copy is necessary because `path` list will be modified during backtracking

5. **Recursive Exploration**:
   - Recursively explore left subtree
   - Recursively explore right subtree

6. **Backtrack**: Remove current node from path (`path.pop()`)
   - This ensures when we return from recursion, the path is restored to its previous state
   - Allows exploring other branches with correct path state

7. **Format Output**: Convert each path (list of integers) to string format with `"->"` separators

### Key Implementation Details:

- **Backtracking**: The `path.pop()` at the end is crucial for proper backtracking
- **Deep Copy**: `[val for val in path]` creates a copy when adding to results, preventing modification
- **String Formatting**: Final conversion joins integers with `"->"` using list comprehension

### Time Complexity: O(N × H)
- `N` = number of nodes (we visit each node once)
- `H` = height of tree (average path length for string construction)

### Space Complexity: O(N × H)
- Recursion stack: `O(H)` in worst case
- Storage for all paths: `O(N × H)` in worst case when tree is completely unbalanced

## Tags

array, string, binary tree, dfs