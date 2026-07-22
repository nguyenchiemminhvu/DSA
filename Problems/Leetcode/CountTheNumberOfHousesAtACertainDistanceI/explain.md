## Problem

https://leetcode.com/problems/count-the-number-of-houses-at-a-certain-distance-i/description/

Given three positive integers `n`, `x`, and `y`, there are `n` houses numbered `1` to `n` connected by a linear chain of streets (`i` ↔ `i+1` for all valid `i`). An **additional** street connects house `x` with house `y`, potentially creating a shortcut. For each `k` from `1` to `n`, find the number of **ordered pairs** `(house1, house2)` such that the **minimum** number of streets to travel from `house1` to `house2` is exactly `k`. Return a 1-indexed array `result` of length `n`.

---

## Observations

1. **Base graph is a path (line graph):** Houses `1..n` form a straight line. Without the extra edge, the distance between house `i` and house `j` is simply `|i - j|`.

2. **Extra edge creates a shortcut:** The edge `x ↔ y` may reduce distances between certain pairs. If `x == y` or `|x - y| == 1`, the extra edge adds nothing new (self-loop or already adjacent).

3. **Small constraints allow BFS from every node:** With `n ≤ 100`, running BFS from each of the `n` houses costs at most `O(n²)`, which is very efficient.

4. **Ordered pairs:** The problem asks for **ordered** pairs, so both `(a, b)` and `(b, a)` are counted separately. BFS naturally handles this because we run it from every node.

5. **Distance = 0 is trivially a node with itself:** We skip `k = 0` in the result; the answer array is 1-indexed from `k = 1`.

---

## Solution Explanation

```python
class Solution:
    def countOfPairs(self, n: int, x: int, y: int) -> List[int]:
        k_count = defaultdict(int)
        graph = defaultdict(list)
        for i in range(2, n + 1):
            graph[i].append(i - 1)
            graph[i - 1].append(i)
        
        if abs(x - y) != 1:
            graph[x].append(y)
            graph[y].append(x)

        def bfs(start: int):
            INF = 0x7FFFFFFF
            q = deque([start])
            visited = set([start])
            steps = -1
            while q:
                steps += 1
                count = len(q)
                for _ in range(count):
                    cur = q.popleft()
                    k_count[steps] += 1
                    for adj in graph[cur]:
                        if adj not in visited:
                            visited.add(adj)
                            q.append(adj)
        
        for i in range(1, n + 1):
            bfs(i)
        
        return [k_count[i] for i in range(1, n + 1)]
```

### Step-by-step breakdown

**1. Build the graph**
- Add edges `i ↔ i+1` for all `i` from `1` to `n-1` to model the linear street layout.
- Add the extra shortcut edge `x ↔ y` **only if** it isn't already implied (i.e., `|x - y| != 1`). If `x == y`, the condition `abs(x - y) != 1` is still `True`, but adding a self-loop to the adjacency list has no effect on BFS because `x` is already visited when we process it.

**2. BFS from every house**
- For each starting house, perform a standard **level-order BFS**.
- The variable `steps` tracks the current distance (number of streets traveled).
- At each level, every node dequeued is at distance `steps` from `start`. We increment `k_count[steps]` for every such node (including the start itself at distance `0`).

**3. Collect results**
- `k_count[0]` counts all `(house, house)` same-node pairs (distance 0) — we ignore these.
- `k_count[k]` for `k ≥ 1` gives the total number of **ordered pairs** at distance `k`.
- Return `[k_count[1], k_count[2], ..., k_count[n]]`.

### Why BFS works here
BFS guarantees the **shortest path** in an unweighted graph. Because the extra edge creates at most one cycle, the graph remains simple enough that BFS from each node correctly computes all pairwise minimum distances.

### Complexity
- **Time:** `O(n²)` — BFS is `O(V + E) = O(n)` per start node, run `n` times.
- **Space:** `O(n)` for the graph, queue, and visited set.

