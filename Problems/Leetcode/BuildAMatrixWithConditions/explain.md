## Problem

https://leetcode.com/problems/build-a-matrix-with-conditions/description/

Given a positive integer `k` and two constraint arrays `rowConditions` and `colConditions`, build a `k x k` matrix containing each number from `1` to `k` exactly once (remaining cells are `0`) such that:
- For each `[above, below]` in `rowConditions`, `above` appears in a strictly higher row than `below`.
- For each `[left, right]` in `colConditions`, `left` appears in a strictly left column than `right`.

Return any valid matrix, or an empty matrix if none exists.

---

## Observations

1. **Row and column constraints are independent.** The row ordering of numbers has no effect on their column ordering. We can solve each dimension separately.

2. **Each constraint `[u, v]` is a directed edge `u → v`.** "u must come before v" in the ordering — this is exactly the definition of a **directed dependency graph**.

3. **We need a linear ordering that respects all dependencies** — this is **topological sort**.

4. **A cycle means no valid ordering exists.** If topological sort cannot include all `k` numbers (cycle detected), return an empty matrix.

5. **Once we have row order and column order**, placing number `i` is trivial: put it at `matrix[row_pos[i]][col_pos[i]]`.

---

## Solution Explanation

### Step 1 — Topological Sort (Kahn's BFS algorithm)

For both `rowConditions` and `colConditions`, build a directed graph and compute **in-degrees** for each node `1..k`.

```
graph[u].append(v)   # u must appear before v
in_degree[v] += 1
```

Start BFS from all nodes with `in_degree == 0` (no prerequisites). Each time a node is processed, decrement the in-degree of its neighbours. When a neighbour's in-degree reaches `0`, enqueue it.

If the resulting topological order contains all `k` numbers → valid. Otherwise a cycle exists → return `[]`.

### Step 2 — Build position maps

```python
row_pos = {num: index for index, num in enumerate(row_topo)}
col_pos = {num: index for index, num in enumerate(col_topo)}
```

`row_topo[i] = num` means number `num` should be placed in row `i`. The position map inverts this for O(1) lookup.

### Step 3 — Fill the matrix

```python
for i in range(1, k + 1):
    res[row_pos[i]][col_pos[i]] = i
```

Each number gets a unique row and a unique column because the topological order is a permutation of `1..k`.

---

## Complexity

| | Time | Space |
|---|---|---|
| Topo sort (×2) | $O(k + E)$ where $E$ = number of conditions | $O(k + E)$ |
| Matrix fill | $O(k)$ | $O(k^2)$ |
| **Total** | $O(k^2 + E)$ | $O(k^2 + E)$ |

---

## Code

```python
class Solution:
    def buildMatrix(self, k: int, row_conds: List[List[int]], col_conds: List[List[int]]) -> List[List[int]]:
        def topo_sort_bfs(conds: List[List[int]]) -> List[int]:
            graph = defaultdict(list)
            in_degree = [0] * (k + 1)
            for u, v in conds:
                graph[u].append(v)
                in_degree[v] += 1
            topo = []
            q = deque([u for u in range(1, k + 1) if in_degree[u] == 0])
            while q:
                cur = q.popleft()
                topo.append(cur)
                for adj in graph[cur]:
                    in_degree[adj] -= 1
                    if in_degree[adj] == 0:
                        q.append(adj)
            return topo if len(topo) == k else []

        row_topo = topo_sort_bfs(row_conds)
        col_topo = topo_sort_bfs(col_conds)
        if not row_topo or not col_topo:
            return []

        row_pos = {num: i for i, num in enumerate(row_topo)}
        col_pos = {num: i for i, num in enumerate(col_topo)}

        res = [[0] * k for _ in range(k)]
        for i in range(1, k + 1):
            res[row_pos[i]][col_pos[i]] = i
        return res
```
