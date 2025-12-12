## Problem

https://leetcode.com/problems/all-possible-full-binary-trees/

```
Given an integer n, return a list of all possible full binary trees with n nodes. Each node of each tree in the answer must have Node.val == 0.

Each element of the answer is the root node of one possible tree. You may return the final list of trees in any order.

A full binary tree is a binary tree where each node has exactly 0 or 2 children.

Example 1:
Input: n = 7
Output: [[0,0,0,null,null,0,0,null,null,0,0],[0,0,0,null,null,0,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,null,null,null,null,0,0],[0,0,0,0,0,null,null,0,0]]

Example 2:
Input: n = 3
Output: [[0,0,0]]

Constraints:
- 1 <= n <= 20
```

## Observations

1. **Full Binary Tree Property**: In a full binary tree, every node has either 0 or 2 children. This means:
   - Leaf nodes have 0 children
   - Internal nodes have exactly 2 children

2. **Odd Number Constraint**: A full binary tree can only have an **odd number** of nodes. Why?
   - Start with 1 node (root)
   - Each internal node adds 2 children
   - So total = 1 + 2k for some k ≥ 0
   - This is always odd
   - Therefore, if n is even, return empty list immediately

3. **Recursive Structure**: To build a full binary tree with n nodes:
   - Use 1 node for the root
   - Distribute remaining (n-1) nodes between left and right subtrees
   - Both subtrees must also be full binary trees
   - Both subtrees must have odd number of nodes

4. **Distribution Pattern**: For n nodes (n is odd):
   - Root takes 1 node
   - Remaining: n-1 nodes to distribute
   - Left subtree can have: 1, 3, 5, ..., (n-2) nodes (all odd)
   - Right subtree gets the remainder
   - For each valid distribution, recursively build all possible left and right subtrees

5. **Combination**: The total number of trees is the product of:
   - Number of possible left subtrees × Number of possible right subtrees
   - For all valid distributions

## Solution

### Approach: Recursive Tree Construction with Memoization Potential

**Algorithm**:

1. **Base Case - Even Numbers**: If n is even, return empty list (impossible to form full binary tree)

2. **Base Cases for Recursion**:
   - If n ≤ 0: return [None]
   - If n == 1: return [TreeNode(0)] (single node tree)

3. **Recursive Case** (n ≥ 3):
   - Reserve 1 node for root
   - Remaining nodes: n - 1
   - Iterate through all odd distributions:
     - Left subtree: 1, 3, 5, ..., (n-2) nodes
     - Right subtree: (n-1) - left_count nodes
   
4. **Build All Combinations**:
   - For each distribution (left_count, right_count):
     - Recursively get all possible left subtrees with left_count nodes
     - Recursively get all possible right subtrees with right_count nodes
     - Create a new root for each combination of left and right subtree
     - Add to results

5. **Return** all generated trees

**Why iterate by 2 (only odd numbers)?**
- Left subtree needs odd number of nodes to be a full binary tree
- We iterate: 1, 3, 5, 7, ... by using `range(1, n, 2)`
- Right subtree automatically gets odd number too since (n-1) is even and we subtract odd from even

**Time Complexity**: O(2^n)
- The number of full binary trees grows exponentially
- Catalan number-like growth pattern
- Each tree construction involves creating nodes and combinations

**Space Complexity**: O(2^n)
- Storing all possible trees
- Recursion call stack: O(n)

# Tags

`Binary Tree` `Recursion` `Dynamic Programming` `Memoization` `Tree Construction` `Backtracking`