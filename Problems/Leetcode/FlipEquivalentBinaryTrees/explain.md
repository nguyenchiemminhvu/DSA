## Problem

https://leetcode.com/problems/flip-equivalent-binary-trees/description/

For a binary tree `T`, a **flip operation** is defined as: choose any node, and swap its left and right child subtrees.

A binary tree `X` is **flip equivalent** to a binary tree `Y` if and only if we can make `X` equal to `Y` after some number of flip operations.

Given the roots of two binary trees `root1` and `root2`, return `true` if the two trees are flip equivalent, or `false` otherwise.

**Examples:**

```
Input: root1 = [1,2,3,4,5,6,null,null,null,7,8], root2 = [1,3,2,null,6,4,5,null,null,null,null,8,7]
Output: true
Explanation: We flipped at nodes with values 1, 3, and 5.

Input: root1 = [], root2 = []
Output: true

Input: root1 = [], root2 = [1]
Output: false
```

**Constraints:**
- The number of nodes in each tree is in the range `[0, 100]`.
- Each tree will have **unique** node values in the range `[0, 99]`.

---

## Ideas

### Key Observation

At each node, we have exactly **two choices** when comparing `root1` and `root2`:
1. **No flip** — the left child of `root1` matches the left child of `root2`, AND the right child of `root1` matches the right child of `root2`.
2. **Flip** — the left child of `root1` matches the **right** child of `root2`, AND the right child of `root1` matches the **left** child of `root2`.

If either choice leads to a full match recursively, the trees are flip equivalent.

---

### Approach 1: Recursive DFS (Top-down)

**Idea:**  
Recursively compare the two trees. At each pair of nodes `(n1, n2)`:
- If both are `null` → return `true`.
- If one is `null` or their values differ → return `false`.
- Otherwise, try both the **no-flip** and **flip** combinations for the children and return `true` if either works.

```
flipEquiv(n1, n2):
    if n1 == null and n2 == null → true
    if n1 == null or n2 == null → false
    if n1.val != n2.val         → false

    // No flip: left-left, right-right
    no_flip = flipEquiv(n1.left, n2.left) AND flipEquiv(n1.right, n2.right)
    // Flip:    left-right, right-left
    flip    = flipEquiv(n1.left, n2.right) AND flipEquiv(n1.right, n2.left)

    return no_flip OR flip
```

**Complexity:**
- Time: `O(min(N1, N2))` — we stop as soon as a mismatch is found.
- Space: `O(min(H1, H2))` — recursion stack depth proportional to tree height.

---

### Approach 2: Canonical Form (Sorting children sets)

**Idea:**  
Transform each tree into a **canonical form** by enforcing a consistent ordering of children at every node. Since node values are unique, at each node we sort the two children so that the child with the **smaller root value** always goes to the left (use `null` as infinity or `INT_MAX`).

After canonicalizing both trees independently, they must be **structurally identical** if they are flip equivalent.

```
canonicalize(node):
    if node == null → return
    canonicalize(node.left)
    canonicalize(node.right)

    left_val  = (node.left  != null) ? node.left.val  : INT_MAX
    right_val = (node.right != null) ? node.right.val : INT_MAX

    if left_val > right_val:
        swap(node.left, node.right)  // enforce canonical order
```

Then compare the two canonicalized trees with a standard tree equality check.

**Complexity:**
- Time: `O(N1 + N2)` — one full traversal of each tree.
- Space: `O(H1 + H2)` — recursion stack.

---

### Comparison

| Approach | Time | Space | Notes |
|---|---|---|---|
| Recursive DFS | `O(min(N1,N2))` | `O(min(H1,H2))` | Simple, early termination |
| Canonical Form | `O(N1 + N2)` | `O(H1 + H2)` | Two-pass, clear separation of concerns |

**Recommended:** Approach 1 (Recursive DFS) — concise, efficient, and directly models the problem definition.

