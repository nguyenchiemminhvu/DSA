## Problem

https://leetcode.com/problems/evaluate-boolean-binary-tree/description/

```
You are given the root of a full binary tree with the following properties:

Leaf nodes have either the value 0 or 1, where 0 represents False and 1 represents True.
Non-leaf nodes have either the value 2 or 3, where 2 represents the boolean OR and 3 represents the boolean AND.
The evaluation of a node is as follows:

If the node is a leaf node, the evaluation is the value of the node, i.e. True or False.
Otherwise, evaluate the node's two children and apply the boolean operation of its value with the children's evaluations.
Return the boolean result of evaluating the root node.

A full binary tree is a binary tree where each node has either 0 or 2 children.

A leaf node is a node that has zero children.

Example 1:

Input: root = [2,1,3,null,null,0,1]
Output: true
Explanation: The above diagram illustrates the evaluation process.
The AND node evaluates to False AND True = False.
The OR node evaluates to True OR False = True.
The root node evaluates to True, so we return true.

Example 2:

Input: root = [0]
Output: false
Explanation: The root node is a leaf node and it evaluates to false, so we return false.

Constraints:

The number of nodes in the tree is in the range [1, 1000].
0 <= Node.val <= 3
Every node has either 0 or 2 children.
Leaf nodes have a value of 0 or 1.
Non-leaf nodes have a value of 2 or 3.
```

## Observations

1. **Tree Structure**: This is a full binary tree where every node has either 0 or 2 children.
2. **Node Values**:
   - Leaf nodes: 0 (False) or 1 (True)
   - Non-leaf nodes: 2 (OR operation) or 3 (AND operation)
3. **Evaluation Rules**:
   - Leaf nodes return their boolean value directly
   - Non-leaf nodes apply their operation to their children's evaluations
4. **Recursive Nature**: The problem naturally lends itself to a recursive solution since we need to evaluate children before evaluating the parent.

## Solution

1. **Base Cases**:
   - If the node is null, return False (though this shouldn't happen in a valid tree)
   - If the node is a leaf (no children), convert its value to boolean and return

2. **Recursive Cases**:
   - For OR operation (value = 2): Recursively evaluate both children and return `left OR right`
   - For AND operation (value = 3): Recursively evaluate both children and return `left AND right`

### Time Complexity: O(n)
- We visit each node exactly once, where n is the number of nodes in the tree

### Space Complexity: O(h)
- Where h is the height of the tree due to the recursive call stack
- In the worst case, h = n for a skewed tree, but for a balanced tree h = log(n)

### Key Insights:
- The solution leverages Python's short-circuit evaluation for `and` and `or` operators
- The recursive structure mirrors the tree structure perfectly
- Each node's evaluation depends only on its children's evaluations, making recursion natural

# Tags

Tree, Binary Tree, Recursion, Depth-First Search, Boolean Logic

