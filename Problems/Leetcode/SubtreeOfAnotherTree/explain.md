## Problem

https://leetcode.com/problems/subtree-of-another-tree/description/

```
Given the roots of two binary trees root and subRoot, return true if there is a subtree of root with the same structure and node values of subRoot and false otherwise.

A subtree of a binary tree tree is a tree that consists of a node in tree and all of this node's descendants. The tree tree could also be considered as a subtree of itself.

Example 1:

Input: root = [3,4,5,1,2], subRoot = [4,1,2]
Output: true

Example 2:

Input: root = [3,4,5,1,2,null,null,null,null,0], subRoot = [4,1,2]
Output: false

Constraints:

The number of nodes in the root tree is in the range [1, 2000].
The number of nodes in the subRoot tree is in the range [1, 1000].
-104 <= root.val <= 104
-104 <= subRoot.val <= 104
```

## Observations

1. **Problem Definition**: We need to determine if `subRoot` exists as a complete subtree within `root`. A subtree means starting from some node in `root`, the entire structure below that node must match `subRoot` exactly.

2. **Key Insight**: This problem can be broken down into two sub-problems:
   - **Tree Comparison**: Given two trees, check if they are identical
   - **Subtree Search**: Traverse the main tree and check if any node can serve as the root of the subtree

3. **Edge Cases to Consider**:
   - If `subRoot` is `None`, it should return `True` (empty tree is subtree of any tree)
   - If `root` is `None` but `subRoot` is not, return `False`
   - Single node trees
   - Trees with duplicate values

4. **Approach Strategy**:
   - Use a helper function to check if two trees are identical
   - For each node in the main tree, check if it can be the root of the subtree
   - Use recursive traversal to explore all possible starting points

## Solution

The solution uses a **two-step recursive approach**:

### Step 1: Tree Comparison Helper (`is_same_tree`)
```python
def is_same_tree(a: Optional[TreeNode], b: Optional[TreeNode]) -> bool:
    if a == None and b == None:
        return True
    if a == None and b != None:
        return False
    if a != None and b == None:
        return False
    if a.val != b.val:
        return False
    return is_same_tree(a.left, b.left) and is_same_tree(a.right, b.right)
```

**Purpose**: Determines if two binary trees are structurally identical with same values.

**Logic**:
- **Base Case**: Both trees are empty → return `True`
- **Mismatch Cases**: One tree is empty while other isn't → return `False`
- **Value Check**: If current node values differ → return `False`
- **Recursive Check**: Both left and right subtrees must be identical

**Time Complexity**: O(min(m,n)) where m and n are sizes of the two trees being compared.

### Step 2: Main Subtree Search (`isSubtree`)
```python
def isSubtree(self, root: Optional[TreeNode], subRoot: Optional[TreeNode]) -> bool:
    if subRoot == None:
        return True
    if root == None:
        return False
    if root.val == subRoot.val:
        if is_same_tree(root, subRoot):
            return True
    return self.isSubtree(root.left, subRoot) or self.isSubtree(root.right, subRoot)
```

**Purpose**: Searches for `subRoot` within `root` by checking every possible starting node.

**Logic**:
1. **Edge Cases**: 
   - Empty `subRoot` → return `True` (empty tree is subtree of any tree)
   - Empty `root` with non-empty `subRoot` → return `False`

2. **Potential Match**: If current node value equals `subRoot`'s root value:
   - Check if trees starting from this point are identical
   - If yes, we found the subtree → return `True`

3. **Continue Search**: Recursively search in left and right subtrees
   - Use OR logic: subtree can be found in either left OR right branch

### Algorithm Flow:
1. Start from root of main tree
2. For each node, check if it could be the start of the subtree
3. If values match, perform complete tree comparison
4. If not found at current node, recursively search left and right children
5. Return `True` if found anywhere, `False` otherwise

### Complexity Analysis:
- **Time Complexity**: O(m × n) in worst case
  - m = number of nodes in main tree
  - n = number of nodes in subtree
  - For each of m nodes, we might do n comparisons
- **Space Complexity**: O(max(m,n)) for recursion stack
  - In worst case (skewed tree), recursion depth equals tree height

### Example Walkthrough:
For `root = [3,4,5,1,2]` and `subRoot = [4,1,2]`:
1. Start at node 3: value doesn't match subRoot (4)
2. Search left child (node 4): value matches!
3. Compare trees starting from node 4: `[4,1,2]` matches `[4,1,2]` ✓
4. Return `True`

# Tags
- Binary Tree
- Tree Traversal
- Recursion
- Tree Comparison

