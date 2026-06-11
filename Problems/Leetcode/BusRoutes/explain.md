## Problem

https://leetcode.com/problems/bus-routes/description

You are given an array `routes` where `routes[i]` is the list of stops the `i`-th bus visits (cycling forever). Starting at stop `source` (not on any bus), find the **minimum number of buses** you must board to reach `target`. Return `-1` if unreachable.

---

## Observations

1. **Stop-level BFS is expensive.** Stops can number in the millions; modelling transitions as "walk between stops" leads to a huge graph.

2. **Route-level BFS is the key insight.** Two bus routes are *connected* if they share at least one common stop. Boarding a bus is one step; switching to a connected route (via a shared stop) is another step. We want the fewest steps (buses boarded) to reach any route that contains `target`.

3. **Initialization.** The starting frontier is every route that contains `source` — those are reachable in 1 bus.

4. **Termination.** As soon as we dequeue a route that contains `target`, return the current step count.

5. **Visited set tracks routes, not stops**, so we never re-enqueue the same route.

---

## Solution Explanation

```python
class Solution:
    def numBusesToDestination(self, routes: List[List[int]], source: int, target: int) -> int:
        if source == target:
            return 0

        n_route = len(routes)
        routes = [set(route) for route in routes]   # O(1) membership checks

        # Seed the queue with every route reachable from source (costs 1 bus)
        q = deque([i for i in range(n_route) if source in routes[i]])
        visited = set()
        steps = 0

        while q:
            steps += 1
            for _ in range(len(q)):          # process one BFS level = one bus ride
                cur_line = q.popleft()

                if target in routes[cur_line]:
                    return steps             # found target on this route

                # Expand to all unvisited routes sharing a stop with cur_line
                for i in range(n_route):
                    if i not in visited and routes[cur_line] & routes[i]:
                        visited.add(i)
                        q.append(i)

        return -1
```

### Step-by-step on Example 1
`routes = [[1,2,7],[3,6,7]], source = 1, target = 6`

| Step | Queue (route indices) | Notes |
|------|-----------------------|-------|
| init | [0] | route 0 contains stop 1 |
| 1 | process route 0 → target 6 not here; route 0 ∩ route 1 = {7} → enqueue route 1 | steps = 1 |
| 2 | process route 1 → target 6 **found** | return **2** |

### Complexity
- **Time:** $O(N^2 \cdot S)$ where $N$ = number of routes, $S$ = average stops per route (set intersection).  
  Can be reduced to $O(\sum |r_i|)$ by pre-building a `stop → [route indices]` map.
- **Space:** $O(\sum |r_i|)$ for the set representation.
