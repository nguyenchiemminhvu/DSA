## Problem

https://leetcode.com/problems/kth-largest-sum-in-a-binary-tree/description/

Given the root of a binary tree and a positive integer `k`, return the **kth largest level sum** in the tree. The level sum is the sum of all node values at the same depth (distance from root). If there are fewer than `k` levels, return `-1`.

---

## Observations

- All nodes at the same depth form one "level", and their values sum to a **level sum**.
- A standard **BFS (level-order traversal)** naturally groups nodes by level, making it straightforward to compute each level sum in one pass.
- We need the **kth largest** among all level sums — this is a classic "top-k" problem.
- Instead of collecting all level sums and sorting at the end (O(L log L)), we can maintain a **min-heap of size k** as we go:
  - Push each new level sum into the heap.
  - If the heap exceeds size `k`, pop the smallest element.
  - After full traversal, the heap top is the kth largest value.
- If the total number of levels is less than `k`, the heap will have fewer than `k` elements → return `-1`.

---

## Solution Explanation

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def kthLargestLevelSum(self, root: Optional[TreeNode], k: int) -> int:
        pq = []

        q = deque([root])
        while q:
            sum_row = 0
            for _ in range(len(q)):
                cur = q.popleft()
                sum_row += cur.val
                if cur.left:
                    q.append(cur.left)
                if cur.right:
                    q.append(cur.right)
            heapq.heappush(pq, sum_row)
            if len(pq) > k:
                heapq.heappop(pq)
        
        return -1 if len(pq) < k else heapq.heappop(pq)
```

**Step-by-step walkthrough:**

1. **BFS traversal** — Use a `deque` initialized with the root. Each iteration of the outer `while` loop processes exactly one level.
2. **Level sum computation** — The inner `for` loop drains the current level from the queue, accumulates `sum_row`, and enqueues children for the next level.
3. **Min-heap of size k** — `heapq` in Python is a min-heap. After pushing `sum_row`:
   - If `len(pq) > k`, pop the minimum. This evicts the smallest value seen so far, keeping only the `k` largest candidates.
4. **Final answer** — After all levels are processed:
   - If fewer than `k` levels exist (`len(pq) < k`), return `-1`.
   - Otherwise, `heapq.heappop(pq)` returns the minimum of the heap, which is the **kth largest** level sum.

**Example trace (root = [5,8,9,2,1,3,7,4,6], k = 2):**

| Level | Nodes       | Sum | Heap after push (size ≤ 2) |
|-------|-------------|-----|-----------------------------|
| 1     | 5           | 5   | [5]                         |
| 2     | 8, 9        | 17  | [5, 17]                     |
| 3     | 2, 1, 3, 7  | 13  | [13, 17]  ← 5 evicted       |
| 4     | 4, 6        | 10  | [13, 17]  ← 10 evicted      |

Heap top = **13** ✓

---

## Complexity

| | |
|---|---|
| **Time** | O(n + L log k), where n = number of nodes, L = number of levels |
| **Space** | O(n) for the BFS queue + O(k) for the heap |
