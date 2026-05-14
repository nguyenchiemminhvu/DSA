## Problem

https://leetcode.com/problems/house-robber-iii/description

The thief has found a new area with houses arranged in a **binary tree structure**. Each house (except the root) has exactly one parent house. The constraint is that **two directly-linked houses cannot be robbed on the same night** (no parent-child pairs can both be robbed).

Given the root of a binary tree where each node's value represents the money in that house, return the **maximum amount of money** the thief can rob without alerting the police.

**Constraints:**
- Number of nodes: [1, 10^4]
- Node values: [0, 10^4]

**Examples:**

Example 1: `[3,2,3,null,3,null,1]`
```
     3
    / \
   2   3
    \   \
     3   1
```
Output: 7 (Rob 3 + 3 + 1)

Example 2: `[3,4,5,1,3,null,1]`
```
     3
    / \
   4   5
  / \   \
 1   3   1
```
Output: 9 (Rob 4 + 5)

## Observations

1. **Two States Per Node**: For each node, there are two possible states:
   - **Rob this node** (`reach_limit=True`): Cannot rob any of its children, must consider children's subtrees where they are NOT robbed
   - **Don't rob this node** (`reach_limit=False`): Children can either be robbed or not robbed, choose the maximum

2. **Dynamic Programming with State**: This is a tree DP problem where the optimal solution for a subtree depends on:
   - Whether the current node is robbed or not
   - The optimal solutions of its left and right subtrees with their respective states

3. **Overlapping Subproblems**: Many nodes will be visited multiple times in different recursive calls. Memoization is crucial to avoid exponential time complexity.

4. **Tree Structure Property**: Unlike arrays, the parent-child constraint on the tree means:
   - If we rob a node, we cannot rob its direct children (but can potentially rob grandchildren)
   - This creates a dependency chain up and down the tree

## Solution

### Approach: Tree DP with Memoization

**Algorithm:**

The solution uses a helper function `F(node, reach_limit)` that returns the maximum money that can be robbed from the subtree rooted at `node`:

- **Parameters:**
  - `node`: Current node in the tree
  - `reach_limit`: Boolean flag indicating if we can rob the current node
    - `reach_limit=False`: We can choose to rob or not rob the current node
    - `reach_limit=True`: We CANNOT rob the current node (it was robbed by parent)

- **Recurrence:**
  
  When `reach_limit=True` (cannot rob current node):
  $$F(\text{node}, \text{True}) = F(\text{left}, \text{False}) + F(\text{right}, \text{False})$$
  
  When `reach_limit=False` (can choose):
  $$F(\text{node}, \text{False}) = \max\begin{cases} 
  \text{node.val} + F(\text{left}, \text{True}) + F(\text{right}, \text{True}) & \text{(rob this node)}\\
  F(\text{left}, \text{False}) + F(\text{right}, \text{False}) & \text{(don't rob)}
  \end{cases}$$

- **Base Case:** 
  - If node is `None`, return 0

- **Memoization:** 
  - Cache results using `(id(node), reach_limit)` as the key
  - `id(node)` uniquely identifies each node object

### Time Complexity: $O(n)$
- Each node is visited at most twice (once with each `reach_limit` state)
- Total: 2n operations for n nodes

### Space Complexity: $O(n)$
- Memoization cache stores up to 2n entries
- Recursion call stack depth: $O(h)$ where h is tree height
- Overall: $O(n)$

### Example Trace: `[3,2,3,null,3,null,1]`

```
     3
    / \
   2   3
    \   \
     3   1

Starting: F(3, False)
├── Option 1: Rob 3 (val=3)
│   └── 3 + F(2, True) + F(3, True)
│       ├── F(2, True): Can't rob 2, sum children unconstrained
│       │   └── F(3, False) + F(None, False) = F(3, False) + 0
│       │       └── F(3, False): max(3 + 0 + 0, 0) = 3
│       │       └── Result: 3
│       └── F(3, True): Can't rob 3
│           └── F(None, False) + F(1, False) = 0 + 1 = 1
│       └── Total: 3 + 3 + 1 = 7
│
└── Option 2: Don't rob 3
    └── F(2, False) + F(3, False)
        ├── F(2, False): max(2 + 0, 0 + F(3, False)) = max(2, 3) = 3
        └── F(3, False): max(3 + 0, 0) = 3
        └── Total: 3 + 3 = 6

Answer: max(7, 6) = 7
```

### Key Insights:

1. **State Encoding**: The `reach_limit` flag elegantly encodes whether we're forced to skip the current node or have freedom to choose

2. **Local Optimality**: Each recursive call makes locally optimal decisions that combine to form the globally optimal solution

3. **Avoiding Redundant Computation**: Without memoization, we'd explore the same subtree states exponentially many times. With memoization, each unique state is computed only once.

# Tags
Tree DP, Dynamic Programming, Memoization, Binary Tree, Recursion

