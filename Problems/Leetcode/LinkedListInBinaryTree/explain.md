## Problem

https://leetcode.com/problems/linked-list-in-binary-tree/description/

**Given:**
- A binary tree with `root` as the root node
- A linked list with `head` as the first node

**Task:** Determine if all elements in the linked list (starting from `head`) correspond to some **downward path** in the binary tree.

A **downward path** is a path that:
- Starts at some node in the tree
- Goes downwards (parent → child direction only)
- Values must match consecutively

Return `True` if such a path exists, otherwise `False`.

### Examples

**Example 1:**
```
Input: head = [4,2,8], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
Output: true
Explanation: The path 4→2→8 exists in the tree
```

**Example 2:**
```
Input: head = [1,4,2,6], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
Output: true
```

**Example 3:**
```
Input: head = [1,4,2,6,8], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
Output: false
Explanation: No complete path contains all elements [1,4,2,6,8]
```

### Constraints
- Tree nodes: `[1, 2500]`
- List nodes: `[1, 100]`
- Node values: `1 <= Node.val <= 100`

## Observations

1. **Two-Level Search Required:**
   - First level: Find potential starting points in the tree (any node whose value matches `head.val`)
   - Second level: Once a starting point is found, verify if the entire linked list path exists from that point downward

2. **Recursive Nature:**
   - The problem naturally fits a recursive approach for both tree traversal and path matching
   - Need to explore all possible starting nodes in the tree

3. **Downward Path Constraint:**
   - Once we start matching from a tree node, we can only go to its left or right children
   - We cannot backtrack or move sideways

4. **Early Termination Conditions:**
   - If we reach the end of the linked list (`head == None`), we've found a valid path → return `True`
   - If we reach a tree leaf but haven't finished the list → return `False`
   - If values don't match → return `False`

5. **Multiple Attempts Needed:**
   - If matching fails at one tree node, we need to try other nodes
   - Must explore the entire tree to find all potential starting points

## Solution

### Approach: Two-Function Recursion

The solution uses two recursive functions working together:

#### 1. Main Function: `isSubPath(head, root)`
**Purpose:** Traverse the entire binary tree to find potential starting points

**Logic:**
- Base case: If `root` is `None`, return `False` (no tree to search)
- Try to match the path starting from the current `root` node using `traversal()`
- If match succeeds, return `True`
- Otherwise, recursively search in left and right subtrees
- Return `True` if either subtree contains the path

#### 2. Helper Function: `traversal(root, head)`
**Purpose:** Check if the linked list matches a downward path starting from a specific tree node

**Logic:**
- Base case 1: If `head` is `None`, we've matched the entire list → return `True`
- Base case 2: If `root` is `None` but list isn't finished → return `False`
- Base case 3: If values don't match (`root.val != head.val`) → return `False`
- Recursive case: If values match, try to continue matching in left OR right child
- Return `True` if either child path completes the match

### Algorithm Walkthrough

```
For head = [4,2,8], root = [1,4,4,null,2,2,...]

1. Start at root (val=1)
   - traversal(1, 4): 1 ≠ 4, return False
   - Search left subtree (val=4)
   
2. At node (val=4, left child of root)
   - traversal(4, 4): Match! 
   - Continue: traversal(2, 2): Match!
   - Continue: traversal(8, 8): Match!
   - head reaches None → return True ✓

Path found: 4 → 2 → 8
```

### Code Explanation

```python
class Solution:
    def isSubPath(self, head, root):
        # Helper: check if path matches from specific node
        def traversal(root, head):
            if not head:           # Matched entire list
                return True
            if not root:           # Tree ended, list didn't
                return False
            if root.val != head.val:  # Values don't match
                return False
            # Try both children (continue downward)
            return traversal(root.left, head.next) or \
                   traversal(root.right, head.next)
        
        # Main: try all tree nodes as starting points
        if not root:
            return False
        if traversal(root, head):  # Try current node
            return True
        # Try left and right subtrees
        return self.isSubPath(head, root.left) or \
               self.isSubPath(head, root.right)
```

### Why This Works

1. **Exhaustive Search:** We check every node in the tree as a potential starting point
2. **Path Validation:** For each starting point, we verify the complete linked list sequence
3. **Backtracking:** If one path fails, we automatically try other branches
4. **Early Success:** As soon as we find one valid path, we return `True`

### Complexity Analysis

**Time Complexity: O(N × min(L, H))**
- **N** = number of nodes in the binary tree
- **L** = length of the linked list
- **H** = height of the tree
- We visit each tree node once: O(N)
- At each node, we potentially run `traversal()` which can go up to min(L, H) depth
- Worst case: O(N × L) when the tree is highly unbalanced

**Space Complexity: O(H)**
- **H** = height of the binary tree
- Recursion stack depth for tree traversal: O(H)
- Additional stack for path matching: O(min(L, H))
- Total: O(H) for balanced trees, O(N) for skewed trees

### Key Takeaways

✅ Use nested recursion for two-level search problems (find + validate)  
✅ Separate concerns: One function for traversal, one for matching  
✅ Trust the recursion: Each function handles its specific task  
✅ Early termination: Return immediately when conditions are met  
✅ Explore all possibilities: Use OR logic to try multiple branches

# Tags

Tree, Linked List, DFS, Recursion

