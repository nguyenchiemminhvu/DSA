## Problem

https://leetcode.com/problems/maximum-product-of-splitted-binary-tree/

```
Given the root of a binary tree, split the binary tree into two subtrees by removing 
one edge such that the product of the sums of the subtrees is maximized.

Return the maximum product of the sums of the two subtrees. Since the answer may be 
too large, return it modulo 10^9 + 7.

Note that you need to maximize the answer before taking the mod and not after taking it.

Constraints:
- The number of nodes in the tree is in the range [2, 5 * 10^4]
- 1 <= Node.val <= 10^4

Example 1:
Input: root = [1,2,3,4,5,6]
Output: 110
Explanation: Remove the red edge and get 2 binary trees with sum 11 and 10. 
Their product is 110 (11*10)

Example 2:
Input: root = [1,null,2,3,4,null,null,5,6]
Output: 90
Explanation: Remove the red edge and get 2 binary trees with sum 15 and 6.
Their product is 90 (15*6)
```

## Observations

1. **Problem Understanding**:
   - We need to remove exactly ONE edge from the binary tree
   - This splits the tree into two subtrees
   - We want to maximize: `sum(subtree1) * sum(subtree2)`

2. **Key Insight - Complementary Sums**:
   - If we know the total sum of all nodes: `total`
   - And we know the sum of one subtree: `subtree_sum`
   - Then the other subtree sum is: `total - subtree_sum`
   - Product: `subtree_sum * (total - subtree_sum)`

3. **Which Edge to Remove?**:
   - Removing an edge below a node disconnects that node's subtree from the rest
   - We need to try removing each possible edge and calculate the product
   - The subtree sum at each node represents what we get if we cut the edge above that node

4. **Approach**:
   - First, calculate the total sum of all nodes
   - Then, for each node, calculate its subtree sum (node + left subtree + right subtree)
   - For each node, if we cut the edge above it, one part has `subtree_sum`, the other has `total - subtree_sum`
   - Track the maximum product

5. **Optimization Technique**:
   - Instead of recalculating subtree sums multiple times, we can modify each node to store its subtree sum
   - This is what the `refactor_tree` function does - it transforms each node's value to represent the sum of its entire subtree

## Solution

### Algorithm

```
1. Calculate the total sum of all nodes in the tree
2. Transform the tree so each node stores its subtree sum (node + left + right)
3. Traverse the tree and for each node:
   - Current subtree sum = node.val (after transformation)
   - Remaining tree sum = total - current subtree sum
   - Product = current_sum * remaining_sum
   - Track maximum product
4. Return max_product % (10^9 + 7)
```

### Implementation Breakdown

**Step 1: Calculate Total Sum**
```python
def sum_tree(root: Optional[TreeNode]) -> int:
    if not root:
        return 0
    return root.val + sum_tree(root.left) + sum_tree(root.right)
```
- Simple recursive traversal to sum all node values

**Step 2: Transform Tree to Store Subtree Sums**
```python
def refactor_tree(root: Optional[TreeNode]) -> None:
    if not root:
        return
    refactor_tree(root.left)    # Process left subtree first
    refactor_tree(root.right)   # Process right subtree first
    if root.left:
        root.val += root.left.val   # Add left subtree sum
    if root.right:
        root.val += root.right.val  # Add right subtree sum
```
- Post-order traversal (children first, then parent)
- After this, each node's value = sum of its entire subtree

**Step 3: Find Maximum Product**
```python
def traversal(root: Optional[TreeNode]) -> None:
    if not root:
        return
    cur_sum = root.val              # Subtree sum at this node
    remain = total - cur_sum        # Remaining tree sum
    max_prod[0] = max(max_prod[0], cur_sum * remain)
    
    traversal(root.left)
    traversal(root.right)
```
- Try cutting at each node
- Calculate product and update maximum

### Example Walkthrough

**Example 1: root = [1,2,3,4,5,6]**

```
Original Tree:        After refactor_tree:
      1                      21
     / \                    /  \
    2   3                 11   10
   / \   \               / \    \
  4   5   6             4   5    6
```

Total sum = 21

Trying each cut:
- Cut at node with subtree_sum=4: 4 * (21-4) = 4 * 17 = 68
- Cut at node with subtree_sum=5: 5 * (21-5) = 5 * 16 = 80
- Cut at node with subtree_sum=11: 11 * (21-11) = 11 * 10 = **110** ← Maximum
- Cut at node with subtree_sum=6: 6 * (21-6) = 6 * 15 = 90
- Cut at node with subtree_sum=10: 10 * (21-10) = 10 * 11 = 110
- Cut at root (subtree_sum=21): 21 * 0 = 0 (can't cut above root)

Maximum product = 110

### Complexity Analysis

- **Time Complexity**: O(n)
  - `sum_tree`: O(n) - visits each node once
  - `refactor_tree`: O(n) - visits each node once
  - `traversal`: O(n) - visits each node once
  - Total: O(n) + O(n) + O(n) = O(n)

- **Space Complexity**: O(h) where h is the height of the tree
  - Recursion stack space
  - O(log n) for balanced tree, O(n) for skewed tree

# Tags

`Binary Tree` `Tree Traversal` `Post-Order Traversal` `Dynamic Programming` `Recursion` `DFS`