## Problem

https://leetcode.com/problems/smallest-string-starting-from-leaf/description/

You are given the root of a binary tree where each node has a value in the range `[0, 25]` representing the letters `'a'` to `'z'`.

Return the **lexicographically smallest string** that starts at a leaf of this tree and ends at the root.

**Important Notes:**
- Any shorter prefix of a string is lexicographically smaller. For example, `"ab"` is lexicographically smaller than `"aba"`.
- A leaf is a node that has no children.

### Example 1:
```
Input: root = [0,1,2,3,4,3,4]
Output: "dba"

Tree structure:
       a(0)
      /   \
    b(1)   c(2)
   /  \    /  \
  d(3) e(4) d(3) e(4)

Paths from leaf to root:
- d -> b -> a = "dba"
- e -> b -> a = "eba"
- d -> c -> a = "dca"
- e -> c -> a = "eca"

Smallest: "dba"
```

### Example 2:
```
Input: root = [25,1,3,1,3,0,2]
Output: "adz"
```

### Example 3:
```
Input: root = [2,2,1,null,1,0,null,0]
Output: "abc"
```

### Constraints:
- The number of nodes in the tree is in the range `[1, 8500]`
- `0 <= Node.val <= 25`

## Observations

1. **Direction Matters**: The string is built from **leaf to root**, not root to leaf. This means we need to reverse or prepend characters as we traverse down the tree.

2. **Leaf Nodes Only**: We only consider complete paths that start at leaf nodes (nodes with no children). Paths ending at internal nodes are not valid.

3. **Lexicographical Comparison**: We need to compare all possible leaf-to-root paths and return the smallest one lexicographically. We cannot use a greedy approach because the lexicographic ordering depends on the entire string.

4. **Character Mapping**: Each node value `val` maps to a character: `chr(val + ord('a'))`, where:
   - 0 → 'a'
   - 1 → 'b'
   - 25 → 'z'

5. **All Paths Required**: We must explore all paths to leaves because:
   - Shorter paths are NOT always lexicographically smaller
   - Local decisions cannot determine global minimum
   - Example: "ba" > "aaa" despite "ba" being shorter

6. **String Building Strategy**: Since we traverse root-to-leaf but need leaf-to-root strings, we can:
   - Collect node values during traversal, then reverse at leaves
   - Or prepend characters as we build the path

## Solution

### Approach: DFS with Path Collection

The solution uses **Depth-First Search (DFS)** to:
1. Traverse all paths from root to leaves
2. Build strings from leaf to root by prepending characters
3. Collect all valid leaf-to-root strings
4. Return the lexicographically smallest one

### Algorithm Steps:

1. **Initialize**: Create an array `arr` to store all leaf-to-root strings

2. **DFS Traversal**: Use a helper function `traversal(root, tmp)`:
   - `root`: current node being visited
   - `tmp`: list of node values from current node's parent back to root

3. **Base Cases**:
   - If node is `None`, return (invalid path, backtrack)
   - If node is a leaf (no left and right children):
     - Build string by prepending current node's character to the accumulated path
     - Convert all values to characters: current node + all values in `tmp`
     - Add the complete string to `arr`
     - Return (backtrack to explore other paths)

4. **Recursive Case** (internal node):
   - Prepend current node's value to `tmp` list
   - Recursively traverse left subtree with updated path
   - Recursively traverse right subtree with updated path

5. **Return Result**: Use `min(arr)` to find lexicographically smallest string

### Code Implementation:

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def smallestFromLeaf(self, root: Optional[TreeNode]) -> str:
        arr = []
        
        def traversal(root: Optional[TreeNode], tmp: List[str]) -> None:
            # Base case: null node
            if not root:
                return
            
            # Base case: leaf node - construct the path string
            if not root.left and not root.right:
                # Build string from leaf to root
                # Current node's character + all parent values converted to chars
                s = "".join([chr(root.val + ord('a'))] + [chr(val + ord('a')) for val in tmp])
                arr.append(s)
                return
            
            # Recursive case: traverse left and right subtrees
            # Prepend current node value to the path
            traversal(root.left, [root.val] + tmp)
            traversal(root.right, [root.val] + tmp)
        
        traversal(root, [])
        return min(arr)
```

### How It Works - Example Walkthrough:

For `root = [0,1,2,3,4,3,4]`:

```
       a(0)
      /   \
    b(1)   c(2)
   /  \    /  \
  d(3) e(4) d(3) e(4)
```

**Execution Trace:**

1. Start at root (val=0), tmp=[]
2. Go left to node (val=1), tmp=[0]
3. Go left to leaf (val=3), tmp=[1,0]
   - Build string: 'd' + 'b' + 'a' = "dba"
   - Add "dba" to arr
4. Backtrack to node (val=1), try right
5. Go right to leaf (val=4), tmp=[1,0]
   - Build string: 'e' + 'b' + 'a' = "eba"
   - Add "eba" to arr
6. Backtrack to root, try right
7. Go right to node (val=2), tmp=[0]
8. Go left to leaf (val=3), tmp=[2,0]
   - Build string: 'd' + 'c' + 'a' = "dca"
   - Add "dca" to arr
9. Go right to leaf (val=4), tmp=[2,0]
   - Build string: 'e' + 'c' + 'a' = "eca"
   - Add "eca" to arr

**Final arr:** ["dba", "eba", "dca", "eca"]
**Result:** min(arr) = "dba" ✓

### Complexity Analysis:

**Time Complexity: O(N * H)**
- N = number of nodes in the tree
- H = height of the tree
- We visit each node exactly once: O(N)
- At each leaf, we construct a string of length at most H: O(H)
- In worst case with many leaves: O(N * H)
- Finding minimum among all strings: O(L * H) where L = number of leaves

**Space Complexity: O(N * H)**
- Recursion call stack depth: O(H)
- Storing all leaf-to-root paths: O(L * H) where L is number of leaves
- In worst case (skewed tree): L ≈ 1, H ≈ N, giving O(N)
- In average case (balanced tree): L ≈ N/2, H ≈ log N, giving O(N log N)

### Alternative Optimization - Early Pruning:

Instead of collecting all strings and finding minimum at the end, maintain a running minimum:

```python
def smallestFromLeaf(self, root: Optional[TreeNode]) -> str:
    self.result = None
    
    def dfs(node, path):
        if not node:
            return
        
        # Build path from leaf to root
        path = chr(node.val + ord('a')) + path
        
        # If we reached a leaf, compare with current result
        if not node.left and not node.right:
            if self.result is None or path < self.result:
                self.result = path
            return
        
        # Continue exploring
        dfs(node.left, path)
        dfs(node.right, path)
    
    dfs(root, "")
    return self.result
```

**Benefits:**
- Avoids storing all paths in memory
- Compares strings incrementally
- Same time complexity but better space usage
- Can potentially prune early if we track minimum prefix

### Edge Cases:

1. **Single Node Tree**: Root is also a leaf
   - Input: `[0]` → Output: `"a"`

2. **Skewed Tree**: Only left or right children
   - Input: `[0,1,null,2]` → Output: `"cba"`

3. **All Same Values**: Multiple identical paths
   - Input: `[0,0,0]` → All paths are `"aa"`, return `"aa"`

4. **Different Depth Leaves**: Shorter path might not be smallest
   - Must check all paths completely, no early termination

### Common Mistakes:

1. ❌ **Building from root to leaf instead of leaf to root**
2. ❌ **Using greedy approach** (choosing smallest child at each level)
3. ❌ **Comparing incomplete paths** (must wait until reaching leaves)
4. ❌ **Forgetting to handle null nodes** in traversal
5. ❌ **Not considering all paths** (early termination based on partial comparison)

# Tags
Binary Tree, Depth-First Search (DFS), String, Tree Traversal, Path Finding, Lexicographic Ordering

