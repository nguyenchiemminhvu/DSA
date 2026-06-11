## Problem

https://leetcode.com/problems/maximum-path-quality-of-a-graph/description/

Given an undirected graph with `n` nodes (numbered `0` to `n-1`), an array `values[i]` representing each node's value, a list of edges `[u, v, time]`, and an integer `maxTime` — find the **maximum quality** of a valid path.

A **valid path**:
- Starts **and ends** at node `0`
- Takes **at most** `maxTime` seconds total
- May visit the same node multiple times

**Quality** = sum of `values[i]` for each **unique** node visited (each node counts at most once).

---

## Observations

1. **Bounded depth via constraints.**  
   Each edge takes at least `10` seconds (`timej >= 10`) and `maxTime <= 100`, so any valid path traverses **at most** `maxTime / min(timej) = 100 / 10 = 10` edges. This caps the DFS recursion depth at 10.

2. **Bounded branching factor.**  
   The problem states: *"There are at most four edges connected to each node."* So at each step we have at most 4 choices.

3. **Combined search space is small.**  
   At most `4^10 ≈ 1,000,000` paths to explore — brute-force DFS with backtracking is feasible within time limits.

4. **Nodes can be revisited, but their value is counted only once.**  
   This means we must track which nodes have been visited, not just the current node.

5. **The path must return to node `0`.**  
   We only record a candidate answer when `cur_node == 0` (not just at the end of recursion), because we can pass through `0` mid-path and still continue.

6. **The graph may not be connected.**  
   Unreachable nodes can simply be ignored — the DFS naturally never reaches them from node `0`.

---

## Solution Explanation

The solution uses **backtracking DFS** starting from node `0`.

```python
class Solution:
    def maximalPathQuality(self, values: List[int], edges: List[List[int]], maxTime: int) -> int:
        n = len(values)
        adj = defaultdict(list)
        for u, v, t in edges:
            adj[u].append((t, v))
            adj[v].append((t, u))
        
        max_path = 0
        def backtracking(cur_node: int, remain_time: int, temp: List[int]):
            nonlocal max_path
            if remain_time < 0:
                return
            
            if cur_node == 0:
                max_path = max(max_path, sum(values[i] for i in set(temp)))

            for time, next_node in adj[cur_node]:
                temp.append(next_node)
                backtracking(next_node, remain_time - time, temp)
                temp.pop()
        
        backtracking(0, maxTime, [0])
        return max_path
```

### Step-by-step walkthrough

**1. Build adjacency list.**  
Convert `edges` into an undirected adjacency list `adj[u] = [(time, v), ...]`.

**2. DFS with backtracking.**  
Call `backtracking(0, maxTime, [0])` — start at node `0`, full time budget, path initialized with `[0]`.

**3. Pruning.**  
If `remain_time < 0`, this path exceeded the time limit — stop immediately.

**4. Record answer at node `0`.**  
Whenever we land back at node `0` (even mid-path), compute the sum of values of unique nodes in `temp` using `set(temp)`, and update `max_path`.

**5. Explore neighbors and backtrack.**  
For each neighbor `next_node` reachable in `time` seconds:
- Push `next_node` onto `temp`
- Recurse with `remain_time - time`
- Pop `next_node` from `temp` (backtrack)

This ensures `temp` always reflects the exact path from the root down to the current call frame.

### Why `temp` and `set(temp)`?

`temp` stores the **sequence** of all nodes visited (with repetitions). Using `set(temp)` extracts the unique nodes visited, so the quality sum counts each node's value at most once — exactly as the problem requires.

### Complexity

| | |
|---|---|
| **Time** | $O(4^{T/t_{min}})$ where $T = \text{maxTime}$, $t_{min} = 10$ → $O(4^{10}) \approx O(10^6)$ |
| **Space** | $O(n + E)$ for adjacency list + $O(T / t_{min})$ recursion stack depth |
