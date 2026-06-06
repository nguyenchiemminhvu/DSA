## Problem

https://leetcode.com/problems/minimum-number-of-operations-to-sort-a-binary-tree-by-level/description/

You are given the `root` of a binary tree with **unique values**.

In one operation, you can choose any two nodes **at the same level** and swap their values.

Return the **minimum number of operations** needed to make the values at each level sorted in **strictly increasing order**.

---

## Observations

1. **Levels are independent.** A swap at one level has no effect on any other level, so each level can be solved independently.

2. **Collect each level with BFS.** A standard level-order traversal (BFS with a queue) naturally groups nodes by level, giving us an array of values per level.

3. **The sub-problem: minimum swaps to sort an array.** For each level's array, we need the minimum number of swaps to sort it. This is a classic problem solved with a **greedy + position-map** approach:
   - Compare the current array against its sorted version.
   - Walk through each index. Whenever `arr[i] != sorted_arr[i]`, swap `arr[i]` with whichever element *should* be at position `i` (found in O(1) via a value→index map), and count one operation.
   - Each such swap places at least one element in its correct position, so this greedy is optimal.

4. **Why greedy gives the minimum?** The minimum number of swaps to sort a permutation equals `n − (number of cycles in the permutation)`. The greedy cycle-following above achieves exactly this count without needing to enumerate cycles explicitly.

5. **Complexity:**
   - BFS: O(N) where N is the number of nodes.
   - Sorting + greedy per level: O(k log k) for a level of size k; summed over all levels this is O(N log N).
   - Overall: **O(N log N)** time, **O(N)** space.

---

## Solution Explanation

```python
from collections import deque
from typing import Optional, List

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def minimumOperations(self, root: Optional[TreeNode]) -> int:
        def min_swap_make_sorted(arr: List[int]) -> int:
            n = len(arr)
            # Map each value to its current index for O(1) look-up.
            mp = {}
            for i in range(n):
                mp[arr[i]] = i

            sorted_arr = sorted(arr)

            count_swap = 0
            for sorted_idx in range(n):
                if arr[sorted_idx] != sorted_arr[sorted_idx]:
                    count_swap += 1

                    # Find where the value that belongs at sorted_idx currently sits.
                    orig_idx = mp[sorted_arr[sorted_idx]]

                    # Swap it into place.
                    arr[sorted_idx], arr[orig_idx] = arr[orig_idx], arr[sorted_idx]

                    # Keep the map consistent after the swap.
                    mp[arr[orig_idx]] = orig_idx
                    mp[arr[sorted_idx]] = sorted_idx

            return count_swap

        if not root:
            return 0

        res = 0
        q = deque([root])

        # BFS: process one level at a time.
        while q:
            z = len(q)
            row = []
            for _ in range(z):
                cur = q.popleft()
                row.append(cur.val)
                if cur.left:
                    q.append(cur.left)
                if cur.right:
                    q.append(cur.right)

            # Accumulate the minimum swaps needed for this level.
            res += min_swap_make_sorted(row)

        return res
```

### Step-by-step walkthrough (Example 1: `[1,4,3,7,6,8,5,…]`)

| Level | Values collected | Sorted target | Swaps |
|-------|-----------------|---------------|-------|
| 0 | `[1]` | `[1]` | 0 |
| 1 | `[4, 3]` | `[3, 4]` | 1 — swap 4↔3 |
| 2 | `[7, 6, 8, 5]` | `[5, 6, 7, 8]` | 2 — swap 7↔5, then 8↔7 |

Total: **3 operations** ✓

### Key insight in `min_swap_make_sorted`

The value-to-index map `mp` lets us answer "where is value V right now?" in O(1). After each swap we update only the two affected entries, keeping the map valid for all future steps. This avoids an O(n) scan per swap and keeps the function at O(n log n) overall (dominated by the sort).
