## Problem

https://leetcode.com/problems/delete-nodes-and-return-forest/description/

Given the root of a binary tree where each node has a **distinct value**, delete all nodes whose values appear in `to_delete`. Return the roots of the trees in the remaining forest (disjoint union of trees).

**Example 1:**
```
Input:  root = [1,2,3,4,5,6,7], to_delete = [3,5]
Output: [[1,2,null,4],[6],[7]]
```

**Example 2:**
```
Input:  root = [1,2,4,null,3], to_delete = [3]
Output: [[1,2,4]]
```

**Constraints:**
- Number of nodes ≤ 1000
- Each node value is distinct, between 1 and 1000
- `to_delete.length` ≤ 1000

---

## Observations

1. **Deleting a node creates new roots.** When a node is deleted, its children (if any) become roots of new subtrees — they are no longer connected to the rest of the tree above.

2. **The original root may itself be deleted.** So we cannot blindly add `root` to the result; we only add a node to the result if it is a root *and* it is not deleted.

3. **We need to process bottom-up (post-order).** To correctly detach children before deciding what to return to the parent, we recurse into children first, then handle the current node. This ensures:
   - A child's subtree is cleaned up before we sever the link.
   - When we return `None` for a deleted node, the parent's `.left` / `.right` pointer is automatically nullified.

4. **A node becomes a new root when its parent is deleted.** We track this with an `is_root` flag passed down: the original root starts as `is_root=True`; when a node is deleted, its children are called with `is_root=True`.

5. **Using a set for `to_delete`** gives O(1) lookup per node, keeping overall complexity at **O(N)** time and **O(N)** space (call stack + set).

---

## Solution Explanation

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def delNodes(self, root: Optional[TreeNode], to_delete: List[int]) -> List[TreeNode]:
        res = []

        delete_set = set(to_delete)          # O(1) membership test

        def helper(root: Optional[TreeNode], is_root: bool) -> Optional[TreeNode]:
            if not root:
                return None

            is_deleted = root.val in delete_set

            # Recurse into children FIRST (post-order).
            # If the current node is deleted, its children become new roots.
            root.left  = helper(root.left,  is_deleted)
            root.right = helper(root.right, is_deleted)

            # A node is added to the result only if it is a root AND not deleted.
            if is_root and not is_deleted:
                res.append(root)

            # Return None if deleted so the parent severs the pointer automatically.
            if is_deleted:
                return None
            return root

        helper(root, True)   # The original root is a root by definition
        return res
```

### Step-by-step walkthrough (Example 1)

```
Tree:          to_delete = {3, 5}
       1
      / \
     2   3
    / \ / \
   4  5 6  7
```

| Call | Node | is_root | is_deleted | Action |
|------|------|---------|------------|--------|
| helper(4, False) | 4 | F | F | return node 4 |
| helper(5, False) | 5 | F | T | children → helper(None, True), helper(None, True); return None |
| helper(2, False) | 2 | F | F | left=4, right=None; return node 2 |
| helper(6, True)  | 6 | T | F | add 6 to res; return node 6 |
| helper(7, True)  | 7 | T | F | add 7 to res; return node 7 |
| helper(3, False) | 3 | F | T | left=helper(6,**True**), right=helper(7,**True**); return None |
| helper(1, True)  | 1 | T | F | left=2, right=None; add 1 to res; return node 1 |

**Result:** roots of subtrees rooted at `1` (containing 1,2,4), `6`, and `7`.

### Key insight summary

```
is_root=True  ──► node is a candidate to add to result
is_deleted=True ──► sever from parent (return None) + promote children to roots
Post-order traversal ──► children are cleaned up before parent decides
```

### Complexity

| | |
|---|---|
| **Time** | O(N) — each node visited once |
| **Space** | O(N) — recursion stack (height of tree) + delete set |
