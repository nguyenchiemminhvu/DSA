## Problem

https://leetcode.com/problems/complete-binary-tree-inserter/description/

Design an algorithm to insert a new node into a **complete binary tree** while keeping it complete after every insertion.

A **complete binary tree** is a binary tree where every level, except possibly the last, is completely filled, and all nodes on the last level are as far **left** as possible.

Implement the `CBTInserter` class:

- `CBTInserter(TreeNode root)` — Initializes the data structure with the root of the complete binary tree.
- `int insert(int val)` — Inserts a `TreeNode` with `Node.val == val` so that the tree remains complete, and returns the **value of the parent** of the inserted node.
- `TreeNode get_root()` — Returns the root node of the tree.

**Constraints:**
- The number of nodes in the tree will be in the range `[1, 1000]`
- `0 <= Node.val <= 5000`
- `root` is a complete binary tree
- `0 <= val <= 5000`
- At most `10^4` calls will be made to `insert` and `get_root`

**Examples:**

1. **Example 1:**
   - Input: `["CBTInserter", "insert", "insert", "get_root"]` with args `[[[1, 2]], [3], [4], []]`
   - Output: `[null, 1, 2, [1, 2, 3, 4]]`
   - Explanation:
     - `CBTInserter([1, 2])` — builds the tree with root=1, left=2
     - `insert(3)` → inserts 3 as right child of 1, returns **1**
     - `insert(4)` → inserts 4 as left child of 2, returns **2**
     - `get_root()` → returns `[1, 2, 3, 4]`

## Ideas

### Key Observations

1. **Where to insert?** In a complete binary tree, the next insertion point is always the **leftmost available position** on the last level, or the leftmost position on a new level if the last level is full.

2. **Finding the insertion candidate:** A node is an **insertion candidate** if it is missing at least one child — i.e., it has no left child or no right child. The next node to receive a child is always the **first such node in BFS (level-order) order**.

3. **Efficient candidate tracking:** Instead of doing a full BFS scan on every `insert()`, we can maintain a **queue of candidate parents** (nodes that still have room for a child). During initialization we populate this queue by doing a BFS over the existing tree and enqueuing every node that lacks a left or right child.

### Approach — BFS Candidate Queue

**Initialization (`__init__` / constructor):**
- Perform a BFS (level-order traversal) over the initial tree.
- Push every node that is missing a child into a **deque** called `candidates`.

**Insert (`insert(val)`):**
1. Create a new `TreeNode(val)`.
2. Peek at the **front** of `candidates` — this is the parent.
3. Attach the new node as the **left child** if the parent has none, otherwise as the **right child**.
4. Push the new node into `candidates` (it may receive children later).
5. If the parent now has **both children**, pop it from the front of `candidates`.
6. Return the parent's value.

**Get Root (`get_root()`):**
- Simply return the stored root.

### Complexity

| Operation | Time | Space |
|-----------|------|-------|
| `__init__` | $O(n)$ | $O(n)$ — BFS queue + candidates deque |
| `insert` | $O(1)$ | $O(1)$ per call |
| `get_root` | $O(1)$ | $O(1)$ |

### Step-by-Step Walkthrough (Example 1)

**Initial tree:** `[1, 2]`

```
    1
   /
  2
```

After BFS initialization, `candidates = [1, 2]` — node 1 has no right child, node 2 has no children.

**`insert(3)`:**
- Front of candidates = node 1 (missing right child)
- Attach 3 as right child of 1
- Push node 3 into candidates
- Node 1 now has both children → pop it → `candidates = [2, 3]`
- Return **1**

```
    1
   / \
  2   3
```

**`insert(4)`:**
- Front of candidates = node 2 (missing left child)
- Attach 4 as left child of 2
- Push node 4 into candidates
- Node 2 still has no right child → keep it → `candidates = [2, 3, 4]`
- Return **2**

```
    1
   / \
  2   3
 /
4
```

**`get_root()`** → returns root node with value 1.

### Alternative Approach — Array / Index Math

A complete binary tree of $n$ nodes can be represented as a 1-indexed array where:
- Node at index $i$ has its **parent** at index $\lfloor i/2 \rfloor$.
- The next insertion index is $n + 1$.

During initialization, store all nodes in a list (BFS order). On each `insert`:
1. Append the new node to the list.
2. Its parent is at index `(len(nodes) - 1) // 2` (0-indexed).
3. Attach the new node as left or right child based on whether the new index is even or odd.

This approach uses the same $O(n)$ space and $O(1)$ insert time, but the BFS candidate queue is more intuitive.

# Tags

- Binary Tree
- Complete Binary Tree
- Breadth-First Search (BFS)
- Design / Data Structure
- Queue
- LeetCode Medium

