## Problem

https://leetcode.com/problems/serialize-and-deserialize-bst/description/

```
Serialization is converting a data structure or object into a sequence of bits so that it can be stored
in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in
the same or another computer environment.

Design an algorithm to serialize and deserialize a binary search tree. There is no restriction on how
your serialization/deserialization algorithm should work. You need to ensure that a BST can be serialized
to a string, and this string can be deserialized to the original tree structure.

The encoded string should be as compact as possible.

Example 1:
Input: root = [2,1,3]
Output: [2,1,3]

Example 2:
Input: root = []
Output: []

Constraints:
- The number of nodes in the tree is in the range [0, 10^4].
- 0 <= Node.val <= 10^4
- The input tree is guaranteed to be a binary search tree.
```

## Observations

1. **BST Property is Key**: Unlike a general binary tree, a BST can be uniquely reconstructed from just its **preorder traversal**. There is no need to store `null` markers, making the encoding more compact.

2. **Why Preorder Works**: In preorder traversal, the first element is always the root. For any subsequent elements, values less than the root belong to the left subtree and values greater belong to the right subtree — this is guaranteed by the BST invariant.

3. **Compactness**: Instead of encoding `null` nodes (as required for a general binary tree), we only store actual node values. For `N` nodes, this saves up to `N+1` null markers.

4. **Encoding Format**: Node values can be stored as space-separated integers (or with any delimiter). Since values are bounded `[0, 10^4]`, they fit in 2 bytes each, allowing an even more compact binary encoding.

5. **Reconstruction Invariant**: During deserialization, at each recursive step we maintain a valid `[min, max]` range. A value is assigned to the current position only if it falls within the allowed range; otherwise we backtrack (no node is created there).

6. **Edge Cases**:
   - Empty tree → empty string → return `nullptr`
   - Single node tree
   - Skewed BST (all left or all right)

## Ideas

### Idea 1: Preorder Traversal (Compact, No Null Markers)

**Serialization**:
- Perform a **preorder DFS** on the BST.
- Append each node value (as a string) separated by spaces.
- Result: a flat sequence of integers, e.g., `"2 1 3"`.

**Deserialization**:
- Parse the string back into a list/queue of integers.
- Reconstruct recursively using a helper that accepts `[min, max]` bounds:
  - If the queue is empty or the front value is outside `[min, max]`, return `nullptr`.
  - Otherwise, consume the front value as the current node, then recurse for left `[min, val)` and right `(val, max]`.

**Time Complexity**: `O(N)` for both serialize and deserialize.  
**Space Complexity**: `O(N)` for the output string and recursion stack.

```
serialize([2,1,3]) → "2 1 3"

deserialize("2 1 3"):
  root = 2, range [-inf, +inf]
    left  = 1, range [-inf, 2)  → leaf
    right = 3, range (2, +inf]  → leaf
```

---

### Idea 2: Level-Order (BFS) Traversal

**Serialization**:
- Perform **BFS** and store values level by level (skip null nodes).

**Deserialization**:
- For each stored value, insert it into the BST using standard BST insertion.
- Because insertion order follows level-order, the tree shape is perfectly reproduced.

**Time Complexity**: `O(N log N)` for deserialization due to repeated BST insertions (O(N²) worst case on skewed tree).  
**Space Complexity**: `O(N)`.

> ⚠️ Less efficient than Idea 1 for deserializing; not preferred when compactness and speed both matter.

---

### Recommended Approach

**Idea 1 (Preorder + range-bounded reconstruction)** is optimal:
- Most compact encoding (no null markers).
- Linear time for both operations.
- Directly exploits the BST invariant.

## Tags

tree, bst, dfs, bfs, serialization, design

