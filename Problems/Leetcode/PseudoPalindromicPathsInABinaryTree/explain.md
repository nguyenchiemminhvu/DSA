## Problem

https://leetcode.com/problems/pseudo-palindromic-paths-in-a-binary-tree/description/

Given a binary tree where node values are digits from **1 to 9**. A path in the binary tree is said to be **pseudo-palindromic** if at least one permutation of the node values in the path is a palindrome.

Return the number of pseudo-palindromic paths going from the root node to leaf nodes.

**Example 1:**
```
Input: root = [2,3,1,3,1,null,1]
Output: 2
Explanation: Three root-to-leaf paths exist:
  - [2,3,3] → can be rearranged to [3,2,3] ✓ pseudo-palindromic
  - [2,1,1] → can be rearranged to [1,2,1] ✓ pseudo-palindromic
  - [2,3,1] → no valid palindrome permutation ✗
```

**Example 2:**
```
Input: root = [2,1,1,1,3,null,null,null,null,null,1]
Output: 1
Explanation: Three root-to-leaf paths exist:
  - [2,1,1] → can be rearranged to [1,2,1] ✓ pseudo-palindromic
  - [2,1,3,1] → no valid palindrome permutation ✗
  - [2,1] → no valid palindrome permutation ✗
```

**Example 3:**
```
Input: root = [9]
Output: 1
```

**Constraints:**
- The number of nodes in the tree is in the range `[1, 10^5]`
- `1 <= Node.val <= 9`

## Observations

1. **Palindrome condition on frequencies:**
   A sequence can form a palindrome if and only if **at most one digit has an odd frequency**. For example:
   - `[2,3,3]` → freq: {2:1, 3:2} → one odd-count digit (2) → valid palindrome permutation
   - `[2,3,1]` → freq: {2:1, 3:1, 1:1} → three odd-count digits → invalid

2. **Bitmask to track parity:**
   Since node values are strictly in `[1..9]`, we can use a 9-bit integer as a bitmask where bit `i` represents whether digit `i` has been seen an **odd** number of times so far on the current path.
   - Visit a node with value `v` → toggle bit `v`: `mask ^= (1 << v)`
   - At a leaf, the path is pseudo-palindromic if **at most one bit is set**: `mask == 0` or `mask & (mask - 1) == 0`

3. **DFS traversal:**
   Perform a DFS from root to leaves, carrying the bitmask along the path. When we backtrack, toggle the bit again to restore the previous state.

4. **Why XOR works perfectly here:**
   XOR naturally tracks parity. Toggling the same bit twice cancels out, so the mask always reflects which digits appear an odd number of times on the current root-to-current-node path.

## Solution

### Approach: DFS with Bitmask

**Algorithm:**
```cpp
class Solution {
public:
    int pseudoPalindromicPaths(TreeNode* root) {
        int count = 0;
        dfs(root, 0, count);
        return count;
    }

private:
    void dfs(TreeNode* node, int mask, int& count) {
        if (!node) return;

        mask ^= (1 << node->val);  // toggle bit for current digit

        if (!node->left && !node->right) {
            // leaf node: check if at most one bit is set
            if (mask == 0 || (mask & (mask - 1)) == 0)
                count++;
            return;
        }

        dfs(node->left,  mask, count);
        dfs(node->right, mask, count);
        // no need to explicitly untoggle: mask is passed by value
    }
};
```

**Step-by-Step Trace on Example 1:** `root = [2,3,1,3,1,null,1]`

```
Start: mask = 0b000000000

Visit 2:  mask = 0b000000100  (bit 2 set)
  Visit 3:  mask = 0b000001100  (bit 3 set)
    Visit 3:  mask = 0b000000100  (bit 3 toggled off → only bit 2 set)
      Leaf! mask = 0b000000100 → one bit set → pseudo-palindromic ✓  count=1
    Visit 1:  mask = 0b000001110  (bit 1 set)
      Leaf! mask = 0b000001110 → multiple bits set → not pseudo-palindromic ✗
  Visit 1:  mask = 0b000000110  (bit 1 set)
    Visit 1:  mask = 0b000000100  (bit 1 toggled off → only bit 2 set)
      Leaf! mask = 0b000000100 → one bit set → pseudo-palindromic ✓  count=2
    Visit 1:  mask = 0b000000110  (bit 1 set)
      Leaf! [2,1,1] but wait — this is the right child path...

Final Answer: 2
```

**Key Insight — `mask & (mask - 1) == 0`:**
This is a classic bit trick to check if at most one bit is set:
- `mask = 0b000000100` → `mask - 1 = 0b000000011` → AND = `0b000000000` = 0 ✓
- `mask = 0b000001100` → `mask - 1 = 0b000001011` → AND = `0b000001000` ≠ 0 ✗

**Complexity:**
- **Time:** O(N) — each node is visited exactly once
- **Space:** O(H) — recursion stack depth equals the height of the tree; O(log N) for balanced, O(N) worst case

# Tags

`Tree` `Depth-First Search` `Bit Manipulation` `Binary Tree` `Bitmask`

