## Problem

https://leetcode.com/problems/find-minimum-time-to-reach-last-room-ii/

There is a dungeon with `n x m` rooms arranged as a grid. You are given a 2D array `moveTime` of size `n x m`, where `moveTime[i][j]` represents the **minimum time** in seconds when you can **start** moving to that room. You start from room `(0, 0)` at time `t = 0` and can move to an adjacent room.

Moving between adjacent rooms takes **alternating costs**: **1 second** for one move and **2 seconds** for the next, toggling back and forth.

Return the **minimum time** to reach room `(n-1, m-1)`.

---

## Observations

1. **It's a shortest-path problem on a grid.** We need the minimum time to go from `(0,0)` to `(n-1, m-1)`, which maps naturally to **Dijkstra's algorithm** with a min-heap (priority queue).

2. **Waiting is allowed.** If we arrive at a room before the earliest allowed departure time `moveTime[nr][nc]`, we must wait until that time before we can start moving to the next room.

3. **Alternating move cost.** The cost to move from cell `(r, c)` to an adjacent cell alternates between 1 and 2 seconds. The parity of `(r + c)` determines which cost applies:
   - If `(r + c)` is **even** → current move costs **1 second**.
   - If `(r + c)` is **odd** → current move costs **2 seconds**.

   This works because each move changes the sum `r + c` by exactly 1, so the parity flips with every step.

4. **Standard Dijkstra optimization applies.** When we pop a node from the heap with a time greater than its recorded best distance, we skip it — it's already been processed with a shorter time.

---

## Solution Explanation

```python
class Solution:
    def minTimeToReach(self, move_time: List[List[int]]) -> int:
        INF = 0xFFFFFFFF
        m, n = len(move_time), len(move_time[0])
        dist = [[INF] * n for _ in range(m)]
        dist[0][0] = 0
        pq = [(0, (0, 0))]
        while pq:
            t, (r, c) = heapq.heappop(pq)
            if t > dist[r][c]:
                continue
            
            cost_next_step = ((r + c) % 2) + 1
            for nr, nc in [(r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)]:
                if 0 <= nr < m and 0 <= nc < n:
                    next_t = move_time[nr][nc] + cost_next_step
                    if t >= move_time[nr][nc]:
                        next_t = t + cost_next_step
                    
                    if dist[nr][nc] > next_t:
                        dist[nr][nc] = next_t
                        heapq.heappush(pq, (next_t, (nr, nc)))
        
        return -1 if dist[m - 1][n - 1] == INF else dist[m - 1][n - 1]
```

**Step-by-step walkthrough:**

1. **Initialization:** Set all distances to `INF`, set `dist[0][0] = 0`, and push `(0, (0,0))` into the min-heap.

2. **Dijkstra loop:** Pop the cell `(r, c)` with the smallest current time `t`.
   - If `t > dist[r][c]`, this is a stale entry — skip it.

3. **Determine move cost from `(r, c)`:**
   - `cost_next_step = ((r + c) % 2) + 1`
   - This gives **1** when `(r+c)` is even, **2** when odd.

4. **Relax neighbors:** For each adjacent cell `(nr, nc)`:
   - If we arrive **before** the room opens (`t < moveTime[nr][nc]`), we wait until `moveTime[nr][nc]` and then spend `cost_next_step` seconds moving:
     `next_t = moveTime[nr][nc] + cost_next_step`
   - If we arrive **at or after** the room opens (`t >= moveTime[nr][nc]`), we move immediately:
     `next_t = t + cost_next_step`
   - If this improves the known distance to `(nr, nc)`, update and push to the heap.

5. **Result:** Return `dist[m-1][n-1]`.

**Complexity:**
- **Time:** $O(m \cdot n \cdot \log(m \cdot n))$ — standard Dijkstra on a grid.
- **Space:** $O(m \cdot n)$ for the distance array and the heap.
