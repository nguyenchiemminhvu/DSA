## Problem

https://leetcode.com/problems/minimum-cost-of-a-path-with-special-roads/description/

You start at `(startX, startY)` and want to reach `(targetX, targetY)` in 2D space. Moving between any two points costs their Manhattan distance. There are also special one-directional roads, each going from `(x1, y1)` to `(x2, y2)` at a fixed `cost` that may be cheaper than the Manhattan distance. Return the minimum total cost to reach the target.

---

## Observations

1. **Movement is always possible via Manhattan distance.** You can go from any point to any other point directly; there is no restriction — the cost is just `|dx| + |dy|`.

2. **Special roads are optional shortcuts.** A special road from `p1` to `p2` is only beneficial when its `cost < dist(p1, p2)`. Otherwise, walking directly is at least as cheap.

3. **Only the endpoints matter.** The optimal path will only "stop" at the start, the target, or the endpoints of special roads. Any detour to a point that is not one of these is dominated by going directly. This reduces the infinite 2D space to at most `2 + 2 * len(specialRoads)` relevant points (≤ 402).

4. **This is a shortest-path problem on a small graph.** Build a complete graph on the relevant points where:
   - Every pair `(p1, p2)` has an edge weighted by their Manhattan distance.
   - Each special road `(x1,y1) → (x2,y2)` additionally offers an edge of weight `cost` (only kept if it beats the Manhattan distance).
   
   Then run **Dijkstra** from `start` to find the minimum cost to reach `target`.

---

## Solution Explanation

```python
class Solution:
    def minimumCost(self, start: List[int], target: List[int], roads: List[List[int]]) -> int:
        def dist(p1, p2):
            x1, y1 = p1
            x2, y2 = p2
            return abs(x2 - x1) + abs(y2 - y1)
        
        INF = 0xFFFFFFFF
        graph = defaultdict(lambda: defaultdict(lambda: int(INF)))
        
        points = set([tuple(start), tuple(target)])
        for x1, y1, x2, y2, _ in roads:
            points.add((x1, y1))
            points.add((x2, y2))
        
        for p1 in points:
            for p2 in points:
                if p1 == p2:
                    continue
                graph[p1][p2] = min(
                    graph[p1][p2],
                    dist(p1, p2)
                )
        
        for x1, y1, x2, y2, cost in roads:
            p1 = (x1, y1)
            p2 = (x2, y2)
            if dist(p1, p2) <= cost:
                continue
            graph[p1][p2] = min(
                graph[p1][p2],
                cost
            )
        
        n = len(points)
        shortest_dist = defaultdict(lambda: int(INF))
        shortest_dist[tuple(start)] = 0

        pq = [(0, tuple(start))]
        while pq:
            cur_dist, node = heapq.heappop(pq)
            if cur_dist > shortest_dist[node]:
                continue

            if node == target:
                return cur_dist
            
            for adj in graph[node]:
                next_cost = graph[node][adj]
                if cur_dist + next_cost < shortest_dist[adj]:
                    shortest_dist[adj] = cur_dist + next_cost
                    heapq.heappush(pq, (shortest_dist[adj], adj))
        
        return shortest_dist[tuple(target)]
```

### Step-by-step

**1. Collect relevant points.**  
Start with `start` and `target`. Add both endpoints of every special road. This gives at most ~402 points.

**2. Build the graph — Manhattan distance edges.**  
For every ordered pair `(p1, p2)` of distinct relevant points, add a directed edge with weight `dist(p1, p2)`. Since you can freely walk anywhere, every point can reach every other point.

**3. Override with special road edges where beneficial.**  
For each special road, if its fixed `cost` is strictly less than `dist(p1, p2)`, update the edge `p1 → p2` to use `cost` instead. If `dist(p1, p2) <= cost`, the road offers no benefit and is ignored.

**4. Run Dijkstra from `start`.**  
Standard Dijkstra on the small graph. The priority queue holds `(accumulated_cost, point)`. Early exit as soon as `target` is popped.

### Complexity

- **Points:** $O(n)$ where $n$ = number of special roads (≤ 200).
- **Graph construction:** $O(n^2)$ edges.
- **Dijkstra:** $O(n^2 \log n)$.
- Overall: $O(n^2 \log n)$, well within limits.
