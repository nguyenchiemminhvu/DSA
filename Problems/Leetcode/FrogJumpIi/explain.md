## Problem

https://leetcode.com/problems/frog-jump-ii/description/

Given a 0-indexed integer array `stones` sorted in strictly increasing order, a frog starts on `stones[0]` and wants to travel to `stones[n-1]` and back to `stones[0]`. Each stone may be visited **at most once** across both trips. The **cost** of a path is the maximum single-jump length. Return the minimum possible cost.

**Example 1:** `stones = [0,2,5,6,7]` → `5`  
**Example 2:** `stones = [0,3,9]` → `9`

**Constraints:** `2 <= stones.length <= 1e5`, `stones[0] == 0`, strictly increasing.

## Observations

1. **Two monotone paths.** The forward trip is an increasing subsequence of `stones`; the return trip is a decreasing one. Together they must cover every stone, with only the endpoints shared. So the problem reduces to: *partition the intermediate stones between two monotone subsequences and minimise the maximum gap inside each subsequence.*

2. **Lower bound — the skip-one gap.**  
   Consider any three consecutive stones `A = stones[i]`, `B = stones[i+1]`, `C = stones[i+2]`. They must be assigned to two paths. If `B` ends up on a different path from `A` and `C`, both paths are monotone and the path containing `A` and `C` jumps directly `A → C`, paying `C − A = stones[i+2] − stones[i]`.  
   
   By a pigeonhole argument on an alternating 2-coloring, there always exists *some* triple where the middle stone is on the other path, so the answer is **at least** `max(stones[i] − stones[i−2])` for `i` from `2` to `n−1`.

3. **Upper bound — alternating assignment achieves the lower bound.**  
   Assign even-indexed stones to path 1 and odd-indexed stones to path 2. The largest jump on either path is at most `max(stones[i] − stones[i−2])`, so this assignment is optimal. The answer is exactly:
   
   ```
   answer = max(stones[i] - stones[i-2])  for i in [2, n-1]
   ```

## Solution

The code explicitly constructs the two paths and tracks the running maximum jump.

```python
class Solution:
    def maxJump(self, pos: List[int]) -> int:
        n = len(pos)
        if n == 2:
            return pos[-1] - pos[0]

        res = 0
        marked = [False] * n

        # --- Path 1 (forward): even indices 0, 2, 4, ... ---
        prev = 0
        for i in range(2, n, 2):
            res = max(res, pos[i] - pos[prev])
            marked[i] = True
            prev = i

        # If n is even the last even index is n-2, not n-1.
        # Extend path 1 to reach the final stone.
        if i != n - 1:
            res = max(res, pos[-1] - pos[i])
            marked[n - 1] = True
            prev = n - 1

        # --- Path 2 (backward): odd indices n-2, n-4, ..., 1 ---
        # Scan right-to-left and pick up every unmarked stone.
        for i in range(n - 1, -1, -1):
            if not marked[i]:
                res = max(res, pos[prev] - pos[i])
                marked[i] = True
                prev = i

        return res
```

**Step-by-step trace on `[0, 2, 5, 6, 7]` (n = 5):**

| Phase | Move | Jump size | `res` |
|-------|------|-----------|-------|
| Path 1 | 0 → 5 (idx 0→2) | 5 | 5 |
| Path 1 | 5 → 7 (idx 2→4) | 2 | 5 |
| Path 2 | 7 → 6 (idx 4→3) | 1 | 5 |
| Path 2 | 6 → 2 (idx 3→1) | 4 | 5 |
| Path 2 | 2 → 0 (idx 1→0) | 2 | 5 |

Result: **5** ✓

**Simpler equivalent one-liner** (same idea, no explicit path construction):

```python
def maxJump(self, stones: List[int]) -> int:
    return max(stones[i] - stones[i - 2] for i in range(2, len(stones)))
```

**Complexity:** O(n) time, O(1) extra space (or O(n) with the `marked` array).

# Tags
`Greedy` `Array`

