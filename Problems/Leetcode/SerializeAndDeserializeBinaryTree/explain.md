## Problem

https://leetcode.com/problems/serialize-and-deserialize-binary-tree/description/

```
Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

Clarification: The input/output format is the same as how LeetCode serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.

Example 1:

Input: root = [1,2,3,null,null,4,5]
Output: [1,2,3,null,null,4,5]

Example 2:

Input: root = []
Output: []

Constraints:

The number of nodes in the tree is in the range [0, 104].
-1000 <= Node.val <= 1000
```

## Observations

1. **Problem Nature**: This is a design problem that requires implementing bidirectional conversion between a binary tree data structure and a string representation.

2. **Key Challenges**:
- Must preserve complete tree structure including null nodes
- The serialized format must contain enough information to reconstruct the exact original tree
- Need to handle edge cases like empty trees and single nodes

1. **Critical Insights**:
- **Preorder traversal** is ideal for serialization because it visits root first, making deserialization straightforward
- **Null marker**: Using a special character (like '#') to represent null nodes is essential
- **Delimiter**: A separator (like ',') is needed to distinguish between node values
- **Recursive nature**: Both operations naturally fit recursive implementation

1. **Format Design**:
- Each node value followed by comma separator
- Null nodes represented by '#' marker
- Results in preorder traversal string: "root,left_subtree,right_subtree"

## Solution

### Approach: Preorder Traversal with Null Markers

The solution uses **preorder traversal** (root → left → right) for both serialization and deserialization.

#### Serialization Process:
```
serialize(root):
1. If root is null → return '#'
2. Otherwise → return root.val + ',' + serialize(left) + ',' + serialize(right)
```

#### Deserialization Process:
```
deserialize(data):
1. Split string by comma to get array of tokens
2. Use helper function with array (passed by reference)
3. For each position:
   - If token is '#' → return None
   - Otherwise → create node, recursively build left and right subtrees
```

### Algorithm Analysis:

**Time Complexity**: 
- Serialization: O(n) - visit each node once
- Deserialization: O(n) - process each token once

**Space Complexity**: 
- O(n) for output string
- O(h) recursive call stack where h is tree height

### Key Implementation Details:

1. **Null Handling**: Uses '#' as sentinel for null nodes
2. **Token Processing**: `nodes.pop(0)` removes processed tokens (maintains state)
3. **Type Safety**: Proper type hints for maintainability
4. **String Building**: Direct concatenation for simplicity

### Example Walkthrough:

For tree: `[1,2,3,null,null,4,5]`
```
    1
   / \
  2   3
     / \
    4   5
```

**Serialization**: "1,2,#,#,3,4,#,#,5,#,#"
**Deserialization**: Reconstruct by consuming tokens left-to-right in preorder

### Alternative Approaches:

1. **Level-order (BFS)**: More intuitive but requires handling of trailing nulls
2. **Inorder + Preorder**: Uses two traversals for unique reconstruction
3. **Bracket notation**: Parentheses to denote subtrees

### Edge Cases Handled:
- Empty tree → "#"
- Single node → "val,#,#"  
- Skewed trees → Works correctly due to preorder nature

## Tags

binary tree