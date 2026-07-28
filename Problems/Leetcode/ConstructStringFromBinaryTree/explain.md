````markdown
## Problem

```
Given the root node of a binary tree, your task is to create a string representation of the tree
following a specific set of formatting rules. The representation should be based on a preorder
traversal of the binary tree and must adhere to the following guidelines:

Node Representation: Each node in the tree should be represented by its integer value.

Parentheses for Children:
  - If a node has a left child, enclose its value inside parentheses immediately after the node's value.
  - If a node has a right child, enclose its value inside parentheses after the left child's parentheses.

Omitting Empty Parentheses:
  - Omit empty parentheses () when a node has only a left child or no children at all.
  - Keep empty parentheses () when a node has a right child but NO left child, to preserve structure.

Example 1:
  Input:  root = [1,2,3,4]
  Output: "1(2(4))(3)"
  Explanation: Full form is "1(2(4)())(3()())", but trailing/unnecessary () are omitted.

Example 2:
  Input:  root = [1,2,3,null,4]
  Output: "1(2()(4))(3)"
  Explanation: The () after 2 is required to indicate the absence of a left child
               while a right child (4) exists.

Constraints:
  - The number of nodes in the tree is in the range [1, 10^4].
  - -1000 <= Node.val <= 1000
```

## Observations

1. **Preorder Traversal**: The string is built by visiting the current node first, then left subtree, then right subtree — a natural fit for recursion.

2. **Rule for Parentheses**:
   - Both children absent → just the node value, no parentheses.
   - Only left child → `val(left_str)`, right parentheses omitted.
   - Only right child → `val()(right_str)`, empty `()` is mandatory to mark the absent left child.
   - Both children → `val(left_str)(right_str)`.

3. **Key Insight**: The omission rule is purely about whether information would be lost. Trailing empty parentheses (right child absent) are always safe to drop; a missing left-child marker is not safe to drop when a right child exists.

4. **Base Case**: A `None` node contributes an empty string `""`.

## Solution

The solution uses **recursive preorder DFS**:

### Algorithm Steps:

1. **Base Case**: If `root` is `None`, return `""`.

2. **Build result string** starting with `str(root.val)`.

3. **Check children** using the four cases above:
   - **No children**: return `str(root.val)` as-is.
   - **Only left child**: return `val + "(" + left_str + ")"`.
   - **Only right child**: return `val + "()" + "(" + right_str + ")"`.
   - **Both children**: return `val + "(" + left_str + ")" + "(" + right_str + ")"`.

4. The recursion handles subtrees identically, so no special logic is needed beyond the four cases.

### Example Walkthrough (root = [1,2,3,null,4]):

```
tree2str(1)
  → "1" + tree2str(2) + tree2str(3)
  → "1" + "(2()(4))" + "(3)"
  → "1(2()(4))(3)"

tree2str(2) — left=None, right=4
  → only right child case: "2" + "()" + "(" + tree2str(4) + ")"
  → "2()(4)"

tree2str(3) — left=None, right=None
  → no children: "3"

tree2str(4) — leaf
  → "4"
```

### Time Complexity: O(N)
- Each node is visited exactly once.

### Space Complexity: O(H)
- Recursion stack depth equals the height `H` of the tree.
- O(N) in the worst case for a skewed tree.

## Tags

string, binary tree, dfs, recursion
````
