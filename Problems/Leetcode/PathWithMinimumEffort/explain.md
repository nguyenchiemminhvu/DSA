## Problem

https://leetcode.com/problems/path-with-minimum-effort/description/

Given a 2D grid `heights[rows][cols]`, find a path from the top-left cell `(0, 0)` to the bottom-right cell `(rows-1, cols-1)` moving in 4 directions (up, down, left, right). A path's **effort** is the **maximum absolute difference** in heights between any two consecutive cells on that path. Return the **minimum effort** over all possible paths.

---

## Observations

1. **Effort definition is "bottleneck"**: The cost of a path is determined by its worst single step, not the sum. This is a classic minimax / minimum bottleneck path problem.

2. **Greedy substructure**: If we know the minimum effort to reach cell `(r, c)`, we should always prefer paths that minimize the maximum edge weight seen so far — not the total weight. This is analogous to Dijkstra's algorithm but with `max` instead of `+`.

3. **Relaxation condition**: For a neighbor `(nr, nc)`, the effort to reach it via `(r, c)` is `max(cur_effort, |heights[r][c] - heights[nr][nc]|)`. We update `efforts[nr][nc]` only if this value is strictly smaller than the currently known best.

4. **Min-heap priority queue**: By always processing the cell with the smallest known effort first, we guarantee that when a cell is first popped, its recorded effort is optimal (same correctness argument as Dijkstra).

5. **Base case**: `efforts[0][0] = 0` because no movement is needed to "reach" the starting cell, so the effort is 0.

---

## Solution Explanation

The algorithm is **Dijkstra's algorithm adapted for bottleneck cost**:

```python
class Solution:
    def minimumEffortPath(self, heights: List[List[int]]) -> int:
        INF = 0xFFFFFFFF
        m, n = len(heights), len(heights[0])
        efforts = [[INF] * n for _ in range(m)]
        efforts[0][0] = 0

        pq = [(0, (0, 0))]
        while pq:
            cur_effort, (r, c) = heapq.heappop(pq)

            if cur_effort > efforts[r][c]:
                continue

            for nr, nc in [(r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)]:
                if nr < 0 or nr >= m or nc < 0 or nc >= n:
                    continue
                
                next_effort = abs(heights[r][c] - heights[nr][nc])
                if efforts[nr][nc] > max(cur_effort, next_effort):
                    efforts[nr][nc] = max(cur_effort, next_effort)
                    heapq.heappush(pq, (efforts[nr][nc], (nr, nc)))
        
        return efforts[m - 1][n - 1]
```

**Step-by-step:**

1. **Initialize** `efforts[r][c] = INF` for all cells, except `efforts[0][0] = 0`. Push `(0, (0,0))` onto the min-heap.

2. **Pop** the cell `(r, c)` with the smallest current effort from the heap.

3. **Stale check**: If `cur_effort > efforts[r][c]`, this entry is outdated (a better path was already found); skip it.

4. **Relax neighbors**: For each valid neighbor `(nr, nc)`, compute the effort of reaching it through `(r, c)`:
   $$\text{new\_effort} = \max(\text{cur\_effort},\ |h[r][c] - h[nr][nc]|)$$
   If this is better than `efforts[nr][nc]`, update and push to the heap.

5. **Termination**: When `(m-1, n-1)` is popped, `efforts[m-1][n-1]` holds the answer.

**Why `max` instead of `+`?**  
In standard Dijkstra, edge weights accumulate with `+`. Here, the path cost is the *maximum* edge weight, so we use `max`. The min-heap still ensures we process optimal states first because a smaller bottleneck effort dominates a larger one.

**Complexity:**
- Time: $O(m \cdot n \cdot \log(m \cdot n))$ — each cell is pushed/popped at most once optimally.
- Space: $O(m \cdot n)$ for the `efforts` table and heap.
