## Problem

https://leetcode.com/problems/sum-of-left-leaves/description/

```
Given the root of a binary tree, return the sum of all left leaves.

A leaf is a node with no children. A left leaf is a leaf that is the left child of another node.

Example 1:

Input: root = [3,9,20,null,null,15,7]
Output: 24
Explanation: There are two left leaves in the binary tree, with values 9 and 15 respectively.

Example 2:

Input: root = [1]
Output: 0

Constraints:

The number of nodes in the tree is in the range [1, 1000].
-1000 <= Node.val <= 1000
```

## Observations

1. **Problem Definition**: We need to identify and sum all "left leaves" - nodes that are both:
   - Leaf nodes (no left or right children)
   - Left children of their parent nodes

2. **Key Insight**: A node's position (left vs right child) can only be determined by tracking the direction we came from during traversal, not from the node itself.

3. **Two Conditions Must Be Met**:
   - The node must be a leaf: `root.left == None and root.right == None`
   - The node must be reached via a left traversal: `went_left == True`

4. **Edge Cases**:
   - Single node tree: Root cannot be a left leaf (no parent), so sum = 0
   - Tree with no left leaves: Return 0
   - Tree with only left or only right children: Still need to check leaf condition

5. **Traversal Strategy**: Use DFS with direction tracking - pass a boolean indicating whether we moved left or right to reach the current node.

6. **Example Walkthrough** for `[3,9,20,null,null,15,7]`:
   ```
   Tree structure:
       3
      / \
     9   20
        /  \
       15   7
   
   Traversal with direction tracking:
   - Start at 3 (went_left=False)
   - Go to 9 (went_left=True) → 9 is leaf + went_left → Add 9
   - Go to 20 (went_left=False)
   - Go to 15 (went_left=True) → 15 is leaf + went_left → Add 15  
   - Go to 7 (went_left=False) → 7 is leaf but !went_left → Skip
   
   Sum = 9 + 15 = 24
   ```

## Solution

The solution uses a **recursive depth-first search (DFS) with direction tracking**:

### Key Strategy:
- **Direction Parameter**: Pass `went_left` boolean to track whether we reached current node via left or right traversal
- **Leaf Detection**: Check if current node has no children (`root.left == None and root.right == None`)
- **Left Leaf Identification**: Combine direction and leaf conditions to identify left leaves
- **Accumulation**: Use a list to collect left leaf values, then sum at the end

### Algorithm Breakdown:

1. **Initialize**: Create empty list `s` for storing left leaf values
2. **Recursive Function**: `traversal(root, went_left)`
   - `root`: current node being visited
   - `went_left`: boolean indicating if we came from a left traversal
3. **Base Case**: If `root` is `None`, return immediately
4. **Left Leaf Check**: If `went_left == True` AND node is a leaf, add value to list
5. **Recursive Calls**:
   - `traversal(root.left, True)` - moving left, so set went_left=True
   - `traversal(root.right, False)` - moving right, so set went_left=False
6. **Initial Call**: Start with `traversal(root, False)` since root is not a left child
7. **Return Sum**: Sum all collected left leaf values

## Tags

binary tree, dfs