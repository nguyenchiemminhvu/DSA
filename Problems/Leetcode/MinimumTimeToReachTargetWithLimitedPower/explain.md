## Problem

https://leetcode.com/problems/minimum-time-to-reach-target-with-limited-power/description/

You are given a directed weighted graph with `n` nodes (labeled `0` to `n-1`), a list of directed edges `edges[i] = [u, v, t]` (traversal takes `t` seconds), and an integer `power` (initial power). Each node `u` has a `cost[u]` — the power consumed when the signal **leaves** that node.

The signal starts at `source` with `power` units. Find the path to `target` such that:
- The signal can only leave node `u` if remaining power `>= cost[u]`.
- Power decreases by `cost[u]` each time the signal leaves `u`.
- Time increases by `t` for each edge traversed.

Return `[min_time, max_remaining_power]` for the fastest path. Among all paths with the same minimum time, return the one with the highest remaining power. If unreachable, return `[-1, -1]`.

---

## Observations

1. **Two competing objectives**: minimize time first, then maximize remaining power. This is a lexicographic optimization problem well-suited for a modified Dijkstra.

2. **State space**: A simple `dist[node]` table is insufficient because the same node can be reached with different amounts of power consumed. Two paths reaching the same node — one fast but power-hungry, the other slow but frugal — can both lead to optimal outcomes depending on what happens next.  
   We need the state `(node, used_power)` to capture this.

3. **State table `used[node][p]`**: Stores the **minimum time** to reach `node` having consumed exactly `p` units of power so far. This is a 2D Dijkstra over `n * (power + 1)` states.

4. **Priority queue ordering**: We push `(time, used_power, node)` and pop by minimum time first. When two states have the same time at the target, the one with **less used power** (hence more remaining) is processed first — but since we return immediately upon reaching the target, we need to be careful. Actually, because we also want **maximum remaining power** (minimum used power) among paths of equal minimum time, we can break ties by `used_power` ascending in the heap, so the first time we pop `node == target`, it is guaranteed to be the optimal answer.

5. **Early termination**: Once we pop the target from the heap, we immediately return, because Dijkstra guarantees that the first time a state is finalized it has the globally optimal (time, used_power) pair.

6. **Complexity**: There are `O(n * power)` states, each processed once. Each pop triggers at most `O(degree)` pushes. Total: `O(n * power * log(n * power))`.

---

## Solution Explanation

```python
import heapq

class Solution:
    def minTimeMaxPower(self, n: int, edges: List[List[int]], power: int, cost: List[int], source: int, target: int) -> List[int]:
        # Base case: no traversal needed
        if source == target:
            return [0, power]
        
        # Build adjacency list: graph[u] = [(time, v), ...]
        graph = defaultdict(list)
        for u, v, t in edges:
            graph[u].append((t, v))
        
        INF = float('inf')

        # used[node][p] = minimum time to reach `node` having used exactly `p` power
        used = [[INF] * (power + 1) for _ in range(n)]
        used[source][0] = 0  # At source, 0 time elapsed, 0 power used

        # Min-heap: (current_time, current_used_power, current_node)
        # Sorting by time first, then used_power (less used = more remaining = better)
        pq = [(0, 0, source)]

        while pq:
            t, p, node = heapq.heappop(pq)

            # Skip if this state is outdated (a better path was already found)
            if t > used[node][p]:
                continue

            # First time target is popped = minimum time, maximum remaining power
            if node == target:
                return [t, power - p]
            
            # Cannot leave this node if not enough power
            if p + cost[node] > power:
                continue
            
            # Explore neighbors
            for next_t, next_node in graph[node]:
                new_time = t + next_t
                new_used = p + cost[node]
                if new_time < used[next_node][new_used]:
                    used[next_node][new_used] = new_time
                    heapq.heappush(pq, (new_time, new_used, next_node))
            
        return [-1, -1]
```

### Step-by-step walkthrough (Example 1)

```
n=5, edges=[[0,1,1],[1,4,1],[0,2,1],[2,3,1],[3,4,1]]
power=4, cost=[2,3,1,1,1], source=0, target=4
```

| Pop (t, p, node) | Action |
|---|---|
| `(0, 0, 0)` | Leave node 0, cost=2 → push `(1, 2, 1)` and `(1, 2, 2)` |
| `(1, 2, 1)` | Leave node 1, cost=3 → p+cost=5 > power=4, **skip** |
| `(1, 2, 2)` | Leave node 2, cost=1 → push `(2, 3, 3)` |
| `(2, 3, 3)` | Leave node 3, cost=1 → push `(3, 4, 4)` |
| `(3, 4, 4)` | **target reached** → return `[3, 4-4]` = `[3, 0]` ✓ |

### Key insight

The algorithm is essentially **Dijkstra on a 2D state space** `(node, used_power)`, where edge weights are traversal times. The heap ordering `(time, used_power)` ensures that when the target is first dequeued, we have both the **minimum time** and — among all paths achieving that minimum time — the **minimum power used** (i.e., maximum remaining power).

