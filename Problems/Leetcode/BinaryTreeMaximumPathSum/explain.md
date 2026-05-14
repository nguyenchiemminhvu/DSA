## Problem

https://leetcode.com/problems/binary-tree-maximum-path-sum/description

A path in a binary tree is a sequence of nodes where each pair of adjacent nodes in the sequence has an edge connecting them. A node can only appear in the sequence at most once. Note that the path does not need to pass through the root.

The path sum of a path is the sum of the node's values in the path.

Given the root of a binary tree, return the maximum path sum of any non-empty path.

### Examples

**Example 1:**
```
Input: root = [1,2,3]
Output: 6
Explanation: The optimal path is 2 -> 1 -> 3 with a path sum of 2 + 1 + 3 = 6.
```

**Example 2:**
```
Input: root = [-10,9,20,null,null,15,7]
Output: 42
Explanation: The optimal path is 15 -> 20 -> 7 with a path sum of 15 + 20 + 7 = 42.
```

### Constraints

- The number of nodes in the tree is in the range [1, 3 * 10^4]
- -1000 <= Node.val <= 1000

## Observations

1. **Path Definition**: A valid path must be contiguous (connected by edges) and can start/end at any node, not necessarily the root.

2. **Non-overlapping Constraints**: A node appears at most once in a path, meaning we can't revisit nodes.

3. **Two Types of Paths at Each Node**:
   - **Full Path**: A path that passes through the current node and uses both left and right subtrees (contributes to the global maximum)
   - **One-sided Path**: A path that goes through the current node and extends to only one child (can be returned to parent)

4. **Key Insight**: For each node, we need to track:
   - The maximum path that passes through it (for global answer)
   - The maximum gain we can get if we extend a path through it to its parent

5. **Pruning Negative Contributions**: If a subtree sum is negative, it's better not to include it in the path, so we take `max(subtree_sum, 0)`.

6. **Parent Constraint**: We can only return one branch to the parent (can't use both left and right), so we pick the maximum.

## Solution

### Approach: Post-order DFS with Memoization

The solution uses **Depth-First Search (DFS)** with a **post-order traversal** to process nodes from leaves to root.

**Key Components:**

1. **Helper Function `F(node)`**: Returns the maximum path sum that **starts from the current node and extends downward** to one of its children (or just the node itself).

2. **Global Maximum Tracker**: Maintained separately because the maximum path might not end at the root.

3. **Memoization**: Uses `id(root)` as key to cache results and avoid recalculating for the same node.

### Algorithm Breakdown

```
For each node:
  1. Recursively calculate maximum gains from left and right subtrees
  2. Clamp negative gains to 0 (don't include negative contributions)
  3. Calculate full_path = left_sum + node.val + right_sum
  4. Update global_max with full_path (this represents a valid path through current node)
  5. Return to parent: node.val + max(left_sum, right_sum)
     (only one branch can extend to parent)
```

### Complexity Analysis

- **Time Complexity**: $O(n)$ where $n$ is the number of nodes. Each node is visited once due to memoization.
- **Space Complexity**: $O(h)$ for the recursion stack (height of tree) + $O(n)$ for memoization = $O(n)$ in the worst case (skewed tree).

### Why This Works

**Example 2 Walkthrough**: `[-10, 9, 20, null, null, 15, 7]`

```
       -10
       /  \
      9    20
         /  \
        15   7
```

- **Node 15**: F(15) = 15, global_max = 15
- **Node 7**: F(7) = 7, global_max = 15
- **Node 20**: 
  - left_sum = max(15, 0) = 15
  - right_sum = max(7, 0) = 7
  - full_path = 15 + 20 + 7 = 42 ✓
  - global_max = 42
  - F(20) = 20 + max(15, 7) = 35
- **Node 9**: F(9) = 9, global_max = 42
- **Node -10**:
  - left_sum = max(9, 0) = 9
  - right_sum = max(35, 0) = 35
  - full_path = 9 + (-10) + 35 = 34
  - global_max = 42 (unchanged, which is correct!)
  - Returns 34 to parent (but no parent exists)

The answer is **42**, which is the path 15 → 20 → 7.

# Tags

#tree #dfs #post-order #memoization #dynamic-programming #path-sum

