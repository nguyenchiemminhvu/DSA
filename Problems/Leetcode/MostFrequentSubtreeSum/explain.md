## Problem

https://leetcode.com/problems/most-frequent-subtree-sum/description/

Given the root of a binary tree, return the most frequent subtree sum. If there is a tie, return all the values with the highest frequency in any order.

The **subtree sum** of a node is defined as the sum of all node values in the subtree rooted at that node (including the node itself).

**Example 1:**
```
      5
     / \
    2  -3
```
- Input: `root = [5, 2, -3]`
- Output: `[2, -3, 4]`
- Subtree sums: node `2` → `2`, node `-3` → `-3`, node `5` → `5 + 2 + (-3) = 4`. All appear once, so all are returned.

**Example 2:**
```
      5
     / \
    2  -5
```
- Input: `root = [5, 2, -5]`
- Output: `[2]`
- Subtree sums: node `2` → `2`, node `-5` → `-5`, node `5` → `5 + 2 + (-5) = 2`. Sum `2` appears twice, which is the highest frequency.

**Constraints:**
- The number of nodes is in range `[1, 10^4]`.
- `-10^5 <= Node.val <= 10^5`

---

## Observations

1. **Every node defines a subtree.** The subtree sum at a node equals the sum of its own value plus the subtree sums of its left and right children. This naturally suggests a **post-order DFS** (process children before parent).

2. **Subtree sums can be computed bottom-up.** If we know the subtree sum of the left child and the subtree sum of the right child, the current node's subtree sum is simply:
   $$\text{sum}(node) = node.val + \text{sum}(node.left) + \text{sum}(node.right)$$
   Base case: a `null` node contributes `0`.

3. **Frequency tracking with a hash map.** As we compute each subtree sum, we record its occurrence count in a dictionary. After the full traversal, the answer is the set of keys whose count equals the maximum count.

4. **Time and space complexity:** We visit each node exactly once → $O(N)$ time. The hash map stores at most $N$ distinct sums → $O(N)$ space.

---

## Solution Explanation

```python
from collections import defaultdict
from typing import List, Optional

class Solution:
    def findFrequentTreeSum(self, root: Optional[TreeNode]) -> List[int]:
        freq = defaultdict(int)          # sum -> frequency count

        def dfs(node):
            if not node:
                return 0                 # null node contributes 0

            left  = dfs(node.left)       # subtree sum of left child
            right = dfs(node.right)      # subtree sum of right child

            s = left + right + node.val  # current subtree sum
            freq[s] += 1                 # record this sum
            return s                     # propagate upward

        dfs(root)

        max_freq = max(freq.values())    # highest frequency seen
        return [k for k, cnt in freq.items() if cnt == max_freq]
```

### Step-by-step walkthrough (Example 2: `[5, 2, -5]`)

| DFS call | left | right | sum | freq after call |
|---|---|---|---|---|
| `dfs(2)` | 0 | 0 | **2** | `{2: 1}` |
| `dfs(-5)` | 0 | 0 | **-5** | `{2: 1, -5: 1}` |
| `dfs(5)` | 2 | -5 | **2** | `{2: 2, -5: 1}` |

`max_freq = 2`, only sum `2` has count `2` → return `[2]`. ✓

### Why post-order?

We need a node's children to be fully resolved before computing the parent's sum. Post-order DFS (left → right → current) guarantees children are processed first, making the bottom-up accumulation correct and straightforward.

