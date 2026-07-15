## Problem

https://leetcode.com/problems/find-minimum-time-to-reach-last-room-i/description/

Given an `n x m` dungeon grid, each room `(i, j)` has a gate that only opens at or after time `moveTime[i][j]`. You start at `(0, 0)` at time `t = 0`. Moving between adjacent rooms takes exactly **1 second**. Return the **minimum time** to reach the bottom-right room `(n-1, m-1)`.

---

## Observations

1. **This is a shortest-path problem on a grid.** We need the minimum "arrival time" at each cell, not just shortest distance — because rooms have time constraints that may force us to wait.

2. **We cannot enter room `(i, j)` before `moveTime[i][j]`.** So the arrival time at a neighbor `(nr, nc)` is:
   - If we arrive at `(r, c)` at time `cur_time` and `cur_time >= moveTime[nr][nc]`, we can move immediately: `arrival = cur_time + 1`.
   - If `cur_time < moveTime[nr][nc]`, we must wait until the room opens: `arrival = moveTime[nr][nc] + 1`.
   - Combined: `arrival = max(cur_time, moveTime[nr][nc]) + 1`.

3. **Dijkstra's algorithm** is a natural fit here. Each node's "cost" is the arrival time, and we always expand the node with the smallest current time first (min-heap). This guarantees we find the optimal path without re-processing nodes.

4. **Standard BFS is not enough** because move costs are not uniform — waiting forces some paths to be more expensive than others.

---

## Solution Explanation

We apply **Dijkstra's algorithm** where the "distance" to each cell is the earliest time we can arrive there.

**Data structures:**
- `dp[i][j]` — the minimum time to reach cell `(i, j)`, initialized to `INF` except `dp[0][0] = 0`.
- A **min-heap** (priority queue) `pq` of `(time, (row, col))` tuples, seeded with `(0, (0, 0))`.

**Algorithm:**
1. Pop the cell `(r, c)` with the smallest current time from the heap.
2. Skip it if the stored time is outdated (already found a better path).
3. For each of the 4 adjacent neighbors `(nr, nc)`:
   - Compute `next_cost = max(cur_time, moveTime[nr][nc]) + 1`.
   - If `next_cost < dp[nr][nc]`, update `dp[nr][nc]` and push to the heap.
4. Return `dp[n-1][m-1]`.

**Why it works:** Dijkstra's guarantees that the first time we finalize a cell, it holds the minimum arrival time. The "waiting" mechanism is encoded naturally in the cost function.

**Time complexity:** $O(n \cdot m \cdot \log(n \cdot m))$ — each cell is pushed/popped from the heap at most once optimally.  
**Space complexity:** $O(n \cdot m)$ for the `dp` table and heap.

---

## Solution

```python
class Solution:
    def minTimeToReach(self, move_time: List[List[int]]) -> int:
        m, n = len(move_time), len(move_time[0])
        INF = 0xFFFFFFFF

        dp = [[INF] * n for _ in range(m)]
        dp[0][0] = 0
        pq = [(0, (0, 0))]
        while pq:
            cur_time, (r, c) = heapq.heappop(pq)
            if cur_time > dp[r][c]:
                continue

            for nr, nc in [(r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)]:
                if nr < 0 or nr >= m or nc < 0 or nc >= n:
                    continue
                
                next_cost = move_time[nr][nc] + 1
                if cur_time >= move_time[nr][nc]:
                    next_cost = cur_time + 1
                
                if dp[nr][nc] > next_cost:
                    dp[nr][nc] = next_cost
                    heapq.heappush(pq, (next_cost, (nr, nc)))
        
        return dp[m - 1][n - 1]
```
