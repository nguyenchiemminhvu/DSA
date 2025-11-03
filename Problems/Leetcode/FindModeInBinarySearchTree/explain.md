## Problem

https://leetcode.com/problems/find-mode-in-binary-search-tree/description/

```
Given the root of a binary search tree (BST) with duplicates, return all the mode(s) (i.e., the most frequently occurred element) in it.

If the tree has more than one mode, return them in any order.

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than or equal to the node's key.
The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
Both the left and right subtrees must also be binary search trees.

Example 1:

Input: root = [1,null,2,2]
Output: [2]

Example 2:

Input: root = [0]
Output: [0]

Constraints:

The number of nodes in the tree is in the range [1, 104].
-105 <= Node.val <= 105

Follow up: Could you do that without using any extra space? (Assume that the implicit stack space incurred due to recursion does not count).
```

## Observations

1. **Problem Analysis**: We need to find the mode(s) - the most frequently occurring values in a BST. Multiple modes can exist if they have the same highest frequency.

2. **BST Property**: The problem mentions it's a BST, but the given solution doesn't leverage this property. In a BST, an inorder traversal gives values in sorted order, which could be useful for optimization.

3. **Current Approach**: The solution uses a simple frequency counting approach:
   - Performs inorder traversal to visit all nodes
   - Maintains a frequency dictionary to count occurrences
   - Finds maximum frequency and returns all values with that frequency

4. **Time Complexity**: O(n) where n is the number of nodes
   - One pass to count frequencies
   - One pass to find maximum frequency  
   - One pass to collect all modes

5. **Space Complexity**: O(n) for the frequency dictionary + O(h) for recursion stack where h is height

6. **Follow-up Challenge**: The problem asks if we can solve without extra space. The current solution uses O(n) extra space for the frequency map.

## Solution

### Approach 1: Frequency Counting (Current Implementation)

**Algorithm:**
1. Traverse the entire tree using inorder traversal
2. Count frequency of each value in a dictionary
3. Find the maximum frequency among all values
4. Return all values that have the maximum frequency

**Code Explanation:**
```python
def findMode(self, root: Optional[TreeNode]) -> List[int]:
    def inorder(root: Optional[TreeNode], freq: Dict[int, int]) -> None:
        if root == None:
            return
        inorder(root.left, freq)           # Traverse left subtree
        freq[root.val] = freq.get(root.val, 0) + 1  # Count current node
        inorder(root.right, freq)          # Traverse right subtree
    
    freq = {}                              # Frequency dictionary
    inorder(root, freq)                    # Count all frequencies
    max_f = max(freq.values())             # Find maximum frequency
    return [k for k, v in freq.items() if v == max_f]  # Return all modes
```

**Pros:**
- Simple and straightforward implementation
- Works for any binary tree (not just BST)
- Easy to understand and debug

**Cons:**
- Doesn't utilize BST property
- Uses O(n) extra space
- Makes two passes through the data (once for counting, once for finding max)

### Approach 2: Optimized BST Solution (Space-Efficient)

For the follow-up question about using no extra space, we can leverage the BST property:

**Algorithm:**
1. Use Morris traversal or two-pass inorder traversal
2. Since inorder gives sorted sequence, identical values will be consecutive
3. Track current value, its count, maximum count seen so far, and current modes
4. Update modes list as we find new maximum frequencies

**Key Insights:**
- In BST inorder traversal, duplicate values appear consecutively
- We can process the sorted sequence in one pass
- Only need to store current modes, not all frequencies

**Time Complexity:** O(n)
**Space Complexity:** O(1) auxiliary space (excluding output and recursion stack)

# Tags

- Binary Search Tree
- Tree Traversal
- Inorder Traversal
- Frequency Counting
- Hash Map
- Morris Traversal (for space-optimized solution)

